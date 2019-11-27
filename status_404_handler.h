#ifndef STATUS_404_HANDLER_H
#define STATUS_404_HANDLER_H

////#include "html_template_engine_handler.h"
#include "template_file_handler.hpp"

namespace ario {
int status_404_service_handler(h2o_handler_t *self, h2o_req_t *req)
{
	static h2o_generator_t generator = {NULL, NULL};

	if (!h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET")))
		return -1;

	std::string path{req->path_normalized.base, req->path_normalized.len};
	json data;
	data["files_dir"] = "";
	data["name"] = "world";
	data["guests"] = {"Jeff", "Tom", "Patrick", "Patrick1", "Behnam"};

	std::string res_str = ario::template_file_handler("/404", data);
	h2o_iovec_t body = h2o_strdup(&req->pool, res_str.c_str(), SIZE_MAX);
	req->res.status = 404;
	req->res.reason = "File not found";
	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
				   H2O_STRLIT("text/html"));
	h2o_start_response(req, &generator);
	h2o_send(req, &body, 1, h2o_send_state::H2O_SEND_STATE_ERROR);

	return 0;
}
} // namespace ario

#endif // STATUS_404_HANDLER_H
