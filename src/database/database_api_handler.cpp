#include "database_api_handler.h"
#include "collection_methods.h"
#include <iostream>

fonqri::api::database::opration::opration()
{
	function_mapper["delete_many"] = iotdb::database::delete_many;
}

std::string fonqri::api::database::opration::handler(std::string database_name,
													 std::string collection_name,
													 std::string opration, std::string request_str)
{
	std::string reply = function_mapper[opration](database_name, collection_name,
												  json::parse(request_str));

	return reply;
}
