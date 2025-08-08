#pragma once
#include <iostream>

namespace ndo {

/**
 * \concept Streamable
 * \brief Concept that requires a type to support streaming to `std::ostream`.
 *
 * A type `T` satisfies the `Streamable` concept if it can be used with
 * the insertion operator (`<<`) to output to an `std::ostream`.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept Streamable = requires(std::ostream& os, T t) {
    { os << t };
};

}  // namespace ndo
