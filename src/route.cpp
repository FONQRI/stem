#include "route.h"

#include "api_controller.h"
#include "ario_server.hpp"
#include "home_service_handler.hpp"
#include "status_404_handler.h"

route::route(h2o_hostconf_t *hostconf)
{
	h2o_file_register(h2o_config_register_path(hostconf, "/files/", 0), "resources/doc_root", NULL,
					  NULL, 0);

	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	//	h2o_file_register(h2o_config_register_path(hostconf, "/favicon.ico", 0),
	//					  "resources/doc_root/favicon.ico", NULL, NULL, 0);

	register_handler(hostconf, "/404", ario::status_404_service_handler);
	register_handler(hostconf, "/api", ario::api::api_controller);

	register_handler(hostconf, "/", ario::home_service_handler);
}
