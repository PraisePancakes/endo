#pragma once
#include <iostream>

#include "../../include/ndo.hpp"

namespace ndo::test {
void test_compositor() {
    auto value = ndo::compositor::compose([](std::string v) { return (v[0] + v[1]); }, [](int v) { return "hi"; });
    auto v1 = value(3);
    std::cout << v1 << std::endl;

    auto value2 = ndo::compositor::compose([](int x) { return x * 2; }, [](std::string new_s) { return 10; }, [](std::string og) { return "hello"; });
    auto v2 = value2("hi");
    std::cout << v2 << std::endl;
};
}  // namespace ndo::test