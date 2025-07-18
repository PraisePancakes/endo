#pragma once
#include <variant>

#include "visitor.hpp"
namespace ndo {

template <typename T>
class maybe;

template <typename T>
struct is_maybe : std::false_type {};

template <typename T>
struct is_maybe<maybe<T>> : std::true_type {};

template <typename T>
class maybe {
    T var;
    bool active;
    void destroy() {
        if (active) {
            active = false;
            (*reinterpret_cast<const T*>(&var)).~T();
        }
    };

   public:
    using value_type = T;
    constexpr maybe() : var(), active(false) {};
    constexpr maybe(T&& v) : var(), active(true) {
        std::construct_at(&var, std::move(v));
    };
    constexpr maybe(const T& o) : var(), active(true) {
        std::construct_at(&var, o);
    };
    constexpr maybe(const maybe<T>& o) : var(), active(o.active) { std::construct_at(&var, std::move(o.var)); };
    constexpr maybe& operator=(const T& o) {
        destroy();
        std::construct_at(&var, o);
        active = true;
    };
    constexpr maybe& operator=(T&& o) {
        destroy();
        std::construct_at(&var, std::move(o));
        active = true;
    }
    constexpr maybe& operator=(const maybe<T>& o) {
        destroy();
        std::construct_at(&var, std::move(o.var));
        active = o.active;
        return *this;
    };

    explicit constexpr operator bool() const {
        return active;
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
        static_assert(is_maybe<U>::value, "invoked result must be a maybe");
        if (has_value()) {
            return std::invoke(std::forward<F>(f), just_or_default());
        }
        return maybe<typename U::value_type>();
    }

    ~maybe() = default;
};

template <typename T>
maybe<T> nothing() {
    return {};
};

};  // namespace ndo