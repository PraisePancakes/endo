#pragma once
#include <iostream>
namespace ndo {
template <typename T>
concept Subtractable = requires(T a, T b) {
    { a - b };
    { a -= b };
};
}  // namespace ndo