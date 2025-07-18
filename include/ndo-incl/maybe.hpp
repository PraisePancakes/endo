#pragma once
#include <variant>

#include "visitor.hpp"
namespace ndo {

struct ndo_null_t {
    ndo_null_t() = default;
    ndo_null_t(ndo_null_t&&) = default;
    ndo_null_t(const ndo_null_t&) = default;
    ~ndo_null_t() = default;
};

inline constexpr ndo_null_t ndo_null{};

template <typename T>
class maybe {
    T var;
    bool engaged;

   public:
    constexpr maybe() : var(), engaged(false) {};
    constexpr maybe(T&& v) : var(std::move(v)), engaged(true) {};
    constexpr maybe(const T& o) : var(o.var), engaged(true) {};
    constexpr maybe(const maybe<T>& o) : var(o.var), engaged(o.engaged) {};

    explicit constexpr operator bool() const {
        return engaged && (!std::is_same_v<T, ndo_null_t>);
    };

    constexpr bool has_value() const {
        return (*this).operator bool();
    };

    constexpr T& just_or_throw() const {
        if (has_value()) {
            return var;
        }
        throw std::runtime_error("maybe just_or_throw exception");
    };

    constexpr T& just_or_throw() {
        if (has_value()) {
            return var;
        }
        throw std::runtime_error("maybe just_or_throw exception");
    };

    constexpr T just_or_default() const {
        if (has_value()) {
            return var;
        }
        return {};
    };
    // a -> (a , f a) -> b

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return std::invoke(f, std::forward<T>(just_or_throw()));
    };

    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_throw())));
    };

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return std::invoke(f, std::forward<T>(just_or_default()));
    }

    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_default())));
    }

    template <typename F>
    constexpr auto and_then(F&& f) {
        using U = std::invoke_result_t<F, T>;
        static_assert(!std::is_same_v<U, void> || !std::is_same_v<T, void>, "and_then has ill-formed tendencies with no transformable return type");
        if (has_value()) {
            return maybe<U>{std::invoke(std::forward<F>(f), just_or_default())};
        }
        return maybe<U>();
    }

    ~maybe() = default;
};

};  // namespace ndo