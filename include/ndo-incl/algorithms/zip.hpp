#pragma once
#include <iostream>
#include <tuple>
#include <utility>

#include "../utils/value.hpp"

/// \ingroup algorithms
/// \brief Namespace for generic tuple and container utilities.
namespace ndo {

/**
 * \brief Combines two tuples of the same size into a tuple of pairs.
 *
 * Given two tuples `t1` and `t2`, returns a tuple where each element
 * is a `std::pair` formed by the corresponding elements of `t1` and `t2`.
 *
 * For example:
 * \code
 * auto t1 = std::make_tuple(1, 'a');
 * auto t2 = std::make_tuple(2.0, "b");
 * auto result = zip(t1, t2); // std::tuple<std::pair<int, double>, std::pair<char, const char*>>
 * \endcode
 *
 * @tparam T1 Type of the first tuple.
 * @tparam T2 Type of the second tuple.
 * @param t1 The first input tuple.
 * @param t2 The second input tuple.
 * @return A tuple of pairs combining elements from `t1` and `t2`.
 *
 * @note Requires `std::tuple_size_v<T1> == std::tuple_size_v<T2>`.
 */
template <typename T1, typename T2>
    requires(std::tuple_size_v<T1> == std::tuple_size_v<T2>)
[[nodiscard]] constexpr auto zip(const T1& t1, const T2& t2) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::make_tuple(
            ([&]<std::size_t idx>(ndo::value<idx>) {
                return std::pair(std::get<idx>(t1), std::get<idx>(t2));
            }(ndo::value<i>{}))...);
    }(std::make_index_sequence<std::tuple_size_v<T1>>{});
}

}  // namespace ndo
