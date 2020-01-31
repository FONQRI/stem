#include "database_globals.h"

// TODO remove test code
//#include "security/password.h"

// mongo includes
#include <boost/optional.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

// TODO add indexes
stem::database::database_globals::database_globals()
	: connection_pool{mongocxx::uri{}}
{
	initialize();
}

void stem::database::database_globals::initialize()
{

	//	iotdb::database::database_urls_and_ports = database_urls_and_ports;

	create_indexes();
}

mongocxx::pool::entry stem::database::database_globals::get_connection()
{
	return connection_pool.acquire();
}

mongocxx::stdx::optional<mongocxx::pool::entry> stem::database::database_globals::try_get_connection()
{
	return connection_pool.try_acquire();
}

bool stem::database::database_globals::create_indexes()
{
	auto index_document = bsoncxx::builder::basic::document{};
	auto index_document_phone_number = bsoncxx::builder::basic::document{};
	auto index_document_email = bsoncxx::builder::basic::document{};
	auto index_document_key = bsoncxx::builder::basic::document{};
	index_document.append(kvp("username", 1));
	index_document_phone_number.append(kvp("primary_phone_number", 1));
	index_document_email.append(kvp("primary_email", 1));
	index_document_key.append(kvp("keys.name", 1));

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	mongocxx::collection collection = database["users"];

	// option
	mongocxx::options::index options{};
	options.unique(true);

	// create indexes
	collection.create_index(index_document.view(), options);
	collection.create_index(index_document_phone_number.view(), options);
	collection.create_index(index_document_email.view(), options);
	collection.create_index(index_document_key.view(), options);

	return true;
}

bool stem::database::database_globals::create_pool()
{

	return true;
}
