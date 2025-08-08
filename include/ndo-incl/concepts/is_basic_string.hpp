#pragma once
#include <iostream>

namespace ndo {

template <class T>
struct is_basic_string : std::false_type {
};

template <class C, class T, class A>
struct is_basic_string<std::basic_string<C, T, A>> : std::true_type {
};

template <class T>
constexpr bool is_basic_string_v = is_basic_string<T>::value;

}