#pragma once
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>
/// \ingroup functional
/// \brief Namespace for functional utilities.
namespace ndo {

/**
 * \brief Curries a callable so it can be invoked with partial arguments in multiple calls.
 *
 * Transforms a callable `f` taking multiple arguments `(int, char, bool)` into a
 * curried callable like `g(int)(char)(bool)`.
 *
 * Example usage:
 * \code
 * auto f = [](int x, char y, bool z) { return x + y + (z ? 1 : 0); };
 * auto curried_f = ndo::curry(f);
 * int result = curried_f(1)('a')(true);
 * \endcode
 *
 * @tparam F Callable type.
 * @param f The callable to curry.
 * @return A curried callable.
 */
namespace internal {

template <typename F, typename... Args>
[[nodiscard]] constexpr decltype(auto) curry_impl(F&& f, std::tuple<Args...>&& args) noexcept(noexcept(std::is_nothrow_invocable_v<F, Args...>)) {
    return [xf = std::forward<F>(f), initial_args = std::move(args)](auto&&... next_args) mutable constexpr {
        auto new_args = std::tuple_cat(initial_args, std::make_tuple(std::forward<decltype(next_args)>(next_args)...));
        if constexpr (std::is_invocable_v<F, Args..., decltype(next_args)...>) {
            return std::apply(std::move(xf), std::move(new_args));
        } else {
            return curry_impl(std::forward<decltype(xf)>(xf), std::forward<decltype(new_args)>(new_args));
        }
    };
}

}  // namespace internal

template <typename F>
[[nodiscard]] constexpr decltype(auto) curry(F&& f) noexcept {
    return internal::curry_impl(std::forward<F>(f), std::tuple<>{});
}

}  // namespace ndo
