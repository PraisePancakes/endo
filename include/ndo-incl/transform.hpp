#pragma once
#include <array>
#include <iostream>
#include <tuple>

namespace ndo {

template <typename Container, typename F>
    requires(std::is_invocable_v<F, typename Container::value_type>)
[[nodiscard]] constexpr auto map_from(const Container& cont, F&& f) noexcept(noexcept(std::is_nothrow_invocable_v<F, typename Container::value_type>)) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        ret.insert(ret.end(), std::move(std::invoke(std::forward<F>(f), *it)));
    }
    return ret;
};

template <std::integral N, N a, N b>
[[nodiscard]] constexpr auto spread() noexcept {
    std::array<N, b - a + 1> ret{};
    size_t index = 0;
    for (N i = a; i < b; i++) {
        ret[index] = i;
        index++;
    }
    return ret;
};

}  // namespace ndo