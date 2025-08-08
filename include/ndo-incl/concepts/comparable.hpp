#pragma once

namespace ndo {
template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b };
    { a == b };
    { a > b };
    { a != b };
    { a >= b };
    { a <= b };
};
}  // namespace ndo