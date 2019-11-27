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

std::string iotdb::controller::delete_many(std::string database_name, std::string collection_name,
										   std::string query_str)
{
	// convert content to json
	bsoncxx::document::value request_document = bsoncxx::from_json(query_str);

	// get query document of request
	bsoncxx::types::b_document query;

	try {
		query = request_document.view()["query"].get_document();
	} catch (std::exception &e) {

		// if element doesn't exist in request document
		if (strcmp(e.what(), "unset document::element") == 0) {
			return core::reply::missing_item_error("query");

		} // check if element type is wrong
		else if (strcmp(e.what(), "expected element "
								  "type k_document")
				 == 0) {
			return core::reply::wrong_item_type("query");
		}
		return core::reply::unknown_error();
	}

	// get collation of request
	// https://docs.mongodb.com/manual/reference/collation/
	boost::optional<bsoncxx::types::b_document> collation;

	try {
		collation = request_document.view()["collation"].get_document();
	} catch (std::exception &e) {

		// element is optional
		// check if element type is wrong
		if (strcmp(e.what(), "expected element "
							 "type k_document")
			== 0) {
			return core::reply::wrong_item_type("collation");
		}
	}

	// get write_concern document of request
	// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
	boost::optional<bsoncxx::types::b_document> write_concern;

	try {
		write_concern = request_document.view()["write_concern"].get_document();
	} catch (std::exception &e) {

		// element is optional
		// check if element type is wrong
		if (strcmp(e.what(), "expected element "
							 "type k_document")
			== 0) {
			return core::reply::wrong_item_type("write_concern");
		}
	}

	// get acknowledge_level from write_concern doc
	boost::optional<std::string> acknowledge_level;

	// get tag from write_concern doc
	boost::optional<std::string> tag;

	// get journal from write_concern doc
	boost::optional<bool> journal;

	// get majority from write_concern doc
	boost::optional<int> majority;

	// get timeout from write_concern doc
	boost::optional<int> timeout;

	// get nodes from write_concern doc
	boost::optional<int> nodes;

	if (write_concern.is_initialized()) {

		try {
			acknowledge_level
				= write_concern.get().view()["acknowledge_level"].get_utf8().value.to_string();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("acknowledge_level");
			}
		}

		// get tag from write_concern doc
		try {
			tag = write_concern.get().view()["tag"].get_utf8().value.to_string();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("tag");
			}
		}

		// get journal from write_concern doc
		try {
			journal = write_concern.get().view()["journal"].get_bool();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("journal");
			}
		}

		// get majority from write_concern doc
		try {
			majority = write_concern.get().view()["majority"].get_int32();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("majority");
			}
		}

		// get timeout from write_concern doc
		try {
			timeout = write_concern.get().view()["timeout"].get_int32();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("timeout");
			}
		}

		// get nodes from write_concern doc
		try {
			nodes = write_concern.get().view()["nodes"].get_int32();
		} catch (std::exception &e) {

			// element is optional
			// check if element type is wrong
			if (strcmp(e.what(), "expected element "
								 "type k_document")
				== 0) {
				return core::reply::wrong_item_type("nodes");
			}
		}
	}

	// get reply from database
	return iotdb::database::delete_many(database_name, collection_name, query, collation,
										acknowledge_level, tag, journal, majority, timeout, nodes);
}
