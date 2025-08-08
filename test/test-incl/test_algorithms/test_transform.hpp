#pragma once
#include <algorithm>

#include "../../../include/ndo.hpp"
namespace ndo::test {

void test_transform() {
    std::cout << "MAP FROM" << std::endl;
    std::vector<int> vec{0, 1, 2, 3};
    auto v = ndo::map_from(vec, [](int x) { return x + 2; });
    std::for_each(v.begin(), v.end(), [](int v) { std::cout << v << " , "; });
    std::cout << "\n.\n.\n.END MAP FROM" << std::endl;

    std::cout << "ZIP" << std::endl;

    std::tuple<int, std::string> t1 = std::make_tuple(4, "hi");
    std::tuple<char, bool> t2 = std::make_tuple('a', false);

    auto zipped = ndo::zip(t1, t2);

    std::cout << "ZIPPED\n";
    std::cout << std::get<0>(zipped).first << " " << std::get<1>(zipped).first << " " << std::get<0>(zipped).second << " " << std::get<1>(zipped).second << std::endl;

    auto unzipped = ndo::unzip(zipped);

    std::cout << "UNZIPPED\n";
    std::cout << std::get<0>(unzipped) << " " << std::get<1>(unzipped) << " " << std::get<2>(unzipped) << " " << std::get<3>(unzipped) << std::endl;

    auto fzip = ndo::flat_zip(t1, t2);

    std::cout << "FLAT ZIPPED\n";
    std::cout << std::get<0>(fzip) << " " << std::get<1>(fzip) << " " << std::get<2>(fzip) << " " << std::get<3>(fzip) << std::endl;

    std::cout << "\n.\n.\n.END ZIP" << std::endl;

    auto v3 = ndo::find_if(vec, [](int x) { return x > 2; });

    if (v3.has_value()) {
        std::cout << "HASSSSSITTTTT " << v3.just_or_default() << std::endl;
    }

    auto v4 = ndo::all_of(vec, [](int x) { return x > 1; });
    std::cout << v4.size() << std::endl;

    std::vector<std::vector<std::vector<int>>> vec1{{{0}, {1}, {2}}, {{1}, {2}, {3, 4, 5}}};
    std::vector<int> vec2;
    ndo::flatten(vec1, vec2);
    for (auto e : vec2) {
        std::cout << e << " , ";
    }
};
};  // namespace ndo::test