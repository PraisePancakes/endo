#pragma once
#include <utility>
/// \ingroup functional
/// \brief Namespace for functional utilities.
namespace ndo {

/**
 * \class compositor
 * \brief Utility for composing functions and threading computations.
 *
 * Provides static methods to compose multiple functions
 * and to thread a value through functions in order.
 *
 * Usage examples:
 * \code
 * auto f = [](int x) { return x + 1; };
 * auto g = [](int x) { return x * 2; };
 * auto h = ndo::compositor::compose(f, g);  // h(x) = f(g(x))
 * int result = h(3); // (3 * 2) + 1 = 7
 *
 * auto t = ndo::compositor::thread_first(f, g);
 * int r2 = t(3); // g(f(3)) = (3 + 1) * 2 = 8
 * \endcode
 */
struct compositor {
    /// Compose a single function (base case)
    template <typename F>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f) {
        return std::forward<F>(f);
    }

    /// Compose multiple functions: compose(f, g, h) => f(g(h(x)))
    template <typename F, typename G, typename... Fs>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f, G&& g, Fs&&... fs) {
        return compose(std::forward<F>(f), compose(std::forward<G>(g), std::forward<Fs>(fs)...));
    }

    /// Compose two functions: compose(f, g)(x) = f(g(x))
    template <typename F, typename G>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f, G&& g) {
        return [_f = std::forward<F>(f), _g = std::forward<G>(g)](auto&& x) -> decltype(auto) {
            return _f(_g(std::forward<decltype(x)>(x)));
        };
    }

    /// Thread-first composition: thread_first(f, g, ...) = g(...(f(x)))
    template <typename F, typename G, typename... Fs>
    [[nodiscard]] constexpr static decltype(auto) thread_first(F&& f, G&& g, Fs&&... fs) {
        return compose(compose(std::forward<Fs>(fs)..., std::forward<G>(g)), std::forward<F>(f));
    }
};

}  // namespace ndo
