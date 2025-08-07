#pragma once
#include <algorithm>

#include "../../../include/ndo.hpp"
namespace ndo::test {

void test_transform() {
    std::vector<int> vec{0, 1, 2, 3};
    auto v = ndo::map_from(vec, [](int x) { return x + 2; });
    std::for_each(v.begin(), v.end(), [](int v) { std::cout << v << std::endl; });

    std::tuple<int, std::string> t1 = std::make_tuple(4, "hi");
    std::tuple<char, bool> t2 = std::make_tuple('a', false);

    auto zipped = ndo::zip(t1, t2);

    std::cout << "ZIPPED\n";
    std::cout << std::get<0>(zipped) << std::endl;  // 4
    std::cout << std::get<1>(zipped) << std::endl;  // 'a'
    std::cout << std::get<2>(zipped) << std::endl;  // "hi"
    std::cout << std::get<3>(zipped) << std::endl;  // false
};
};  // namespace ndo::test