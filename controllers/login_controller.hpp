#ifndef LOGIN_CONTROLLER_H
#define LOGIN_CONTROLLER_H

////#include "html_template_engine_handler.h"
#include "server_library.h"
#include "status_404_handler.h"
#include "template_file_handler.hpp"
#include <h2o.h>
#include <h2o/token.h>
#include <iostream>

namespace ario {
int login_controller(h2o_handler_t *self, h2o_req_t *req)
{
	static h2o_generator_t generator = {NULL, NULL};
	auto entities = server_library::get_entities(req);
	json data;
	data["wrong"] = false;
	if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET"))) {

		//		h2o_iovec_t status_list = {NULL, 0}; /* NULL means we'll show all statuses */
		//		if (req->query_at != SIZE_MAX) {
		//			status_list = h2o_iovec_init(&req->path.base[req->query_at + 1],
		//										 h2o_strstr(req->path.base, req->path.len, "username", 8));
		//		}
		//		std::clog << h2o_contains_token(status_list.base, status_list.len, "username", 8, '=')
		//				  << std::endl;
		//		//		auto username = h2o_req_getenv(req, "username", 8, 0);
		//		//		auto username = h2o_next_token()
		//		//		;h2o_send_inline

		//		//			    get_send_parameters(req->entity.base, req->entity.len, &param);
		//		//				for (size_t i = 0; i < status_list.; i++) {
		//		//				}

	} else if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("POST"))) {

		if (!entities.empty()) {
			// check username and password exsists and are true
			data["wrong"] = true;
		}

		//		std::string entity(req->entity.base, req->entity.len);
		//		std::clog << entity << std::endl;
		//		std::clog << "___________________________" << std::endl;

		//		//		h2o_iovec_t status_list = {NULL, 0}; /* NULL means we'll show all statuses */
		//		//		status_list = h2o_iovec_init(&req->entity.base[0],
		//		//									 h2o_strstr(req->entity.base, req->entity.len, "username", 8));
		//		//		std::clog << __LINE__ << " " << h2o_strstr(req->entity.base, req->entity.len, "username", 8)
		//		//				  << std::endl;
		//		//		std::clog << h2o_contains_token(status_list.base, status_list.len, "username", 8, '=')
		//		//				  << std::endl;
		//		//		std::string st(status_list.base, status_list.len);

		//		//		std::clog << st << std::endl;

		//		return -1;
	}

	std::string path{req->path_normalized.base, req->path_normalized.len};

	std::string res_str = ario::template_file_handler(path, data);

	h2o_iovec_t body = h2o_strdup(&req->pool, res_str.c_str(), SIZE_MAX);
	req->res.status = 200;
	req->res.reason = "OK";
	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
				   H2O_STRLIT("text/html"));
	h2o_start_response(req, &generator);
	h2o_send(req, &body, 1, h2o_send_state::H2O_SEND_STATE_FINAL);

	return 0;
}
}; // namespace ario

#endif // LOGIN_CONTROLLER_H
