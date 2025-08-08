#pragma once
#include <iostream>
#include <memory>  // for std::destroy_at

namespace ndo {

/**
 * \concept DefaultErasable
 * \brief Concept that requires a pointer to an object of type `E` to be destroyable via `std::destroy_at`.
 *
 * A type `E` satisfies this concept if `std::destroy_at(p)` is a valid expression for `E* p`.
 *
 * @tparam E The element type to be destroyed.
 */
template <class E>
concept DefaultErasable = requires(E* p) {
    std::destroy_at(p);
};

}  // namespace ndo
