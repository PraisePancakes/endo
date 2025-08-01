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
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::append<float>::type, ndo::type_multiset<int, char, bool, float>>);
    static_assert(!std::is_same_v<ndo::type_multiset<int, char, bool>::append<float>::type, ndo::type_multiset<int, char, bool, int>>);
    static_assert(std::is_same_v<ndo::type_multiset<int, char, bool>::prepend<float>::type, ndo::type_multiset<float, int, char, bool>>);
    static_assert(!std::is_same_v<ndo::type_multiset<int, char, bool>::prepend<float>::type, ndo::type_multiset<bool, int, char, bool>>);

    using from_tup = std::tuple<int, char, bool>;
    using from_tup1 = std::tuple<char, bool, float>;

    static_assert(!ndo::type_multiset<from_tup>::contains<float>);
    static_assert(ndo::type_multiset<from_tup>::contains<int>);
    using t = ndo::type_multiset<from_tup, from_tup1>;
    static_assert(std::is_same_v<t::get<0>, int>);
    static_assert(std::is_same_v<t::get<1>, char>);
    static_assert(std::is_same_v<t::get<2>, bool>);
    static_assert(std::is_same_v<t::get<3>, char>);
    static_assert(std::is_same_v<t::get<4>, bool>);
    static_assert(std::is_same_v<t::get<5>, float>);
    static_assert(std::is_same_v<t::pop_front, ndo::type_multiset<char, bool, char, bool, float>>);

    constexpr auto idx = ndo::type_multiset<int, char>::index<bool>;
    constexpr auto idx2 = ndo::type_multiset<int, char>::index<int>;
    static_assert(idx == -1);
    static_assert(idx2 == 0);

    using v = type_multiset<int, char, bool>::pop_back;

    using reverse = type_multiset<int, char, float>::reverse;

    using l = type_multiset<int, char, bool, float>::splicer::at<2>::left;
    using r = type_multiset<int>::splicer::at<0>::right;

    using from_empty = type_multiset<>::append<int>::type::prepend<bool, char>::type;

    static_assert(type_multiset<int, char, std::string, bool>::contains_from<1, bool>);
    static_assert(type_multiset<int, char, std::string, bool>::contains_from<0, int>);
    static_assert(!type_multiset<int, char, std::string, bool>::contains_from<3, int>);
    static_assert(!type_multiset<int, char, int, bool>::is_unique);
    static_assert(type_multiset<int, char, bool>::is_unique == true);
    static_assert(type_multiset<int>::is_unique);

    using fre = type_multiset<char, int, char, bool, int>::unique;
   
};
}  // namespace ndo::test