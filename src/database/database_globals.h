#ifndef DATABASE_GLOBALS_H
#define DATABASE_GLOBALS_H

#include <boost/serialization/singleton.hpp>
#include <mongocxx/pool.hpp>
#include <string>
#include <vector>

namespace iotdb {
namespace database {
class database_globals : public boost::serialization::singleton<database_globals>
{

public:
	database_globals();
	mongocxx::pool::entry get_connection();
	mongocxx::stdx::optional<mongocxx::pool::entry> try_get_connection();

private:
	void initialize();
	static bool create_indexes();
	static bool create_pool();

private:
	mongocxx::pool connection_pool;
};

// std::vector<std::string> m_database_urls_and_ports;
} // namespace database
} // namespace iotdb
#endif // DATABASE_GLOBALS_H
