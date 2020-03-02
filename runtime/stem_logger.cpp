#include "runtime/stem_logger.h"

#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>

void stem::log::manual_logging()
{
	src::severity_logger<boost::log::trivial::severity_level> slg;

	logging::record rec = slg.open_record(
		keywords::severity = boost::log::trivial::severity_level::trace);
	if (rec)
	{
		logging::record_ostream strm(rec);
		strm << "A regular message";
		strm.flush();
		slg.push_record(boost::move(rec));
	}
}

void stem::log::init_logging(std::filesystem::path log_file_name)
{
	logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

	logging::add_file_log(keywords::file_name = log_file_name,
						  keywords::format
						  = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] "
							"%Message%");

	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);

	//	logging::core::get()->add_global_attribute("MyAttr", attrs::constant<int>(42));
	//	logging::core::get()->add_global_attribute("CountDown", attrs::counter<int>(1, -1));

	logging::add_common_attributes();
}
