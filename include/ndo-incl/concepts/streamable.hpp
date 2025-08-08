#pragma once
#include <iostream>

namespace ndo {
template <typename T>
concept Streamable = requires(std::ostream &os, T t) {
    { os << t };
};
}  // namespace ndo