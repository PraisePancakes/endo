#pragma once
#include <iostream>

/// \ingroup concepts
/// \brief Namespace for metaprogramming traits and concepts.
namespace ndo {

/**
 * \concept Addable
 * \brief Concept that requires a type to support addition operations.
 *
 * A type `T` satisfies the `Addable` concept if it supports both:
 * - Binary addition operator: `a + b`
 * - Addition assignment operator: `a += b`
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b };
    { a += b };
};

}  // namespace ndo
