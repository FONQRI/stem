#ifndef PATH_LIBRARIES_H
#define PATH_LIBRARIES_H

#include <string>

class path_libraries
{
public:
	path_libraries();

	static std::string add_slash_at_end(std::string str)
	{
		if (str[str.size() - 1] != '/') {
			str += '/';
		}
		return str;
	}
};

#endif // PATH_LIBRARIES_H
