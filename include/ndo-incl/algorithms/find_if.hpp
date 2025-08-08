#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

#include "../algebraic/maybe.hpp"

/// \ingroup algorithms
/// \brief Namespace for generic algorithms.
namespace ndo {

/**
 * \brief Finds the last element in a container that satisfies a predicate.
 *
 * Iterates through the container and returns the **last** value `v` such that `f(v)` is `true`,
 * wrapped in a `maybe<T>`. If no such element is found, returns an empty `maybe`.
 *
 * @tparam F A callable predicate type. Must be invocable with `Cont::value_type` and return `bool`.
 * @tparam Cont A container type that supports range-based for loops.
 *
 * @param cont The input container to search.
 * @param f The predicate function to apply.
 * @return A `maybe<Cont::value_type>` containing the last matching element, or empty if none match.
 *
 * @note This returns the *last* matching value. If you want the first, add a `break` after assignment.
 */
template <typename F, typename Cont>
    requires(std::is_invocable_r_v<bool, F, typename Cont::value_type>)
[[nodiscard]] constexpr static auto find_if(const Cont& cont, F&& f) noexcept {
    using maybe_t = ndo::maybe<typename Cont::value_type>;
    maybe_t mayb;
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            mayb = v;  // Overwrites with last matching value.
        }
    }
    return mayb;
}

}  // namespace ndo
