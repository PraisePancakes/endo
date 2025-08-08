#pragma once
#include "addable.hpp"
#include "divisible.hpp"
#include "multipliable.hpp"
#include "subtractable.hpp"

namespace ndo {
template <typename T>
concept Arithmetical = Subtractable<T> && Multipliable<T> && Divisible<T> && Addable<T>;
}