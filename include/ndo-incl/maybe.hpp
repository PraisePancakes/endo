#pragma once
#include <variant>

#include "visitor.hpp"
namespace ndo {
template <typename T>
struct maybe;

template <typename T>
struct is_maybe : std::false_type {};

template <typename T>
struct is_maybe<maybe<T>> : std::true_type {};

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
        return std::visit(visitor{[](NDO_NOTHING_TYPE NT) { return false; }, [](T lit) { return true; }}, var);
    };

    constexpr bool has_value() const {
        return (*this).operator bool();
    };

    const T& just() const {
        if (has_value()) {
            return std::get<T>(var);
        }
        throw std::runtime_error("maybe just_safe exception");
    };

    T& just() {
        if (has_value()) {
            return std::get<T>(var);
        }
        throw std::runtime_error("maybe just_safe exception");
    };

    ~maybe() = default;
};
};  // namespace ndo