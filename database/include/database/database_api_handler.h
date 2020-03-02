#ifndef DATABASE_API_HANDLER_H
#define DATABASE_API_HANDLER_H

#include <map>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace fonqri::api::database {

typedef std::string opration_func(std::string database_name, std::string collection_name,
								  json request_str);
typedef std::map<std::string, opration_func *> opration_function_mapper;

class opration
{
public:
	opration();
	std::string handler(std::string database_name, std::string collection_name,
						std::string opration, std::string request_str);

	opration_function_mapper function_mapper;
};

} // namespace fonqri::api::database

#endif // DATABASE_API_HANDLER_H
