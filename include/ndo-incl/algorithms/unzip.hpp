#pragma once
#include <iostream>
#include <tuple>
#include <utility>

#include "../utils/value.hpp"

/// \ingroup algorithms
/// \brief Namespace for generic tuple and container utilities.
namespace ndo {

/**
 * \brief Splits a tuple of pairs into a concatenated tuple of first and second elements.
 *
 * Given a tuple like `std::tuple<std::pair<A, B>, std::pair<C, D>, ...>`, this function
 * returns a tuple containing `(A, C, ..., B, D, ...)`.
 *
 * For example:
 * \code
 * auto t = std::make_tuple(std::pair{1, 'a'}, std::pair{2, 'b'});
 * auto result = unzip(t); // returns tuple<int, int, char, char> = (1, 2, 'a', 'b')
 * \endcode
 *
 * @tparam T A tuple type holding pairs.
 * @param t The tuple of pairs to unzip.
 * @return A tuple concatenating all first elements followed by all second elements.
 *
 * @note Requires C++20 for templated lambdas and `std::index_sequence`.
 */
template <typename T>
[[nodiscard]] constexpr auto unzip(const T& t) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat(
            ([&]<std::size_t idx>(ndo::value<idx>) {
                // Extract pair at index idx, returning a tuple of first and second separately
                const auto& p = std::get<idx>(t);
                return std::tuple{p.first, p.second};
            }(ndo::value<i>{}))...);
    }(std::make_index_sequence<std::tuple_size_v<T>>{});
}

}  // namespace ndo
