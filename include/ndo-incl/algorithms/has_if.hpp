#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and predicates.
namespace ndo {

/**
 * \brief Checks if any element in a container satisfies a predicate.
 *
 * Iterates over the container and returns `true` if the predicate returns `true`
 * for at least one element.
 *
 * Equivalent to `std::any_of` but with stricter type constraints and noexcept handling.
 *
 * @tparam F A callable predicate type. Must be invocable with `Container::value_type` and return `bool`.
 * @tparam Container A container type supporting range-based for loops.
 *
 * @param cont The container to search.
 * @param f The predicate function to apply to each element.
 * @return `true` if any element matches the predicate, otherwise `false`.
 *
 * @note This function short-circuits on the first matching element.
 * @note The function is `noexcept` if the predicate is `noexcept`.
 */
template <typename F, typename Container>
    requires(std::is_invocable_r_v<bool, F, typename Container::value_type>)
[[nodiscard]] constexpr static bool has_if(
    const Container& cont,
    F&& f) noexcept(std::is_nothrow_invocable_r_v<F, typename Container::value_type>) {
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            return true;
        }
    }
    return false;
}

}  // namespace ndo
