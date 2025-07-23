#pragma once
#include "../../include/ndo.hpp"
namespace ndo::test {

int sum(int x, int y, int z, int t) { return x + y + z + t; };
void test_curry() {
    auto v = ndo::curry(sum);
    auto v1 = v(10);
    auto v2 = v1(20);
    auto v3 = v2(10)(5);

    std::cout << v3;
};
};  // namespace ndo::test