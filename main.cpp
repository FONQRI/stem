#include "ario_server.hpp"
#include <filesystem>

#include "controllers/login_controller.hpp"
#include "home_service_handler.hpp"
#include "template_file_handler.hpp"

#include <inja/parser.hpp>

int main(int argc, char **argv)
{

	//	static h2o_globalconf_t config;
	//	static h2o_context_t ctx;
	//	static h2o_multithread_receiver_t libmemcached_receiver;
	//	static h2o_accept_ctx_t accept_ctx;

	h2o_hostconf_t *hostconf;

	signal(SIGPIPE, SIG_IGN);

	h2o_config_init(&config);
	hostconf = h2o_config_register_host(&config, h2o_iovec_init(H2O_STRLIT("default")), 65535);
	h2o_file_register(h2o_config_register_path(hostconf, "/files/", 0), "resources/doc_root", NULL,
					  NULL, 0);

	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	//	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
	//					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	register_handler(hostconf, "/login", ario::login_controller);
	register_handler(hostconf, "/404", ario::status_404_service_handler);
	register_handler(hostconf, "/", ario::home_service_handler);
#if H2O_USE_LIBUV

	uv_loop_t loop;
	uv_loop_init(&loop);
	h2o_context_init(&ctx, &loop, &config);
#else
	h2o_context_init(&ctx, h2o_evloop_create(), &config);
#endif
	if (USE_MEMCACHED)
		h2o_multithread_register_receiver(ctx.queue, &libmemcached_receiver, h2o_memcached_receiver);

	if (USE_HTTPS && setup_ssl("resources/h2o/server.crt", "resources/h2o/server.key") != 0)
		goto Error;

	/* disabled by default: uncomment the line below to enable access logging */
	/* h2o_access_log_register(&config.default_host, "/dev/stdout", NULL); */

	accept_ctx.ctx = &ctx;
	accept_ctx.hosts = config.hosts;

	if (create_listener() != 0) {
		fprintf(stderr, "failed to listen to 127.0.0.1:%d:%s\n", ario_vars::SERVER_PORT,
				strerror(errno));
		goto Error;
	}

#if H2O_USE_LIBUV
	uv_run(ctx.loop, UV_RUN_DEFAULT);
#else
	while (h2o_evloop_run(ctx.loop, INT32_MAX) == 0)
		;
#endif

Error:
	return 1;
}
