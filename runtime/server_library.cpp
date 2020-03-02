#include "runtime/server_library.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string_view>
#include <vector>

std::map<std::string, std::string> stem::server_library::get_entities(h2o_req_t *req)
{
	std::map<std::string, std::string> ret;
	// TODO handle get
	std::string_view sv;
	if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("GET")))
	{

		h2o_iovec_t status_list = {nullptr, 0}; /* NULL means we'll show all statuses */
		if (req->query_at != SIZE_MAX)
		{
			status_list = h2o_iovec_init(&req->path.base[req->query_at + 1],
										 req->path.len - (req->query_at + 1));
		}
		sv = std::string_view(status_list.base, status_list.len);
	}
	else if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT("POST")))
	{
		sv = std::string_view(req->entity.base, req->entity.len);
	}

	std::vector<std::string> strs;
	boost::split(strs, sv, boost::is_any_of("&"));

	for (std::string_view entity_str : strs)
	{
		std::vector<std::string> entity_strv;
		boost::split(entity_strv, entity_str, boost::is_any_of("="));
		if (entity_strv.size() > 1)
		{
			ret[entity_strv[0]] = entity_strv[1];
		}
	}
	return ret;
}

bool stem::server_library::if_http_method_not_match(h2o_req_t *req, std::string method)
{
	if (h2o_memis(req->method.base, req->method.len, H2O_STRLIT(method.c_str())))
		return false;
	return true;
}
