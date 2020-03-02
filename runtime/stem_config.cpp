#include "runtime/stem_config.h"

#include <fstream>
#include <iostream>

#include "runtime/random_string.h"

void stem_config::init()
{

	config["security"]["random_string"] = random_string::generate_string(256);
	config["security"]["algorithm"] = "HS256";

	std::ofstream fout("config.yaml");
	fout << config;
	fout.close();

	//NOTE for json export
	//	YAML::Emitter out;
	//	out << YAML::DoubleQuoted << YAML::Flow << config;
	//	std::cout << "Here's the output YAML:\n" << out.c_str() << std::endl; // prints "Hello, World!"
}

void stem_config::init(std::filesystem::path config)
{
	load(config);
}

std::string stem_config::random_string_key()
{
	return config["security"]["random_string"].as<std::string>();
}

std::string stem_config::jwt_algorithm()
{
	return config["security"]["algorithm"].as<std::string>();
}

bool stem_config::load(std::filesystem::path path)
{

	config = YAML::LoadFile(path);
	if (config.IsNull())
	{
		throw std::runtime_error("config is empty");
	}

	if (config["security"]["random_string"].as<std::string>().empty())
	{
		throw std::runtime_error("Please add random_string in config file");
	}

	//	if (config["lastLogin"]) {
	//		std::cout << "Last logged in: " <<
	// config["lastLogin"].as<DateTime>() << "\n";
	//	}

	//	const std::string username = config["username"].as<std::string>();
	//	const std::string password = config["password"].as<std::string>();
	//	login(username, password);
	//	config["lastLogin"] = getCurrentDateTime();

	//	std::ofstream fout("config.yaml");
	//	fout << config;
	return true;
}

YAML::Node stem_config::config;
