#pragma once

namespace ndo {
template <typename F>
struct is_noexcept : std::false_type {};

template <typename F, typename... Args>
struct is_noexcept<F(Args...) noexcept> : std::true_type {};
}