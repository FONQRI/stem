#ifndef CONTROLLER_DELETE_MANY_H
#define CONTROLLER_DELETE_MANY_H

#include <string>

namespace iotdb {
namespace controller {

std::string delete_many(std::string database_name, std::string collection_name, std::string query);

} // namespace controller
} // namespace iotdb

#endif // CONTROLLER_DELETE_MANY_H
