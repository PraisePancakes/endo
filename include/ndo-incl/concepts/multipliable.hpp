#pragma once
#include <iostream>

namespace ndo {

/**
 * \concept Multipliable
 * \brief Concept that requires a type to support multiplication operations.
 *
 * A type `T` satisfies the `Multipliable` concept if it supports both:
 * - Binary multiplication operator: `a * b`
 * - Multiplication assignment operator: `a *= b`
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Multipliable = requires(T a, T b) {
    { a * b };
    { a *= b };
};

}  // namespace ndo
