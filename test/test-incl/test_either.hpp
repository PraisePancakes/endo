#pragma once
#include <expected>
#include <iostream>

#include "../../include/ndo.hpp"

namespace ndo::test {
void test_either() {
    std::cout << "EITHER\n.\n.\n." << std::endl;
    ndo::either<std::string, int> e;

    e = 4;
    e = "uh oh error";

    if (e.has_value()) {
        std::cout << "has it : " << e.just_or_throw() << std::endl;
    } else {
        std::cout << "doesnt have it : " << e.error_or_default() << std::endl;
    };

    auto v = e.and_then([](int x) { return "hi"; }).and_then([](const char* v) { return 10; });

    std::cout << "HERE : " << v.just_or(0) << std::endl;
    std::cout << "\n.\n.\n.\nEND EITHER" << std::endl;
};
};  // namespace ndo::test