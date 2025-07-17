#pragma once

#include "../../include/ndo.hpp"
namespace ndo::test {
void test_function_traits() {
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

    static_assert(ndo::ndo_callable<decltype([](bool x) { return 4; })>);
    static_assert(ndo::ndo_callable<std::function<int(char)>>);
    static_assert(!ndo::ndo_callable<int>);
};

};  // namespace ndo::test