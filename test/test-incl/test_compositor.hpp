#pragma once
#include <iostream>

#include "../../include/ndo.hpp"

namespace ndo::test {
void test_compositor() {
    ndo::compositor<int> v{10};
    auto value = v.compose([](std::string v) { return (v[0] + v[1]); }, [](int v) { return "hi"; });
    std::cout << "composite value : " << value << std::endl;
};
}  // namespace ndo::test