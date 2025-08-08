#pragma once
#include <iostream>
#include <tuple>
#include <utility>

#include "../utils/value.hpp"

/// \ingroup algorithms
/// \brief Namespace for generic algorithms and utilities.
namespace ndo {

/**
 * \brief Zips two tuples of the same size into a flat tuple of values.
 *
 * Given two tuples `t1` and `t2` of the same size, returns a new tuple
 * containing `value`s of elements at corresponding indices.
 *
 * For example:
 * ```cpp
 * auto t1 = std::make_tuple(1, 'a');
 * auto t2 = std::make_tuple(2.0, "b");
 * auto result = flat_zip(t1, t2); // result is std::tuple<int, double, char, const char*>
 * ```
 *
 * @tparam T1 The type of the first tuple.
 * @tparam T2 The type of the second tuple.
 *
 * @param t1 The first input tuple.
 * @param t2 The second input tuple.
 * @return A new tuple of `value`s created from `t1[i]` and `t2[i]`.
 *
 * @note Requires `std::tuple_size_v<T1> == std::tuple_size_v<T2>`.
 */
template <typename T1, typename T2>
    requires(std::tuple_size_v<T1> == std::tuple_size_v<T2>)
[[nodiscard]] constexpr auto flat_zip(const T1& t1, const T2& t2) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat(
            ([&]<std::size_t idx>(ndo::value<idx>) {
                return std::tuple{std::pair(std::get<idx>(t1), std::get<idx>(t2))};
            }(ndo::value<i>{}))...);
    }(std::make_index_sequence<std::tuple_size_v<T1>>{});
}

}  // namespace ndo
