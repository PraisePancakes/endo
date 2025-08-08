#pragma once
#include <iostream>
#include <type_traits>

namespace ndo {

/**
 * \brief Forward declaration of `maybe` template.
 */
template <typename T>
struct maybe;

/**
 * \brief Type trait to detect if a type is an instantiation of `maybe`.
 *
 * Primary template defaults to `false`.
 */
template <typename T>
struct is_maybe_trait : std::false_type {};

/**
 * \brief Specialization for `maybe<T>` sets to `true`.
 */
template <typename T>
struct is_maybe_trait<maybe<T>> : std::true_type {};

/**
 * \concept is_maybe
 * \brief Concept that checks if a type is a `maybe` instantiation.
 *
 * Matches types that decay to `maybe<T>`.
 */
template <typename T>
concept is_maybe = is_maybe_trait<std::decay_t<T>>::value;

}  // namespace ndo
