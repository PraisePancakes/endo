#pragma once
#include <iostream>

namespace ndo {
template <class E, class T, class A>
concept AllocatorEraseable = requires(A m, E *p) {
    requires std::same_as<typename T::allocator_type, typename std::allocator_traits<A>::rebind_alloc<E>>;
    std::allocator_traits<A>::destroy(m, p);
};

}  // namespace ndo