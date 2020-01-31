#include "stem_server.hpp"
#include <filesystem>

#include "route.h"

#include <inja/parser.hpp>
#include <nlohmann/json.hpp>

#include "database/database_globals.h"
/* TODO : list
 * [ ] create a response model in c++ struct to get response string and code and answer in server library and sprate server from implamentation
 * [ ] doument all steps in md files in doc folder
 * [ ] use correct library adding in cmake for project
 * [x] Select a good datamodel
 * [x] select a good library for it
 * [ ] rewite controllers to become sprate from server part(using datamodel for interface)
 * [ ] write h2o handlers for controllers
 * [ ] find good way for auth prodects and database and statices
 * [ ] use connection pool instade of creating one connection er request
 * [ ] update add comments
 *
 *
 *
 *
 *
 *
 *
 */

#include "command_line_option_handler.h"

int main(int argc, char **argv)
{
	command_line_option_handler(argc, argv);

	//	static h2o_globalconf_t config;
	//	static h2o_context_t ctx;
	//	static h2o_multithread_receiver_t libmemcached_receiver;
	//	static h2o_accept_ctx_t accept_ctx;
	stem::database::database_globals::get_mutable_instance();

	h2o_hostconf_t *hostconf;

	signal(SIGPIPE, SIG_IGN);

	h2o_config_init(&config);
	hostconf = h2o_config_register_host(&config, h2o_iovec_init(H2O_STRLIT("default")), 65535);
	route router(hostconf);

#if H2O_USE_LIBUV

	uv_loop_t loop;
	uv_loop_init(&loop);
	h2o_context_init(&ctx, &loop, &config);
#else
	h2o_context_init(&ctx, h2o_evloop_create(), &config);
#endif
	if (USE_MEMCACHED)
		h2o_multithread_register_receiver(ctx.queue, &libmemcached_receiver, h2o_memcached_receiver);

	if (USE_HTTPS && setup_ssl("resources/h2o/server.crt", "resources/h2o/server.key") != 0)
		goto Error;

	/* disabled by default: uncomment the line below to enable access logging */
	/* h2o_access_log_register(&config.default_host, "/dev/stdout", NULL); */

	accept_ctx.ctx = &ctx;
	accept_ctx.hosts = config.hosts;

	if (create_listener() != 0)
	{
		fprintf(stderr, "failed to listen to 127.0.0.1:%d:%s\n", stem::vars::SERVER_PORT,
				strerror(errno));
		goto Error;
	}

#if H2O_USE_LIBUV
	uv_run(ctx.loop, UV_RUN_DEFAULT);
#else
	while (h2o_evloop_run(ctx.loop, INT32_MAX) == 0)
		;
#endif

Error:
	return 1;
}

//log4cpp_____________________________________________________________
//#include "log4cpp/Appender.hh"
//#include "log4cpp/BasicLayout.hh"
//#include "log4cpp/Category.hh"
//#include "log4cpp/FileAppender.hh"
//#include "log4cpp/Layout.hh"
//#include "log4cpp/OstreamAppender.hh"
//#include "log4cpp/Priority.hh"

//int main(int argc, char **argv)
//{
//	log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
//	appender1->setLayout(new log4cpp::BasicLayout());

//	log4cpp::Appender *appender2 = new log4cpp::FileAppender("default", "program.log");
//	appender2->setLayout(new log4cpp::BasicLayout());

//	log4cpp::Category &root = log4cpp::Category::getRoot();
//	root.setPriority(log4cpp::Priority::INFO);
//	root.addAppender(appender1);

//	log4cpp::Category &sub1 = log4cpp::Category::getInstance(std::string("sub1"));
//	sub1.addAppender(appender2);

//	// use of functions for logging messages
//	root.error("root error");
//	root.info("root info");
//	sub1.error("sub1 error");
//	sub1.warn("sub1 warn");

//	// printf-style for logging variables
//	root.warn("%d + %d == %s ?", 1, 1, "two");

//	// use of streams for logging messages
//	root << log4cpp::Priority::ERROR << "Streamed root error";
//	root << log4cpp::Priority::INFO << "Streamed root info";
//	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
//	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

//	// or this way:
//	root.errorStream() << "Another streamed error";

//	return 0;
//}

////_______________________________________________________________
//#include <boost/log/trivial.hpp>

//int main(int, char *[])
//{
//	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
//	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
//	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
//	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
//	BOOST_LOG_TRIVIAL(error) << "An error severity message";
//	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

//	return 0;
//}
