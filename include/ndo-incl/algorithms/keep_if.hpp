#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and transformations.
namespace ndo {

/**
 * \brief Filters elements of a container based on a predicate.
 *
 * Returns a new container of the same type, containing only the elements for which
 * the predicate returns `true`. This is similar to `std::copy_if` but uses insertion
 * and returns a new container.
 *
 * @tparam Container A container type with `value_type`, `cbegin/cend`, and `insert(end(), value)`.
 * @tparam Cond A callable predicate type invocable with `Container::value_type` and returning `bool`.
 *
 * @param cont The input container.
 * @param c The predicate to apply to each element.
 * @return A container with elements that satisfy the predicate.
 *
 * @note The function preserves the original order of elements.
 * @note The function is `noexcept` if the predicate is `noexcept`.
 */
template <typename Container, typename Cond>
    requires(std::is_invocable_r_v<bool, Cond, typename Container::value_type>)
[[nodiscard]] constexpr auto keep_if(
    const Container& cont,
    Cond&& c) noexcept(std::is_nothrow_invocable_v<Cond, typename Container::value_type>) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        const auto& v = *it;
        if (std::invoke(c, v)) {
            ret.insert(ret.end(), v);
        }
    }
    return ret;
}

}  // namespace ndo
