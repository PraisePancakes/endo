#pragma once
#include <iostream>

#include "function_traits.hpp"
namespace ndo {

// f(int, char, bool) -> (F) => g(int)(char)(bool)
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
};

template <typename F, typename... Args>
[[nodiscard]] constexpr decltype(auto) uncurry_impl(F&& f, std::tuple<Args...>&& args) noexcept(noexcept(std::is_nothrow_invocable_v<F, Args...>)) {
    if constexpr (std::is_invocable_v<F, Args...>) {
        return std::apply(std::forward<F>(f), std::move(args));
    } else {
        return [xf = std::forward<F>(f)](auto&&... args) {
            auto remainder = std::make_tuple(std::forward<decltype(args)>(args)...);
            return uncurry_impl(std::forward<decltype(xf)>(xf), std::move(remainder));
        };
    }
};

}  // namespace internal

template <typename F>
[[nodiscard]] constexpr decltype(auto) curry(F&& f) noexcept {
    return internal::curry_impl(std::forward<F>(f), std::tuple<>{});
};

// uncurry(curr(int)(int)) -> f(int, int)
template <typename F>
[[nodiscard]] constexpr decltype(auto) uncurry(F&& f) noexcept {
    return internal::uncurry_impl(std::forward<F>(f), std::tuple<>{});
};

};  // namespace ndo
