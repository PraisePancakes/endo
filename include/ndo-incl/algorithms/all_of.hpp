#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

#include "../algebraic/maybe.hpp"

/// \ingroup algorithms
/// \brief Namespace for generic algorithms.
namespace ndo {

/**
 * \brief Filters a container by a predicate.
 *
 * Returns a new container of the same type, containing only elements
 * for which the predicate returns true.
 *
 *
 * @tparam F A callable predicate type. Must be invocable with `Cont::value_type` and return `bool`.
 * @tparam Cont A container type supporting `begin()`, `end()`, and `insert(end(), value)`.
 *
 * @param cont The input container to filter.
 * @param f The predicate function to apply.
 * @return A new container with elements `v` such that `f(v)` is `true`.
 *
 * @note Requires: `std::is_invocable_r_v<bool, F, typename Cont::value_type>` to be satisfied.
 */
template <typename F, typename Cont>
    requires(std::is_invocable_r_v<bool, F, typename Cont::value_type>)
[[nodiscard]] constexpr static auto all_of(const Cont& cont, F&& f) noexcept {
    Cont out{};
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            out.insert(out.end(), v);
        }
    }
    return out;
}

}  // namespace ndo
