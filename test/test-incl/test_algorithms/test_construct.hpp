#pragma once
#include <algorithm>

#include "../../include/ndo.hpp"
namespace ndo::test {

void test_construct() {
    auto ns = ndo::spread(5, 10);
    for (auto e : ns) {
        std::cout << e << std::endl;
    }
};
};  // namespace ndo::test