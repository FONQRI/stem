#ifndef STEM_TYPE_H
#define STEM_TYPE_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;


namespace stem {

class type
{
public:
	type(json input);
	virtual ~type() = default;
	virtual json to_json() = 0;
};
}

#endif // STEM_TYPE_H
