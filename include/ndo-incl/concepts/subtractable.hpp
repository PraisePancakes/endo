#pragma once
#include <iostream>

namespace ndo {

/**
 * \concept Subtractable
 * \brief Concept that requires a type to support subtraction operations.
 *
 * A type `T` satisfies the `Subtractable` concept if it supports both:
 * - Binary subtraction operator: `a - b`
 * - Subtraction assignment operator: `a -= b`
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Subtractable = requires(T a, T b) {
    { a - b };
    { a -= b };
};

}  // namespace ndo
