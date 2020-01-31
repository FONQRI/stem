#include <numeric>
#include <random>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

namespace random_string {
    
namespace impl {
    
class randomer {
    // random seed by default
    std::mt19937 gen_;
    std::uniform_int_distribution<size_t> dist_;
    
public:
	randomer() : randomer(0, std::numeric_limits<size_t>::max(), std::random_device{}()) {
    }

    // convenience ctor
	explicit randomer(size_t max)
		: randomer(0, max, std::random_device{}()) {
    }
    
	randomer(size_t min, size_t max, unsigned int seed = std::random_device{}())
        : gen_{seed}, dist_{min, max} {
    }

    // if you want predictable numbers
    void SetSeed(unsigned int seed) {
        gen_.seed(seed);
    }

    size_t operator()() {
        return dist_(gen_);
	}
};

// you can set alphabet here
static std::vector<char> alphabet{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                                  'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                  'k', 'l', 'm', 'n','o','p', 'q', 'r', 's', 't', 'u', 'v',
                                  'w', 'x', 'y', 'z'};
// alpha-numeric example:
//static std::vector<char> alpha_num{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
//                                   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
//                                   'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
//                                   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
//                                   'k', 'l', 'm', 'n','o','p', 'q', 'r', 's', 't', 'u', 'v',
//                                   'w', 'x', 'y', 'z'};
// static std::vector<char> alpha_min{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
//                                    'k', 'l', 'm', 'n','o','p', 'q', 'r', 's', 't', 'u', 'v',
//                                    'w', 'x', 'y', 'z'}

// add seed as second parametr if you want
static randomer randomer{alphabet.size() - 1};

}  // namespace impl

std::string generate_string(size_t len) {
    std::string str;
    auto rand_char = [](){ return impl::alphabet[impl::randomer()]; };
    std::generate_n(std::back_inserter(str), len, rand_char);
    return str;
}


// test example:
void Test(size_t str_len) {
    // randomer.SetSeed(777);  // another option to set seed
	auto str = generate_string(str_len);
	std::cout << str << std::endl;
    /*
     * Test your function for example ...
     */
}
    
}  // namespace random_string

// Usage example:

// ======== main.cpp =======

// #include "random_string.h"

// int main() {
//     random_string::Test(10);
//     auto str = random_string::GenerateString(100);
//     std::cout << str << "\n";
//     return 0;
// }
