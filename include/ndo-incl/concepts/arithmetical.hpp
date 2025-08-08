#pragma once
#include "addable.hpp"
#include "divisible.hpp"
#include "multipliable.hpp"
#include "subtractable.hpp"

namespace ndo {

/**
 * \concept Arithmetical
 * \brief Concept representing types that support basic arithmetic operations.
 *
 * A type `T` satisfies the `Arithmetical` concept if it supports:
 * - Addition (`Addable`)
 * - Subtraction (`Subtractable`)
 * - Multiplication (`Multipliable`)
 * - Division (`Divisible`)
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Arithmetical = Subtractable<T> && Multipliable<T> && Divisible<T> && Addable<T>;

}  // namespace ndo
