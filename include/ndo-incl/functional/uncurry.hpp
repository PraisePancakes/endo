#pragma once
#include <iostream>

namespace ndo {

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
};
}  // namespace internal

// uncurry(curr(int)(int)) -> f(int, int)
template <typename F>
[[nodiscard]] constexpr decltype(auto) uncurry(F&& f) noexcept {
    return internal::uncurry_impl(std::forward<F>(f), std::tuple<>{});
};

}  // namespace ndo
