#pragma once
#include "maybe.hpp"

namespace ndo {
template <typename Left, typename Right>
class either {
    ndo::maybe<Left> left;
    ndo::maybe<Right> right;

   public:
    using left_type = Left;
    using right_type = Right;

    either() : left{}, right{} {};
    either(const Left& l, const Right& r) : left{l}, right{r} {};
    either(Left&& l, Right&& r) : left{std::move(l)}, right{std::move(r)} {};
    either(const Left& l) : left{l}, right{} {};
    either(const Right& r) : left{}, right{r} {};
    either(Left&& l) : left{std::move(l)}, right{} {};
    either(Right&& r) : left{}, right{std::move(r)} {};
    either& operator=(const std::pair<Left, Right>& p) {
        left = p.first;
        right = p.second;
        return *this;
    };
    either& operator=(const Left& l) {
        left = l;
        return *this;
    };
    either& operator=(const either& o) {
        left = o.left;
        right = o.right;
        return *this;
    };
    either& operator=(const Right& r) {
        return *this;
    };

    [[nodiscard]] constexpr Right just_or_default() const noexcept {
        return right.just_or_default();
    };

    [[nodiscard]] constexpr Right& just_or_throw() {
        return right.just_or_throw();
    };

    [[nodiscard]] constexpr Left& error_or_throw() const {
        return left.just_or_throw();
    }

    [[nodiscard]] constexpr Left error_or_default() const noexcept {
        return left.just_or_default();
    };

    constexpr explicit operator bool() const noexcept {
        return this->has_value();
    };

    [[nodiscard]] constexpr bool has_value() const noexcept {
        return right.has_value();
    };

    [[nodiscard]] constexpr Right just_or(const Right& r) const noexcept {
        return right.just_or(r);
    }

    [[nodiscard]] constexpr Left error_or(const Left& l) const noexcept {
        return left.just_or(l);
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then(F&& f) {
        return right.and_then(std::forward<F>(f));
    }

    template <typename F>
    [[nodiscard]] constexpr decltype(auto) and_then_safe(F&& f) {
        return right.and_then_safe(std::forward<F>(f));
    }

    ~either() = default;
};
}  // namespace ndo