#pragma once
#include <iostream>

#include "../../include/ndo.hpp"

namespace ndo::examples {

int sum(int x, int y, int z, int t) { return x + y + z + t; };
int foo(int x, int y) { return x + y; };

void curry_ex() {
    auto v = ndo::curry(sum);

    auto v1 = v(10);
    auto v2 = v1(20);
    auto v3 = v2(10)(5);

    auto ucurr = ndo::uncurry(v1);
    std::cout << "here" << ucurr(1, 2, 2) << std::endl;

    auto v1 = ndo::curry(foo);
    auto c = ndo::uncurry(v1);

    auto ans = c(1, 2);

    std::cout << ans << std::endl;
};

}  // namespace ndo::examples