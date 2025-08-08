#pragma once
#include <iostream>

namespace ndo {

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