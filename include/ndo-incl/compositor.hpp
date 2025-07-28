#pragma once
#include "maybe.hpp"
namespace ndo {

struct compositor {
    template <typename F>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f) {
        return std::forward<F>(f);
    }
    template <typename F, typename G, typename... Fs>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f, G&& g, Fs&&... fs) {
        return compose(std::forward<F>(f), compose(std::forward<G>(g), std::forward<Fs>(fs)...));
    }
    // x -> (f(g(x))) => y
    template <typename F, typename G>
    [[nodiscard]] constexpr static decltype(auto) compose(F&& f, G&& g) {
        return [_f = std::forward<F>(f), _g = std::forward<G>(g)](auto&& x) -> decltype(auto) {
            return _f(_g(std::forward<decltype(x)>(x)));
        };
    }

    // x -> (g(f(x))) => y
    template <typename F, typename G, typename... Fs>
    [[nodiscard]] constexpr static decltype(auto) thread_first(F&& f, G&& g, Fs&&... fs) {
        return compose(compose(std::forward<Fs>(fs)..., std::forward<G>(g)), std::forward<F>(f));
    }

    


};
};  // namespace ndo