#pragma once
#include <concepts>
#include <functional>
#include <iostream>

namespace ndo {

/**
 * \concept Hashable
 * \brief Concept that requires a type to be hashable by `std::hash`.
 *
 * A type `T` satisfies the `Hashable` concept if `std::hash<T>` is invocable
 * with an instance of `T` and returns a type convertible to `std::size_t`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Hashable = requires(T x) {
    { std::hash<T>{}(x) } -> std::convertible_to<std::size_t>;
};

}  // namespace ndo
