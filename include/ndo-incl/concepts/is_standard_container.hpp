#pragma once
#include <concepts>
#include <iostream>
#include <iterator>

#include "eraseable.hpp"

namespace ndo {

/**
 * \concept Container
 * \brief Concept that requires a type to fulfill typical container requirements.
 *
 * A type `T` satisfies the `Container` concept if it:
 * - Is `std::regular` and `std::swappable`.
 * - Supports erasing elements of its `value_type` (`Eraseable`).
 * - Has correct member types `reference`, `const_reference`, `iterator`, `const_iterator`, `difference_type`, `size_type`.
 * - Provides iterator functionality with forward iterators.
 * - Supports typical container member functions (`begin`, `end`, `cbegin`, `cend`, `size`, `max_size`, `empty`).
 *
 * @tparam T The container type to check.
 */
template <class T>
concept Container = requires(T a, const T b) {
    requires std::regular<T>;
    requires std::swappable<T>;
    requires Eraseable<typename T::value_type, T>;
    requires std::same_as<typename T::reference, typename T::value_type &>;
    requires std::same_as<typename T::const_reference, const typename T::value_type &>;
    requires std::forward_iterator<typename T::iterator>;
    requires std::forward_iterator<typename T::const_iterator>;
    requires std::signed_integral<typename T::difference_type>;
    requires std::same_as<typename T::difference_type, typename std::iterator_traits<typename T::iterator>::difference_type>;
    requires std::same_as<typename T::difference_type, typename std::iterator_traits<typename T::const_iterator>::difference_type>;

    { a.begin() } -> std::same_as<typename T::iterator>;
    { a.end() } -> std::same_as<typename T::iterator>;
    { b.begin() } -> std::same_as<typename T::const_iterator>;
    { b.end() } -> std::same_as<typename T::const_iterator>;
    { a.cbegin() } -> std::same_as<typename T::const_iterator>;
    { a.cend() } -> std::same_as<typename T::const_iterator>;

    { a.size() } -> std::same_as<typename T::size_type>;
    { a.max_size() } -> std::same_as<typename T::size_type>;
    { a.empty() } -> std::convertible_to<bool>;
};

}  // namespace ndo
