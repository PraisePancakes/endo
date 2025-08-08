#pragma once
#include <concepts>
#include <iostream>

namespace ndo {

/**
 * \concept AllocatorAware
 * \brief Concept that requires a type to provide an allocator accessor.
 *
 * A type `T` satisfies the `AllocatorAware` concept if it has a member
 * function `get_allocator()` that returns its `allocator_type`.
 *
 * @tparam T The type to check.
 */
template <class T>
concept AllocatorAware = requires(T a) {
    { a.get_allocator() } -> std::same_as<typename T::allocator_type>;
};

}  // namespace ndo
