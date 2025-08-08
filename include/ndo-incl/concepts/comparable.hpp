#pragma once

namespace ndo {

/**
 * \concept Comparable
 * \brief Concept that requires a type to support all standard comparison operators.
 *
 * A type `T` satisfies the `Comparable` concept if it supports:
 * - less than (`<`)
 * - equality (`==`)
 * - greater than (`>`)
 * - inequality (`!=`)
 * - greater than or equal (`>=`)
 * - less than or equal (`<=`)
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b };
    { a == b };
    { a > b };
    { a != b };
    { a >= b };
    { a <= b };
};

}  // namespace ndo
