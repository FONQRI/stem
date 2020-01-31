#include "tocken_controller.h"

#include <iostream>

#include <jwt/jwt.hpp>


std::string tocken_controller::get_tocken(std::string_view name, std::string_view password)
{
	using namespace jwt::params;

	auto key = "secret"; //Secret to use for the algorithm
	//Create JWT object
	jwt::jwt_object obj{algorithm("HS256"),
						payload({{"some", "payload"},
								 {"some1", "payload"},
								 {"some2", "payload"},
								 {"some3", "payload"}}),
						secret(key)};

	//Get the encoded string/assertion
	auto enc_str = obj.signature();
	std::cout << enc_str << std::endl;

	//Decode
	auto dec_obj = jwt::decode(enc_str, algorithms({"HS256"}), secret(key));
	std::cout << dec_obj.header() << std::endl;
	std::cout << dec_obj.payload() << std::endl;

}
