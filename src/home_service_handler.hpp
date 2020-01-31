#ifndef HOME_SERVICE_HANDLER_H
#define HOME_SERVICE_HANDLER_H

////#include "html_template_engine_handler.h"
#include "status_404_handler.h"
#include "template_file_handler.hpp"
#include <h2o.h>

namespace stem {
int home_service_handler(h2o_handler_t *self, h2o_req_t *req)
{
	static h2o_generator_t generator = {NULL, NULL};

	if (!h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET")))
		return -1;

	std::string path{req->path_normalized.base, req->path_normalized.len};
	json data;
	data["files_dir"] = "";
	data["name"] = "world";
	data["guests"] = {"Jeff", "Tom", "Patrick", "Patrick1", "Behnam"};

	std::string res_str = stem::template_file_handler(path, data);

	if (res_str == "404") {

		std::string notFound{"http://localhost:80/404"};
		h2o_send_redirect_internal(req, req->method, notFound.c_str(), notFound.size(), 0);
		return 0;
	}

	h2o_iovec_t body = h2o_strdup(&req->pool, res_str.c_str(), SIZE_MAX);
	req->res.status = 200;
	req->res.reason = "OK";
	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
				   H2O_STRLIT("text/html"));
	h2o_start_response(req, &generator);
	h2o_send(req, &body, 1, h2o_send_state::H2O_SEND_STATE_FINAL);

	return 0;
}
////json json_model()
////{
////	json data;
////	data["files_dir"] = "";
////	data["name"] = "world";
////	data["guests"] = {"Jeff", "Tom", "Patrick"};
////	return data;
////}
}; // namespace stem

#endif // HOME_SERVICE_HANDLER_H
