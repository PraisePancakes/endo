#pragma once
#include <iostream>

#include "../algebraic/nothing.hpp"
namespace ndo {

template <typename T>
struct maybe;

template <typename T>
struct is_nothing_trait : std::false_type {};

template <>
struct is_nothing_trait<maybe<ndo_null_t>> : std::true_type {};

template <typename T>
concept is_nothing = is_nothing_trait<std::decay_t<T>>::value;
}  // namespace ndo