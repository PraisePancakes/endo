#pragma once
#include <iostream>

namespace ndo {

/**
 * \concept Divisible
 * \brief Concept that requires a type to support division operations.
 *
 * A type `T` satisfies the `Divisible` concept if it supports both:
 * - Binary division operator: `a / b`
 * - Division assignment operator: `a /= b`
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Divisible = requires(T a, T b) {
    { a / b };
    { a /= b };
};

}  // namespace ndo
