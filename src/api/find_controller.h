#ifndef FIND_CONTROLLER_H
#define FIND_CONTROLLER_H

#include <h2o.h>

namespace stem::api {

int find_controller(h2o_handler_t *self, h2o_req_t *req);
}

#endif // FIND_CONTROLLER_H
