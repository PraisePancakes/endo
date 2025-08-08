#pragma once
#include <iostream>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and transformations.
namespace ndo {

/**
 * \brief Returns a new container with the elements of the input container in reverse order.
 *
 * Creates a new container of the same type, filled with the elements of `cont`
 * in reverse order.
 *
 * @tparam Container A container type supporting `crbegin`, `crend`, and `insert(end(), value)`.
 * @param cont The input container to reverse.
 * @return A new container with reversed elements.
 *
 * @note This function assumes the container supports bidirectional iteration.
 */
template <typename Container>
[[nodiscard]] constexpr auto reverse(const Container& cont) noexcept {
    Container ret{};
    for (auto it = cont.crbegin(); it != cont.crend(); ++it) {
        const auto& v = *it;  // use const ref to avoid copy/move
        ret.insert(ret.end(), v);
    }
    return ret;
}

}  // namespace ndo
