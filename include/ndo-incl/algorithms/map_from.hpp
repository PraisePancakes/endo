#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and transformations.
namespace ndo {

/**
 * \brief Applies a transformation to each element of a container and returns a container of the same type.
 *
 * Each element is passed to the given function `f`, and the result is inserted into the resulting container.
 * The input and output container must be the same type, which means the result of `f` must be convertible to `Container::value_type`.
 *
 * @tparam Container A container type with `value_type`, `cbegin/cend`, and `insert(end(), value)`.
 * @tparam F A callable that takes `Container::value_type` and returns a value convertible to `Container::value_type`.
 *
 * @param cont The input container.
 * @param f The mapping function to apply to each element.
 * @return A container containing the transformed elements.
 *
 * @note The container must support `insert` at `end()`.
 * @note The function is `noexcept` if the callable `f` is `noexcept`.
 */
template <typename Container, typename F>
    requires(std::is_invocable_v<F, typename Container::value_type>)
[[nodiscard]] constexpr auto map_from(
    const Container& cont,
    F&& f) noexcept(std::is_nothrow_invocable_v<F, typename Container::value_type>) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        const auto& v = *it;
        ret.insert(ret.end(), std::invoke(std::forward<F>(f), v));
    }
    return ret;
}

}  // namespace ndo
