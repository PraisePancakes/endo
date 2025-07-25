#pragma once
#include <algorithm>

#include "../../include/ndo.hpp"
namespace ndo::test {

void test_transform() {
    std::vector<int> vec{0, 1, 2, 3};
    auto v = ndo::map_from(vec, [](int x) { return x + 2; });
    std::for_each(v.begin(), v.end(), [](int v) { std::cout << v << std::endl; });
};
};  // namespace ndo::test