#pragma once
#include "maybe.hpp"

namespace ndo {
template <typename Left, typename Right>
class either {
    ndo::maybe<Left> left;
    ndo::maybe<Right> right;

   public:
    either() : left{}, right{} {};
    either(const Left& l, const Right& r) : left{l}, right{r} {};
    either(Left&& l, Right&& r) : left{std::move(l)}, right{std::move(r)} {};
    either(const Left& l) : left{l}, right{} {};
    either(const Right& r) : left{}, right{r} {};
    either(Left&& l) : left{std::move(l)}, right{} {};
    either(Right&& r) : left{}, right{std::move(r)} {};

    [[nodiscard]] constexpr Right& just_or_default() const noexcept {
        return right.just_or_default();
    };

    [[nodiscard]] constexpr Left& error_or_default() const noexcept {
        return left.just_or_default();
    };

    constexpr explicit operator bool() const noexcept {
        return this->has_value();
    };

    [[nodiscard]] constexpr bool has_value() const noexcept {
        return right.has_value();
    };

    [[nodiscard]] constexpr Right& just_or(const Right& r) const noexcept {
        if (has_value()) {
            return just_or_default();
        };
        return r;
    }

    [[nodiscard]] constexpr Left& error_or(const Left& l) const noexcept {
        if (left.has_value()) {
            return error_or_default();
        }
        return l;
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then(F&& f) const {
        if (has_value()) {
            return right.and_then(std::forward<F>(f));
        }
    };

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then_safe(F&& f) const {};

    ~either() {};
};
}  // namespace ndo