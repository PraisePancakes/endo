#pragma once
#include <tuple>

#include "../../include/ndo.hpp"
namespace ndo::test {
void test_type_multiset() {
    static_assert(!ndo::type_multiset<int, char, bool>::contains<float>);
    static_assert(ndo::type_multiset<int, char, bool>::contains<int>);
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::get<2>, bool>);
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::get<1>, char>);
    static_assert(!std::is_same_v<ndo::type_multiset<int, char, bool>::get<1>, int>);
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::append<float>, ndo::type_multiset<int, char, bool, float>>);
    static_assert(!std::is_same_v<ndo::type_multiset<int, char, bool>::append<float>, ndo::type_multiset<int, char, bool, int>>);
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::prepend<float>, ndo::type_multiset<float, int, char, bool>>);
    static_assert(!std::is_same_v<ndo::type_multiset<int, char, bool>::prepend<float>, ndo::type_multiset<bool, int, char, bool>>);

    using from_tup = std::tuple<int, char, bool>;

    static_assert(!ndo::type_multiset<from_tup>::contains<float>);
    static_assert(ndo::type_multiset<from_tup>::contains<int>);
};
}  // namespace ndo::test