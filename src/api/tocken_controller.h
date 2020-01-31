#ifndef TOCKEN_CONTROLLER_H
#define TOCKEN_CONTROLLER_H

#include <string>

namespace tocken_controller
{

std::string get_tocken(std::string_view name , std::string_view password);
};

#endif // TOCKEN_CONTROLLER_H
