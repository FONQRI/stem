#ifndef ARIO_SERVER_H
#define ARIO_SERVER_H
/*
 * Copyright (c) 2014 DeNA Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "h2o.h"
#include "h2o/http1.h"
#include "h2o/http2.h"
#include "h2o/memcached.h"
#include <errno.h>
#include <limits.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define USE_HTTPS 0
#define USE_MEMCACHED 0

#include "global_server_variables.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

static h2o_globalconf_t config;
static h2o_context_t ctx;
static h2o_multithread_receiver_t libmemcached_receiver;
static h2o_accept_ctx_t accept_ctx;

#if H2O_USE_LIBUV

static void on_accept(uv_stream_t *listener, int status)
{
	uv_tcp_t *conn;
	h2o_socket_t *sock;

	if (status != 0)
		return;

	conn = static_cast<uv_tcp_t *>(h2o_mem_alloc(sizeof(*conn)));
	uv_tcp_init(listener->loop, conn);

	if (uv_accept(listener, (uv_stream_t *) conn) != 0) {
		uv_close((uv_handle_t *) conn, (uv_close_cb) free);
		return;
	}

	sock = h2o_uv_socket_create((uv_stream_t *) conn, (uv_close_cb) free);
	h2o_accept(&accept_ctx, sock);
}

static int create_listener(void)
{
	static uv_tcp_t listener;
	struct sockaddr_in addr;
	int r;

	uv_tcp_init(ctx.loop, &listener);
	uv_ip4_addr("0.0.0.0", ario_vars::SERVER_PORT, &addr);
	if ((r = uv_tcp_bind(&listener, (struct sockaddr *) &addr, 0)) != 0) {
		fprintf(stderr, "uv_tcp_bind:%s\n", uv_strerror(r));
		goto Error;
	}
	if ((r = uv_listen((uv_stream_t *) &listener, 128, on_accept)) != 0) {
		fprintf(stderr, "uv_listen:%s\n", uv_strerror(r));
		goto Error;
	}

	return 0;
Error:
	uv_close((uv_handle_t *) &listener, NULL);
	return r;
}

#else

static void on_accept(h2o_socket_t *listener, const char *err)
{
	h2o_socket_t *sock;

	if (err != NULL) {
		return;
	}

	if ((sock = h2o_evloop_socket_accept(listener)) == NULL)
		return;
	h2o_accept(&accept_ctx, sock);
}

static int create_listener(void)
{
	struct sockaddr_in addr;
	int fd, reuseaddr_flag = 1;
	h2o_socket_t *sock;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(0x7f000001);
	addr.sin_port = htons(7890);

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1
		|| setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_flag, sizeof(reuseaddr_flag)) != 0
		|| bind(fd, (struct sockaddr *) &addr, sizeof(addr)) != 0 || listen(fd, SOMAXCONN) != 0) {
		return -1;
	}

	sock = h2o_evloop_socket_create(ctx.loop, fd, H2O_SOCKET_FLAG_DONT_READ);
	h2o_socket_read_start(sock, on_accept);

	return 0;
}

#endif

static int setup_ssl(const char *cert_file, const char *key_file)
{
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();

	accept_ctx.ssl_ctx = SSL_CTX_new(SSLv23_server_method());
	SSL_CTX_set_options(accept_ctx.ssl_ctx, SSL_OP_NO_SSLv2);

	if (USE_MEMCACHED) {
		accept_ctx.libmemcached_receiver = &libmemcached_receiver;
		h2o_accept_setup_async_ssl_resumption(h2o_memcached_create_context("127.0.0.1", 11211, 0, 1,
																		   "h2o:ssl-resumption:"),
											  86400);
		h2o_socket_ssl_async_resumption_setup_ctx(accept_ctx.ssl_ctx);
	}

	/* load certificate and private key */
	if (SSL_CTX_use_certificate_file(accept_ctx.ssl_ctx, cert_file, SSL_FILETYPE_PEM) != 1) {
		fprintf(stderr, "an error occurred while trying to load server certificate file:%s\n",
				cert_file);
		return -1;
	}
	if (SSL_CTX_use_PrivateKey_file(accept_ctx.ssl_ctx, key_file, SSL_FILETYPE_PEM) != 1) {
		fprintf(stderr, "an error occurred while trying to load private key file:%s\n", key_file);
		return -1;
	}

/* setup protocol negotiation methods */
#if H2O_USE_NPN
	h2o_ssl_register_npn_protocols(accept_ctx.ssl_ctx, h2o_http2_npn_protocols);
#endif
#if H2O_USE_ALPN
	h2o_ssl_register_alpn_protocols(accept_ctx.ssl_ctx, h2o_http2_alpn_protocols);
#endif

	return 0;
}

static h2o_pathconf_t *register_handler(h2o_hostconf_t *hostconf, const char *path,
										int (*on_req)(h2o_handler_t *, h2o_req_t *))
{
	h2o_pathconf_t *pathconf = h2o_config_register_path(hostconf, path, 0);
	h2o_handler_t *handler = h2o_create_handler(pathconf, sizeof(*handler));
	handler->on_req = on_req;
	return pathconf;
}

#endif // ARIO_SERVER_H
