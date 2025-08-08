#pragma once
#include <iostream>
#include <vector>

namespace ndo {

template <typename T, typename U>
constexpr void flatten(const std::vector<T>& in, std::vector<U>& out) noexcept {
        out.insert(out.end(), in.begin(), in.end());
};

template <typename T, typename U>
constexpr void flatten(const std::vector<std::vector<T>>& vec, std::vector<U>& out) noexcept {
    for (auto e : vec) {
        flatten(e, out);
    }
};

}  // namespace ndo