#pragma once
#include <iostream>

#include "../../include/ndo.hpp"

namespace ndo::test {
void test_either() {
    ndo::either<std::string, int> e;

    e = 0;

    if (e.has_value()) {
        std::cout << "has it : " << e.just_or_throw() << std::endl;
    } else {
        std::cout << "doesnt have it : " << e.error_or_default() << std::endl;
    };

    auto v = e.and_then([](int x) { return "hi"; }).and_then([](const char* v) { return 10; });

    std::cout << v.just_or(0) << std::endl;
};
};  // namespace ndo::test