#pragma once
#include <tuple>

#include "../../include/ndo.hpp"
namespace ndo::test {
void test_type_set() {
    static_assert(!ndo::type_set<int, char, bool>::contains<float>);
    static_assert(ndo::type_set<int, char, bool>::contains<int>);
    static_assert(std::is_same_v<ndo::type_set<int, char, bool>::get<2>, bool>);
    static_assert(std::is_same_v<ndo::type_set<int, char, bool>::get<1>, char>);
    static_assert(!std::is_same_v<ndo::type_set<int, char, bool>::get<1>, int>);
    static_assert(std::is_same_v<ndo::type_set<int, char, bool>::append<float>::type, ndo::type_set<int, char, bool, float>>);
    static_assert(!std::is_same_v<ndo::type_set<int, char, bool>::append<float>::type, ndo::type_set<int, char, bool, int>>);
    static_assert(std::is_same_v<ndo::type_set<int, char, bool>::prepend<float>::type, ndo::type_set<float, int, char, bool>>);
    static_assert(!std::is_same_v<ndo::type_set<int, char, bool>::prepend<float>::type, ndo::type_set<bool, int, char, bool>>);

    using from_tup = std::tuple<int, char, bool>;
    using from_tup1 = std::tuple<char, bool, float>;

    static_assert(!ndo::type_set<from_tup>::contains<float>);

    constexpr auto idx2 = ndo::type_set<int, char>::index<int>;

    static_assert(idx2 == 0);

    using v = ndo::type_set<int, char, bool>::pop_back;

    using reverse = ndo::type_set<int, char, float>::reverse;

    using l = ndo::type_set<int, char, bool, float>::splicer::at<2>::left;
    using r = ndo::type_set<int>::splicer::at<0>::right;

    using from_empty = ndo::type_set<>::append<int>::type::prepend<bool, char>::type;

    static_assert(ndo::type_set<int, char, std::string, bool>::contains_from<1, bool>);
    static_assert(ndo::type_set<int, char, std::string, bool>::contains_from<0, int>);
    static_assert(!ndo::type_set<int, char, std::string, bool>::contains_from<1, int>);
    static_assert(!ndo::type_set<int, char, std::string, bool>::contains_from<3, int>);
    static_assert(!ndo::type_set<int, char, int, bool>::is_unique);
    static_assert(ndo::type_set<int, char, bool>::is_unique == true);
    static_assert(ndo::type_set<int>::is_unique);

    static_assert(std::is_same_v<ndo::type_set<int, char, char, int>::unique, ndo::type_set<int, char>>);
    static_assert(std::is_same_v<ndo::type_set<void, int, void>::unique, ndo::type_set<void, int>>);
    static_assert(!ndo::satisfies_it<[]<std::integral>() {}, std::string>);
    static_assert(ndo::satisfies_it<[]<std::integral>() {}, int>);
    using t = ndo::type_set<int, char, std::string>::filter<[]<std::integral>() {}>;
    static_assert(std::is_same_v<t, ndo::type_set<int, char>>);
};
}  // namespace ndo::test