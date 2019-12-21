// header
#include "delete_many.h"

// internal
#include "collection_methods.h"
#include "reply.h"

// mongocxx
#include <mongocxx/exception/exception.hpp>

// boost
#include <boost/optional.hpp>

// json
#include <nlohmann/json.hpp>

// std
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

std::string iotdb::controller::delete_many(std::string database_name, std::string collection_name,
										   std::string request_str)
{

	json request{request_str};

	// get reply from database
	return iotdb::database::delete_many(database_name, collection_name, request);
}
