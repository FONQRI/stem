#ifndef SERVER_LIBRARY_H
#define SERVER_LIBRARY_H

#include <h2o.h>
#include <map>
#include <string>

namespace Stem::server_library {

std::map<std::string, std::string> get_entities(h2o_req_t *req);

bool if_http_method_not_match(h2o_req_t *req, std::string method);
}; // namespace Stem::server_library

#endif // SERVER_LIBRARY_H
