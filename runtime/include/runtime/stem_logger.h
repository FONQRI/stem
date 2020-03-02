#ifndef STEM_LOGGER_H
#define STEM_LOGGER_H


#include <filesystem>
#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

#define stem_trace BOOST_LOG_TRIVIAL(trace)
#define stem_debug BOOST_LOG_TRIVIAL(debug)
#define stem_info BOOST_LOG_TRIVIAL(info)
#define stem_warning BOOST_LOG_TRIVIAL(warning)
#define stem_error BOOST_LOG_TRIVIAL(error)
#define stem_fatal BOOST_LOG_TRIVIAL(fatal)

namespace stem::log
{
namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

/**
 * @brief stem::log::manual_logging : for logging withut macros
 */
void manual_logging();
/**
 * @brief init_logging
 * @param log_file_name
 */
void init_logging(std::filesystem::path log_file_name = "log.txt");

} // namespace stem::log


#endif // STEM_LOGGER_H
