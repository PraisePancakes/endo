#pragma once
#include <iostream>

#include "../utils/value.hpp"
namespace ndo {
template <typename T1, typename T2>
    requires(std::tuple_size_v<T1> == std::tuple_size_v<T2>)
[[nodiscard]] constexpr auto flat_zip(const T1& t1, const T2& t2) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat([&]<std::size_t idx>(ndo::value<idx>) {
            return std::pair(std::get<idx>(t1), std::get<idx>(t2));
        }(ndo::value<i>{})...);
    }(std::make_index_sequence<std::tuple_size_v<T1>>{});
};
}  // namespace ndo