#pragma once
#include <variant>

#include "visitor.hpp"
namespace ndo {

struct NDO_NOTHING_TYPE {
};

template <typename T>
class maybe {
    std::variant<NDO_NOTHING_TYPE, T> var;

   public:
    constexpr maybe() : var(NDO_NOTHING_TYPE{}) {};
    constexpr maybe(T&& v) : var(std::move(v)) {};
    constexpr maybe(const T& o) : var(o.var) {};

    explicit constexpr operator bool() const {
        return std::visit(visitor{[](NDO_NOTHING_TYPE) { return false; }, [](T) { return true; }}, var);
    };

    constexpr bool has_value() const {
        return (*this).operator bool();
    };

    const T& just_or_throw() const {
        if (has_value()) {
            return std::get<T>(var);
        }
        throw std::runtime_error("maybe just_safe exception");
    };

    T& just_or_throw() {
        if (has_value()) {
            return std::get<T>(var);
        }
        throw std::runtime_error("maybe just_safe exception");
    };

    T just_or_default() {
        if (has_value()) {
            return std::get<T>(var);
        }
        return {};
    };
    // a -> (a , f a) -> b

    template <ndo::ndo_callable F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return std::invoke(f, std::forward<T>(just_or_throw()));
    };

    template <typename Target, ndo::ndo_callable F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_throw())));
    };

    template <ndo::ndo_callable F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) {
        return std::invoke(f, std::forward<T>(just_or_default()));
    }

    template <typename Target, ndo::ndo_callable F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_default())));
    }

    template <typename F, typename U>
    maybe<U> and_then(F&& f) {
        if (has_value()) {
            return maybe<U>{};
        }
        return maybe<U>{f(just_or_throw())};
    };

    ~maybe() = default;
};

};  // namespace ndo