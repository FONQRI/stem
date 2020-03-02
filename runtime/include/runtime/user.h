#ifndef USER_H
#define USER_H

#include "type.h"
namespace stem {

class user:public stem::type
{
public:
	user(json input);

	// type interface
public:
	json to_json();
};
}

#endif // USER_H
