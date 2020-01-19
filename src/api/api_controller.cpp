#include "api_controller.h"

#include <iostream>
#include <string>

#include "server_library.h"

//fonqri::api::database::opration op;
int ario::api::api_controller(h2o_handler_t *self, h2o_req_t *req)
{
	static h2o_generator_t generator = {NULL, NULL};

	if (!server_library::if_http_method_not_match(req, "POST"))
		return -1;

	std::string response;

	json request = json::parse(req->entity.base);

	json query = request["query"];
	json options = request["options"];

	try {
		//		response = op.handler("test", "myCollection", "delete_many", req->entity.base);
	} catch (std::exception &e) {
		std::clog << e.what() << std::endl;
	}

	h2o_iovec_t body = h2o_strdup(&req->pool, response.c_str(), SIZE_MAX);
	req->res.status = 200;
	req->res.reason = "OK";
	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
				   H2O_STRLIT("text/html"));
	h2o_start_response(req, &generator);
	h2o_send(req, &body, 1, h2o_send_state::H2O_SEND_STATE_FINAL);
	return 0;
}
