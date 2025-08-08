#pragma once
#include <iostream>
#include <type_traits>

#include "../algebraic/nothing.hpp"

namespace ndo {

/**
 * \brief Forward declaration of `maybe` template.
 */
template <typename T>
struct maybe;

/**
 * \brief Type trait to detect if a type is `maybe<ndo_null_t>`.
 *
 * Primary template defaults to `false`.
 */
template <typename T>
struct is_nothing_trait : std::false_type {};

/**
 * \brief Specialization for `maybe<ndo_null_t>` sets to `true`.
 */
template <>
struct is_nothing_trait<maybe<ndo_null_t>> : std::true_type {};

/**
 * \concept is_nothing
 * \brief Concept that checks if a type is `maybe<ndo_null_t>`.
 */
template <typename T>
concept is_nothing = is_nothing_trait<std::decay_t<T>>::value;

}  // namespace ndo
