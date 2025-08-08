#pragma once
#include <concepts>
#include <iostream>
#include <memory>

namespace ndo {

/**
 * \concept AllocatorEraseable
 * \brief Concept that requires an allocator to be able to destroy an object of type `E`.
 *
 * This concept checks that:
 * - `T`'s `allocator_type` is the rebound allocator of `A` for element type `E`.
 * - The allocator `A` can destroy an object of type `E*` via `allocator_traits<A>::destroy`.
 *
 * @tparam E Element type to be destroyed.
 * @tparam T Container type that uses the allocator.
 * @tparam A Allocator type.
 */
template <class E, class T, class A>
concept AllocatorEraseable = requires(A m, E* p) {
    requires std::same_as<typename T::allocator_type, typename std::allocator_traits<A>::template rebind_alloc<E>>;
    std::allocator_traits<A>::destroy(m, p);
};

}  // namespace ndo
