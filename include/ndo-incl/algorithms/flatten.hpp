#pragma once
#include <iostream>
#include <vector>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and data transformations.
namespace ndo {

/**
 * \brief Flattens a single-level `std::vector<T>` into `std::vector<U>`.
 *
 * Copies all elements from `in` into the end of `out`.
 *
 * @tparam T The input vector element type.
 * @tparam U The output vector element type. Must be assignable from `T`.
 * @param in The input vector of elements.
 * @param out The output vector to insert into.
 */
template <typename T, typename U>
constexpr void flatten(const std::vector<T>& in, std::vector<U>& out) noexcept {
    out.insert(out.end(), in.begin(), in.end());
}

/**
 * \brief Recursively flattens a nested `std::vector<std::vector<T>>` into `std::vector<U>`.
 *
 * Traverses the 2D vector and inserts all inner elements into `out`.
 *
 * @tparam T The element type inside inner vectors.
 * @tparam U The output vector element type. Must be assignable from `T`.
 * @param vec The input 2D vector.
 * @param out The output vector to populate.
 */
template <typename T, typename U>
constexpr void flatten(const std::vector<std::vector<T>>& vec, std::vector<U>& out) noexcept {
    for (const auto& e : vec) {
        flatten(e, out);
    }
}

}  // namespace ndo
