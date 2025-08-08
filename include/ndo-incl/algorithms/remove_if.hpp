#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and transformations.
namespace ndo {

/**
 * \brief Returns a new container with elements that do **not** satisfy the given predicate.
 *
 * This is the logical inverse of `keep_if`. Elements for which the predicate returns `true`
 * are excluded from the result.
 *
 * @tparam Container A container type with `value_type`, `cbegin/cend`, and `insert(end(), value)`.
 * @tparam Cond A callable predicate that returns `bool` when passed a `value_type`.
 *
 * @param cont The input container to be filtered.
 * @param c The predicate to evaluate for each element.
 * @return A container with only the elements that do **not** satisfy the predicate.
 *
 * @note The container type must support `insert` at `end()`.
 * @note This function is `noexcept` if the predicate is `noexcept`.
 */
template <typename Container, typename Cond>
    requires(std::is_invocable_r_v<bool, Cond, typename Container::value_type>)
[[nodiscard]] constexpr auto remove_if(
    const Container& cont,
    Cond&& c) noexcept(std::is_nothrow_invocable_v<Cond, typename Container::value_type>) {
    Container ret{};
    for (const auto& v : cont) {
        if (!std::invoke(c, v)) {
            ret.insert(ret.end(), v);
        }
    }
    return ret;
}

}  // namespace ndo
