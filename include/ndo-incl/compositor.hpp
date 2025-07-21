#pragma once
#include "maybe.hpp"
namespace ndo {

template <typename T>
class compositor {
    ndo::maybe<T> value;

   public:
    compositor() : value{} {};
    compositor(T&& t) : value{std::move(t)} {};
    compositor(const T& t) : value(t) {};
    compositor(const compositor& o) : value{std::move(o.value)} {};
    compositor& operator=(const compositor& o) {
        value = o.value;
        return *this;
    };

    compositor& operator=(const T& v) {
        value = v;
        return *this;
    };

    // x -> (f(g(x))) => y

    template <typename F, typename G>
    [[nodiscard]] constexpr decltype(auto) compose(F&& f, G&& g) {
        using first_t = std::invoke_result_t<G, T>;
        ndo::maybe<first_t> first = ndo::maybe<first_t>(value.map_or_throw(std::forward<G>(g)));
        return first.map_or_throw(std::forward<F>(f));
    };

    template <typename F, typename G>
    [[nodiscard]] constexpr decltype(auto) compose_safely(F&& f, G&& g) noexcept {
        using first_t = std::invoke_result_t<G, T>;
        ndo::maybe<first_t> first = ndo::maybe<first_t>(value.map_or_default(std::forward<G>(g)));
        return first.map_or_default(std::forward<F>(f));
    };

    ~compositor() = default;
};

};  // namespace ndo