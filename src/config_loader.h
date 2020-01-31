#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <filesystem>
#include <string>

#include <boost/serialization/singleton.hpp>
#include <yaml-cpp/yaml.h>

class config_loader;
using cl = config_loader;

class config_loader : public boost::serialization::singleton<config_loader>
{
public:
	void init();
	void init(std::filesystem::path config);

public:
	static YAML::Node config;

private:
	//		config_loader();
	bool load(std::filesystem::path path);
};

#endif // CONFIG_LOADER_H
