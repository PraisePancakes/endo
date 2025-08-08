#pragma once
#include <iostream>
#include <utility>

namespace ndo {

/**
 * \brief Executes a callable `f` with compile-time indices from 0 to N-1.
 *
 * This utility performs a compile-time "for loop" by expanding
 * a parameter pack of indices into a call to `f.template operator()<I...>(args...)`.
 *
 * Example usage:
 * \code
 * struct Foo {
 *     template <std::size_t... I>
 *     void operator()(int x) const {
 *         ((std::cout << "Index: " << I << ", x: " << x << "\n"), ...);
 *     }
 * };
 * ndo::static_for<3>(Foo{}, 42);
 * \endcode
 *
 * @tparam N Number of iterations.
 * @tparam F Callable type with a templated operator().
 * @tparam Args Types of additional arguments to forward.
 * @param f Callable to invoke with the indices.
 * @param args Additional arguments forwarded to the callable.
 */
template <std::size_t N, typename F, typename... Args>
[[nodiscard]] constexpr void static_for(F&& f, Args&&... args) {
    []<std::size_t... I>(std::index_sequence<I...>, F&& f, Args&&... args) constexpr {
        std::forward<F>(f).template operator()<I...>(std::forward<Args>(args)...);
    }(std::make_index_sequence<N>{}, std::forward<F>(f), std::forward<Args>(args)...);
}

}  // namespace ndo
