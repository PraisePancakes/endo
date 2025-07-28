#pragma once
#include <functional>
#include <iostream>

namespace ndo {
/*
Y ≡ λf.((λf'.f(λx.f'f'x)) (λf'.f(λx.f'f'x)) )
*/

namespace internal {
template <typename F>
class [[nodiscard]] y_ready {
    F f;

   public:
    explicit constexpr y_ready(F&& f) : f(std::forward<F>(f)) {};
    template <typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) noexcept {
        return f(*this, std::forward<Args>(args)...);
    }
    ~y_ready() = default;
};
}  // namespace internal

template <typename F>
[[nodiscard]] constexpr decltype(auto) make_y_combinator(F&& f) {
    return internal::y_ready<std::decay_t<F>>(std::forward<F>(f));
};


};  // namespace ndo