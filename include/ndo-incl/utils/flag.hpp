#pragma once
#include <iostream>

namespace ndo {

template <typename ENUM>
struct flagnum {
    static_assert(std::is_enum<ENUM>::value, "ENUM must be an enum type");
    using underlying_t = typename std::underlying_type<ENUM>::type;
    underlying_t mask = 0x000;

    flagnum() : mask{0} {}
    flagnum(ENUM single_flag) : mask(static_cast<underlying_t>(single_flag)) {}
    flagnum(const flagnum &o) : mask(o.mask) {}
    ~flagnum() = default;

    constexpr flagnum &operator|=(ENUM addValue) {
        mask |= static_cast<underlying_t>(addValue);
        return *this;
    }

    constexpr flagnum &operator&=(ENUM maskValue) {
        mask &= static_cast<underlying_t>(maskValue);
        return *this;
    }

    constexpr bool operator==(ENUM maskValue) const noexcept {
        return ((this->mask & static_cast<underlying_t>(maskValue)) == static_cast<underlying_t>(maskValue));
    }

    explicit operator bool() const noexcept {
        return mask != 0;
    }
};

template <typename E>
    requires std::is_enum_v<E>
constexpr flagnum<E> operator|(E lhs, E rhs) {
    return flagnum<E>(lhs) | rhs;
}

template <typename E>
    requires std::is_enum_v<E>
constexpr flagnum<E> operator&(E lhs, E rhs) {
    return flagnum<E>(lhs) & rhs;
}

template <typename E>
    requires std::is_enum_v<E>
constexpr flagnum<E> operator~(E val) {
    return ~flagnum<E>(val);
}
};  // namespace ndo