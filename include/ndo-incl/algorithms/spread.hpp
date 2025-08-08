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

}  // namespace ndo