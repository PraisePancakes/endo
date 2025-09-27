#pragma once
#include <functional>
#include <iostream>
#include <type_traits>

/// \ingroup algorithms
/// \brief Namespace for generic algorithms.
namespace ndo {
template <auto... Values>
struct tuple {
    static consteval std::tuple<decltype(Values)...> tuple() {
        return std::tuple{Values...};
    }
};

template <typename T, typename F>
consteval auto tuple_filter(T t, F func) {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat([&]<std::size_t idx>(std::integral_constant<std::size_t, idx>) {
            if constexpr (func(std::get<idx>(t.tuple()))) {
                return std::make_tuple(std::get<idx>(t.tuple()));
            } else {
                return std::make_tuple();
            }
        }(std::integral_constant<std::size_t, i>{})...);
    }(std::make_index_sequence<std::tuple_size_v<decltype(t.tuple())>>{});
}

}  // namespace ndo
