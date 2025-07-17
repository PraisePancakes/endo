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

    // map (unwrap) tests
    ndo::maybe<int> may5{10};
    auto lam = [](int x) { return "hello"; };

    std::string ctad = may5.map_or_throw(lam);
    std::size_t strict = may5.map_or_throw<std::string>(lam).size();
    std::cout << ctad << " : " << strict << std::endl;

    constexpr ndo::maybe<const char*> may6("hello world!");
    static_assert(may6);
    auto lam2 = [](const char* v) { return 4; };
    auto v = may6.map_or_default(lam2);
    std::cout << v << std::endl;
};

}  // namespace ndo::test