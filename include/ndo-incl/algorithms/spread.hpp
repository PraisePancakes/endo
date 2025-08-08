#pragma once
#include <concepts>
#include <iostream>
#include <vector>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and data generation utilities.
namespace ndo {

/**
 * \brief Generates a vector containing an inclusive range of integral values.
 *
 * Returns a vector with all integers from `a` to `b` inclusive.
 *
 * @tparam N An integral type (defaults to `int`).
 * @param a The start of the range.
 * @param b The end of the range.
 * @return A `std::vector<N>` containing the range `[a, b]`.
 *
 * @note If `b < a`, the returned vector will be empty.
 */
template <std::integral N = int>
[[nodiscard]] auto spread(N a, N b) noexcept {
    std::vector<N> ret;
    if (b < a) {
        return ret;  // empty vector if range invalid
    }
    ret.reserve(static_cast<size_t>(b - a) + 1);
    for (N i = a; i <= b; ++i) {
        ret.push_back(i);
    }
    return ret;
}

}  // namespace ndo
