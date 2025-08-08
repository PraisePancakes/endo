#pragma once
#include <iostream>

#include "../utils/value.hpp"
namespace ndo {
template <typename T>
[[nodiscard]] constexpr auto unzip(const T& t) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat([&]<std::size_t idx>(ndo::value<idx>) {
            return std::pair(std::get<idx>(t).first, std::get<idx>(t).second);
        }(ndo::value<i>{})...);
    }(std::make_index_sequence<std::tuple_size_v<T>>{});
}
}  // namespace ndo