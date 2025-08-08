#pragma once
#include <iostream>

#include "allocator_aware.hpp"
#include "allocator_eraseable.hpp"
#include "default_eraseable.hpp"
#include "is_basic_string.hpp"

namespace ndo {
template <class E, class T>
concept Eraseable = (is_basic_string_v<T> && DefaultErasable<E>) || (AllocatorAware<T> && AllocatorEraseable<E, T, typename T::allocator_type>) || (!AllocatorAware<T> && DefaultErasable<E>);

}