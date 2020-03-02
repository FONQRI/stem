#include "runtime/user.h"

stem::user::user(json input)
	: type(input)
{}

json stem::user::to_json()
{
	return {};
}
