#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <filesystem>
#include <string>

#include <boost/serialization/singleton.hpp>
#include <yaml-cpp/yaml.h>

class stem_config;
using cl = stem_config;

class stem_config : public boost::serialization::singleton<stem_config>
{
public:
	void init();
	void init(std::filesystem::path config);
	static std::string random_string_key();
	static std::string jwt_algorithm();

public:
	static YAML::Node config;

private:
	//		config_loader();
	bool load(std::filesystem::path path);
};

#endif // CONFIG_LOADER_H
