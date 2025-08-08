#pragma once
#include <algorithm>
#include <iostream>

#include "../include/ndo.hpp"
namespace ndo::examples {
void construct_exe() {
    auto ns = ndo::spread(5, 10);
    for (auto e : ns) {
        std::cout << e << std::endl;
    }
};

void map_from_ex() {
    std::vector<int> vec{0, 1, 2, 3};
    auto v = ndo::map_from(vec, [](int x) { return x + 2; });
    std::for_each(v.begin(), v.end(), [](int v) { std::cout << v << std::endl; });
};

void zipp_ex() {
    std::tuple<int, std::string> t1 = std::make_tuple(4, "hi");
    std::tuple<char, bool> t2 = std::make_tuple('a', false);

    auto zipped = ndo::zip(t1, t2);

    std::cout << "ZIPPED\n";
    std::cout << std::get<0>(zipped).first << std::endl;   // 4
    std::cout << std::get<1>(zipped).first << std::endl;   // "hi"
    std::cout << std::get<0>(zipped).second << std::endl;  // a
    std::cout << std::get<1>(zipped).second << std::endl;  // false

    auto unzipped = ndo::unzip(zipped);

    std::cout << "UNZIPPED\n";
    std::cout << std::get<0>(unzipped) << std::endl;
    std::cout << std::get<1>(unzipped) << std::endl;
    std::cout << std::get<2>(unzipped) << std::endl;
    std::cout << std::get<3>(unzipped) << std::endl;

    auto fzip = ndo::flat_zip(t1, t2);

    std::cout << "FLAT ZIPPED\n";
    std::cout << std::get<0>(fzip) << std::endl;  // 4
    std::cout << std::get<1>(fzip) << std::endl;  // a
    std::cout << std::get<2>(fzip) << std::endl;  // "hi"
    std::cout << std::get<3>(fzip) << std::endl;  // false
};

void find_if_ex() {
    std::vector<int> vec{0, 1, 2, 3};
    auto v3 = ndo::find_if(vec, [](int x) { return x > 2; });

    if (v3.has_value()) {
        std::cout << "HASSSSSITTTTT " << v3.just_or_default() << std::endl;
    }
}

void all_of_ex() {
    std::vector<int> vec{0, 1, 2, 3};
    auto v4 = ndo::all_of(vec, [](int x) { return x > 1; });
    std::cout << v4.size() << std::endl;
}

void flatten_ex() {
    std::vector<std::vector<std::vector<int>>> vec1{{{0}, {1}, {2}}, {{1}, {2}, {3, 4, 5}}};
    std::vector<int> vec2;
    ndo::flatten(vec1, vec2);
    for (auto e : vec2) {
        std::cout << e << " , ";
    }
}
}  // namespace ndo::examples