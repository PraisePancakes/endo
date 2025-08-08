#pragma once
#include <iostream>
#include <unordered_map>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and transformations.
namespace ndo {

/**
 * \brief Creates an `std::unordered_map` mapping indices to elements from a container.
 *
 * Given a container, returns a map from `int` indices (starting at 0) to the container's elements.
 *
 * @tparam Container A container type with `value_type` and iterable with range-based for.
 * @param cont The input container.
 * @return An `std::unordered_map<int, Container::value_type>` mapping indices to elements.
 *
 * @note The container must be iterable and elements must be copyable/movable.
 * @note The indices are `int` starting from 0.
 */
template <typename Container>
[[nodiscard]] auto to_indexed_map(const Container& cont) noexcept {
    std::unordered_map<int, typename Container::value_type> ret{};
    int idx = 0;
    for (const auto& v : cont) {
        ret[idx++] = v;
    }
    return ret;
}

}  // namespace ndo
