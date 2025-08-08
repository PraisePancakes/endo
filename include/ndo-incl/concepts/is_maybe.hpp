#pragma once
#include <iostream>

namespace ndo {

template <typename T>
struct maybe;

template <typename T>
struct is_maybe_trait : std::false_type {};

template <typename T>
struct is_maybe_trait<maybe<T>> : std::true_type {};

template <typename T>
concept is_maybe = is_maybe_trait<std::decay_t<T>>::value;
}  // namespace ndo