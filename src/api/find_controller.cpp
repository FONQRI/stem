#include "find_controller.h"

#include <iostream>
#include <string>

#include "collection_methods.h"
#include "reply.h"
#include "server_library.h"

int ario::api::find_controller(h2o_handler_t *self, h2o_req_t *req)
{
	std::clog << __FUNCTION__ << " " << __LINE__ << std::endl;
	static h2o_generator_t generator = {NULL, NULL};

	if (!server_library::if_http_method_not_match(req, "POST")) {
		return -1;
	}

	std::string response;

	//FIXME get this from request
	std::string username;
	std::string database;

	json request; // = json::parse(req->entity.base);
	try {
		request = json::parse(req->entity.base);

	} catch (std::exception &e) {

		//FIXME handle error
		std::clog << e.what();
	}

	json options;
	try {
		options = request["options"];
	} catch (...) {
		//FIXME handle error
	}
	json query;
	try {
		query = request["query"];

	} catch (...) {
		//FIXME handle error
	}

	try {
		//		response = ario::database::find();
	} catch (std::exception &e) {
		//FIXME handle error

		std::clog << e.what() << std::endl;
	}

	// call collection method
	response = ario::database::collection::find(username, database, query, options);

	h2o_iovec_t body = h2o_strdup(&req->pool, response.c_str(), SIZE_MAX);
	req->res.status = 200;
	req->res.reason = "OK";
	h2o_add_header(&req->pool, &req->res.headers, H2O_TOKEN_CONTENT_TYPE, NULL,
				   H2O_STRLIT("text/html"));
	h2o_start_response(req, &generator);
	h2o_send(req, &body, 1, h2o_send_state::H2O_SEND_STATE_FINAL);
	return 0;
}
