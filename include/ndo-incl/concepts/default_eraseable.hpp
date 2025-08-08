#pragma once
#include <iostream>

namespace ndo {

template <class E>
concept DefaultErasable = requires(E *p) {
    std::destroy_at(p);
};
}  // namespace ndo