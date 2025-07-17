#include <functional>
#include <iostream>
#include <tuple>
#include <variant>

#include "include/ndo.hpp"

int main(int argc, char** argv) {
    using f1_traits = ndo::function_traits<decltype([](bool x) { return 4; })>;
    using f1_ret = f1_traits::return_t;
    using arg_1 = f1_traits::arg_t<0>;
    static_assert(std::is_same_v<arg_1, bool>);
    static_assert(std::is_same_v<f1_ret, int>);

    using f2_traits = ndo::function_traits<std::function<int(char)>>;
    using f2_ret = f2_traits::return_t;
    using arg_2 = f2_traits::arg_t<0>;
    static_assert(std::is_same_v<arg_2, char>);
    static_assert(std::is_same_v<f2_ret, int>);

    constexpr static ndo::maybe<int> may;
    static_assert(!may);

    constexpr static ndo::maybe<int> may2;
    static_assert(!may2.has_value());

    constexpr static ndo::maybe<int> may3{10};
    static_assert(may3);

    constexpr static ndo::maybe<int> may4{10};
    static_assert(may4.has_value());

    static_assert(ndo::ndo_callable<decltype([](bool x) { return 4; })>);
    static_assert(ndo::ndo_callable<std::function<int(char)>>);

    ndo::maybe<int> may5{10};
    auto v = may5.map([](int x) { return "hi"; });

    return 0;
}