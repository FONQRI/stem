#include "config_loader.h"

#include <fstream>
#include <iostream>

#include "random_string.h"

void config_loader::init()
{
	config["security"]["random_string"] = random_string::generate_string(256);

	std::ofstream fout("config.yaml");
	fout << config;
	fout.close();
}

void config_loader::init(std::filesystem::path config)
{
	load(config);
}

bool config_loader::load(std::filesystem::path path)
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

YAML::Node config_loader::config;
