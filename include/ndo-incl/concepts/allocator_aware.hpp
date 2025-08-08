#pragma once
#include <iostream>

namespace ndo {
template <class T>
concept AllocatorAware = requires(T a) {
    { a.get_allocator() } -> std::same_as<typename T::allocator_type>;
};

}  // namespace ndo