#ifndef API_CONTROLLER_H
#define API_CONTROLLER_H

#include "database_api_handler.h"
#include <h2o.h>

namespace ario::api {

int api_controller(h2o_handler_t *self, h2o_req_t *req);
}

#endif // API_CONTROLLER_H
