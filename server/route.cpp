#include "server/route.h"

//#include "home_service_handler.hpp"
#include "server/status_404_handler.h"
#include "server/stem_server.hpp"

#include "server/api_controller.h"
#include "server/find_controller.h"

route::route(h2o_hostconf_t *hostconf)
{
	h2o_file_register(h2o_config_register_path(hostconf, "/files/", 0), "resources/doc_root", NULL,
					  NULL, 0);

	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	//	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
	//					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	register_handler(hostconf, "/404", stem::status_404_service_handler);
	register_handler(hostconf, "/api/find", stem::api::find_controller);
	register_handler(hostconf, "/api", stem::api::api_controller);

	//	register_handler(hostconf, "/", stem::home_service_handler);
}
