#ifndef SERVER_LIBRARY_H
#define SERVER_LIBRARY_H

#include <h2o.h>
#include <map>
#include <string>

namespace server_library {

std::map<std::string, std::string> get_entities(h2o_req_t *req);
};

#endif // SERVER_LIBRARY_H
