#pragma once
#include <iostream>

#include "allocator_aware.hpp"
#include "allocator_eraseable.hpp"
#include "default_eraseable.hpp"
#include "is_basic_string.hpp"

namespace ndo {

/**
 * \concept Eraseable
 * \brief Concept that checks if type `T` can erase elements of type `E`.
 *
 * This concept is satisfied if any of the following hold:
 * - `T` is a basic string and `E` is `DefaultErasable`.
 * - `T` is allocator-aware and its allocator supports erasing `E`.
 * - `T` is not allocator-aware but `E` is `DefaultErasable`.
 *
 * @tparam E The element type.
 * @tparam T The container or string type.
 */
template <class E, class T>
concept Eraseable =
    (is_basic_string_v<T> && DefaultErasable<E>) ||
    (AllocatorAware<T> && AllocatorEraseable<E, T, typename T::allocator_type>) ||
    (!AllocatorAware<T> && DefaultErasable<E>);

}  // namespace ndo
