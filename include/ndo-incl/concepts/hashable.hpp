#pragma once
#include <iostream>

namespace ndo {
template <typename T>
concept Hashable = requires(T x) {
    { std::hash<T>{}(x) } -> std::convertible_to<std::size_t>;
};
}  // namespace ndo