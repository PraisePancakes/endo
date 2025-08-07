#pragma once
#include <iostream>

namespace ndo {

template <std::integral N = int>
[[nodiscard]] auto spread(N a, N b) noexcept {
    std::vector<N> ret;
    for (N i = a; i <= b; i++) {
        ret.push_back(i);
    }
    return ret;
};

template <typename Container>
[[nodiscard]] auto to_indexed_map(const Container& cont) noexcept {
    std::unordered_map<int, typename Container::value_type> ret{};
    std::size_t idx = 0;
    for (const auto& v : cont) {
        ret[idx++] = v;
    };
    return ret;
};

}  // namespace ndo