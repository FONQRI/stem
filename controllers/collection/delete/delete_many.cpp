// header
#include "delete_many.h"

// internal
#include "lib/reply.h"
#include "src/database/collection_methods.h"
#include "src/database/security/password.h"

// mongocxx
#include <mongocxx/exception/exception.hpp>

// boost
#include <boost/optional.hpp>

// std
#include <iostream>
#include <string>
#include <vector>

std::string iotdb::controller::delete_many(std::string input)
{

	// get database name and check client_key access
	std::string database_name{};
	std::string check_key_reply;
	if (!iotdb::database::security::password::check_key(username, client_key, check_key_reply)) {
		rep.content.append(check_key_reply.c_str(), check_key_reply.size());
		return;
	} else {
		database_name = check_key_reply;
	}

	// convert content to json
	bsoncxx::document::value request_document = bsoncxx::from_json(request.content);

	// get query document of request
	bsoncxx::types::b_document query;

	try {
		query = request_document.view()["query"].get_document();
	} catch (std::exception &e) {

		// if element doesn't exist in request document
		if (strcmp(e.what(), "unset document::element") == 0) {
			std::string reply = core::reply::missing_item_error("query");
			rep.content.append(reply.c_str(), reply.size());
		} // check if element type is wrong
		else if (strcmp(e.what(), "expected element "
								  "type k_document")
				 == 0) {
			std::string reply = core::reply::wrong_item_type("query");
			rep.content.append(reply.c_str(), reply.size());
		}
		return;
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
			std::string reply = core::reply::wrong_item_type("collation");
			rep.content.append(reply.c_str(), reply.size());
			return;
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
			std::string reply = core::reply::wrong_item_type("write_concern");
			rep.content.append(reply.c_str(), reply.size());
			return;
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
				std::string reply = core::reply::wrong_item_type("acknowledge_level");
				rep.content.append(reply.c_str(), reply.size());
				return;
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
				std::string reply = core::reply::wrong_item_type("tag");
				rep.content.append(reply.c_str(), reply.size());
				return;
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
				std::string reply = core::reply::wrong_item_type("journal");
				rep.content.append(reply.c_str(), reply.size());
				return;
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
				std::string reply = core::reply::wrong_item_type("majority");
				rep.content.append(reply.c_str(), reply.size());
				return;
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
				std::string reply = core::reply::wrong_item_type("timeout");
				rep.content.append(reply.c_str(), reply.size());
				return;
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
				std::string reply = core::reply::wrong_item_type("nodes");
				rep.content.append(reply.c_str(), reply.size());
				return;
			}
		}
	}

	// get reply from database
	auto reply = iotdb::database::delete_many(username, database_name, query, collation,
											  acknowledge_level, tag, journal, majority, timeout,
											  nodes);

	// write reply
	rep.content.append(reply.c_str(), reply.size());
}
