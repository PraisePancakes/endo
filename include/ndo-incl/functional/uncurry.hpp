#pragma once
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
/// \ingroup functional
/// \brief Namespace for functional utilities.
namespace ndo {

/**
 * \brief Transforms a curried callable into a callable accepting all arguments at once.
 *
 * Converts a curried function `f` like `f(int)(int)` into a function
 * `g(int, int)`.
 *
 * Example usage:
 * \code
 * auto curried_add = [](int x) {
 *     return [x](int y) {
 *         return x + y;
 *     };
 * };
 * auto uncurried_add = ndo::uncurry(curried_add);
 * int result = uncurried_add(1, 2); // 3
 * \endcode
 *
 * @tparam F Curried callable type.
 * @param f The curried callable.
 * @return A callable accepting all arguments at once.
 */
namespace internal {

template <typename F, typename... Args>
[[nodiscard]] constexpr decltype(auto) uncurry_impl(F&& f, std::tuple<Args...>&& args) noexcept(
    noexcept(std::is_nothrow_invocable_v<F, Args...>)) {
    if constexpr (std::is_invocable_v<F, Args...>) {
        return std::apply(std::forward<F>(f), std::move(args));
    } else {
        return [xf = std::forward<F>(f)](auto&&... args) {
            auto remainder = std::make_tuple(std::forward<decltype(args)>(args)...);
            return uncurry_impl(std::forward<decltype(xf)>(xf), std::move(remainder));
        };
    }
}

}  // namespace internal

template <typename F>
[[nodiscard]] constexpr decltype(auto) uncurry(F&& f) noexcept {
    return internal::uncurry_impl(std::forward<F>(f), std::tuple<>{});
}

}  // namespace ndo
