#pragma once
#include <functional>
#include <variant>

namespace ndo {

struct ndo_null_t {};

inline constexpr ndo_null_t ndo_nothing{};

template <typename T>
class maybe {
    std::variant<T, ndo_null_t> value;

   public:
    constexpr maybe() : value(ndo_nothing) {};
    constexpr maybe(const T& v) : value(v) {};
    constexpr maybe(T&& v) : value(std::move(v)) {};
    constexpr maybe(const maybe<T>& o) : value(std::move(o.value)) {};
    constexpr maybe& operator=(const ndo_null_t& n) {
        value = n;
        return *this;
    };

    explicit constexpr operator bool() const noexcept {
        return std::holds_alternative<T>(value);
    };

    constexpr bool has_value() const noexcept {
        return this->operator bool();
    };

    constexpr T& just_or_throw() {
        if (has_value()) {
            return std::get<T>(value);
        }
        throw std::runtime_error("just_or_throw exception");
    };

    constexpr T just_or_default() const {
        if (has_value()) {
            return std::get<T>(value);
        }
        return {};
    }

    constexpr T just_or(const T& v) {
        if (has_value()) {
            return just_or_throw();
        }
        return v;
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return std::invoke(f, std::forward<T>(just_or_throw()));
    }
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_throw())));
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return std::invoke(f, std::forward<T>(just_or_default()));
    }

    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return static_cast<Target>(std::invoke(f, std::forward<T>(just_or_default())));
    }

    template <typename F>
    [[nodiscard]] constexpr auto and_then(F&& f) {
        using result_t = std::decay_t<std::invoke_result_t<F, T>>;
        if (has_value()) {
            return maybe<result_t>({std::invoke(std::forward<F>(f), std::forward<T>(just_or_throw()))});
        }

        return maybe<result_t>();
    }

    template <typename F>
    [[nodiscard]] constexpr auto and_then_safe(F&& f) {
        using result_t = std::decay_t<std::invoke_result_t<F, T>>;
        if (has_value()) {
            return maybe<result_t>({std::invoke(std::forward<F>(f), std::forward<T>(just_or_default()))});
        }
        return maybe<result_t>();
    }

    ~maybe() = default;
};

template <>
class maybe<ndo_null_t> {
   public:
    constexpr maybe() noexcept = default;
    constexpr maybe(ndo_null_t) noexcept {}
    constexpr maybe(const maybe&) noexcept = default;
    constexpr maybe(maybe&&) noexcept = default;
    ~maybe() = default;
    explicit constexpr operator bool() const noexcept {
        return false;
    }

    constexpr bool has_value() const noexcept {
        return false;
    }

    constexpr ndo_null_t just_or_throw() {
        return ndo_nothing;
    };

    constexpr ndo_null_t just_or_default() const {
        return ndo_nothing;
    };

    constexpr ndo_null_t just_or(void) {
        return ndo_nothing;
    };

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return ndo_nothing;
    }
    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_throw(F&& f) {
        return ndo_nothing;
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return ndo_nothing;
    }

    template <typename Target, typename F>
    [[nodiscard]] constexpr decltype(auto) map_or_default(F&& f) const noexcept {
        return ndo_nothing;
    }

    template <typename F>
    [[nodiscard]] constexpr auto and_then(F&& f) {
        return maybe<ndo_null_t>();
    }
};

namespace internal {
template <typename T>
struct is_nothing_trait : std::false_type {};

template <>
struct is_nothing_trait<maybe<ndo_null_t>> : std::true_type {};

template <typename T>
struct is_maybe_trait : std::false_type {};

template <typename T>
struct is_maybe_trait<maybe<T>> : std::true_type {};
}  // namespace internal

template <typename T>
concept is_maybe = internal::is_maybe_trait<std::decay_t<T>>::value;

template <typename T>
concept is_nothing = internal::is_nothing_trait<std::decay_t<T>>::value;

};  // namespace ndo