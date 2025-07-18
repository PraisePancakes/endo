#pragma once
#include <array>
#include <numeric>

#include "../../include/ndo.hpp"
namespace ndo::test {

void test_maybe() {
    // constexpr tests
    constexpr static ndo::maybe<int> may;
    static_assert(!may);

    constexpr static ndo::maybe<int> may2;
    static_assert(!may2.has_value());

    constexpr static ndo::maybe<int> may3{10};
    static_assert(may3);

    constexpr static ndo::maybe<int> may4{10};
    static_assert(may4.has_value());

    // constexpr map_or_default
    constexpr ndo::maybe<const char*> may6("hello world!");
    static_assert(may6.has_value());

    constexpr auto lam2 = [](const char* v) constexpr { return 4; };
    static_assert(may6.map_or_default(lam2) == 4);
    static_assert(may6.map_or_default(lam2) != 5);

    // map (unwrap) tests
    ndo::maybe<int> may5{10};
    auto lam = [](int x) { return "hello"; };
    std::string ctad = may5.map_or_throw(lam);
    std::size_t strict = may5.map_or_throw<std::string>(lam).size();
    std::cout << ctad << " : " << strict << std::endl;

    ndo::maybe<std::vector<int>> may7{{56, 1, 2, 3}};

    auto lam3 = [](std::vector<int> v) {
        return 4;
    };

    auto lam4 = [](int v) {
        return ndo::ndo_nothing;
    };

    auto v = may7.and_then(lam3).and_then(lam4).and_then(lam4);

    std::cout << std::boolalpha << v.has_value() << std::endl;
};

}  // namespace ndo::test