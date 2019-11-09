#ifndef TEMPLATE_FILE_HANDLER_H
#define TEMPLATE_FILE_HANDLER_H

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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

#include "path_libraries.h"
#include <inja/inja.hpp>

// Just for convenience
using namespace inja;
using json = nlohmann::json;
std::string doc_root{"resources/doc_root"};
namespace ario {
std::string template_file_handler(std::string path, json data = json{})
{
	std::clog << __FUNCTION__ << " Path: " << path << std::endl;
	//std::filesystem::current_path().string()
	std::string filename;
	filename += path_libraries::add_slash_at_end(std::filesystem::current_path().string())
				+ doc_root + path_libraries::add_slash_at_end(path.c_str()) + "index.html";

	std::clog << filename << std::endl;

	std::ifstream t;
	std::string str;
	try {
		t.open(filename);

		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	} catch (std::exception &e) {
		std::clog << e.what() << std::endl;
		str = "404";
	}

	if (data.is_null()) {
		return str.c_str();
	}

	return inja::render(str.c_str(), data);

	//	static h2o_generator_t	generator = {NULL, NULL};

	//	if (!h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET")))
	//		return {};

	//	h2o_iovec_t body = h2o_strdup(&req->pool, inja::render(str.c_str(), data).c_str(),
	//								  SIZE_MAX);
	//	req->res.status = 200;
	//	req->res.reason = "OK";
	//	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
	//				   H2O_STRLIT("text/html"));
	//	h2o_start_response(req, &generator);
	//	h2o_send(req, &body, 1, h2o_send_state_t::H2O_SEND_STATE_FINAL);

	//	return 0;
}
} // namespace ario

#endif // TEMPLATE_FILE_HANDLER_H
