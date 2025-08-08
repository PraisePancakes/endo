#pragma once
#include <functional>
#include <iostream>
/// \ingroup functional
/// \brief Namespace for functional utilities.
namespace ndo {

/**
 * \brief Y Combinator utility to enable anonymous recursion for lambdas.
 *
 * The Y combinator allows defining recursive lambdas without naming the lambda.
 *
 * \code
 * auto factorial = ndo::make_y_combinator([](auto self, int n) -> int {
 *     return n <= 1 ? 1 : n * self(n - 1);
 * });
 * int result = factorial(5); // 120
 * \endcode
 *
 * @tparam F The type of the callable to enable recursion on.
 * @param f The callable (usually a lambda) that accepts itself as the first argument.
 * @return A callable that supports recursion via the first argument.
 */
namespace internal {
/*
Y ≡ λf.((λf'.f(λx.f'f'x)) (λf'.f(λx.f'f'x)) )
*/
template <typename F>
class [[nodiscard]] y_ready {
    F f;

   public:
    explicit constexpr y_ready(F&& f) : f(std::forward<F>(f)) {}

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
}

}  // namespace ndo
