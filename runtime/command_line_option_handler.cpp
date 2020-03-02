#include "runtime/command_line_option_handler.h"

#include <iostream>
#include <stdlib.h> /* exit, EXIT_FAILURE */

#include <boost/program_options.hpp>

#include "runtime/stem_config.h"
#include "runtime/stem_logger.h"

namespace po = boost::program_options;

command_line_option_handler::command_line_option_handler(int argc, char **argv)
{
	handle_command_line(argc, argv);
}

void command_line_option_handler::handle_command_line(int argc, char **argv)
{

	// Declare a group of options that will be
	// allowed only on command line
	po::options_description generic("Generic options");
	generic.add_options()("version,v", "print version string")("help,h", "produce help message");

	// Declare a group of options that will be
	// allowed both on command line and in
	int opt;
	std::string config_path;
	// config file
	po::options_description config("Configuration");
	config.add_options()("config,c", po::value<std::string>(),
						 "config file")("logfile,l", po::value<std::vector<std::string>>(),
										"log file");

	// Hidden options, will be allowed both on command line and
	// in config file, but will not be shown to the user.
	po::options_description hidden("Hidden options");
	hidden.add_options()("input-file", po::value<std::vector<std::string>>(), "input file");

	po::options_description cmdline_options;
	cmdline_options.add(generic).add(config).add(hidden);

	po::options_description config_file_options;
	config_file_options.add(config).add(hidden);

	po::options_description visible("Allowed options");
	visible.add(generic).add(config);

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, visible), vm);
	po::notify(vm);

	if (vm["logfile"].empty())
	{
		std::clog << "no logfile" << std::endl;
		std::clog << "creating defult logfile saving in log.txt" << std::endl;
		stem::log::init_logging();
	}
	else
	{
		stem::log::init_logging(vm["logfile"].as<std::string>());
		std::clog << "logging into: " << vm["logfile"].as<std::string>() << std::endl;
	}

	if (vm["config"].empty())
	{
		std::clog << "no yaml config file" << std::endl;
		std::clog << "creating defult config file saving in config.yaml" << std::endl;
		cl::get_mutable_instance().init();

		//TODO use a default config
	}
	else
	{

		cl::get_mutable_instance().init(vm["config"].as<std::string>());
		std::clog << vm["config"].as<std::string>() << std::endl;
	}

	if (vm.count("help"))
	{
		std::cout << visible << "\n";
		exit(EXIT_FAILURE);
	}
}
