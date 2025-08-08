#pragma once
#include <iostream>
#include <string>
#include <type_traits>

namespace ndo {

/**
 * \brief Type trait to detect if a type is a specialization of `std::basic_string`.
 *
 * Primary template defaults to `false`.
 */
template <class T>
struct is_basic_string : std::false_type {};

/**
 * \brief Specialization for `std::basic_string` types sets to `true`.
 */
template <class CharT, class Traits, class Allocator>
struct is_basic_string<std::basic_string<CharT, Traits, Allocator>> : std::true_type {};

/**
 * \brief Helper variable template for `is_basic_string`.
 */
template <class T>
constexpr bool is_basic_string_v = is_basic_string<T>::value;

}  // namespace ndo
