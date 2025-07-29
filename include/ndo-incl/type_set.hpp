#pragma once
#include <iostream>
#include <tuple>

namespace ndo {
template <typename... Ts>
class type_multiset;

template <template <typename...> class Ts, typename... T1>
struct type_multiset<Ts<T1...>> : public type_multiset<T1...> {
};

template <template <typename...> class Ts, typename... T1, typename... T2>
struct type_multiset<Ts<T1...>, Ts<T2...>> : public type_multiset<T1..., T2...> {};

template <typename... Ts>
class type_multiset {
    using this_type__ = type_multiset<Ts...>;

   public:
    constexpr static std::size_t cardinality = sizeof...(Ts);

    template <typename... Ls>
    struct append {
        using type = type_multiset<Ts..., Ls...>;
    };

    template <template <typename...> class T, typename... Us>
    struct append<T<Us...>> : append<Ts..., Us...> {};

    template <typename... Ls>
    struct prepend {
        using type = type_multiset<Ls..., Ts...>;
    };

    template <template <typename...> class T, typename... Us>
    struct prepend<T<Us...>> : prepend<Ts..., Us...> {};

    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<Ts...>>;

    template <typename T>
    constexpr static auto index = []() {
        return ((std::is_same_v<T, Ts> || ...) ? (([]() {
            signed i = 0;
            (... && (!std::is_same_v<T, Ts> && ++i));
            return i;
        }()))
                                               : -1);
    }();

    template <typename T>
    constexpr static bool contains = (std::is_same_v<T, Ts> || ...);

    using pop_front = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_type__::get<i + 1>...>>{};
    }(std::make_index_sequence<sizeof...(Ts) - 1>{}))::type;

    using pop_back = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_type__::get<i>...>>{};
    }(std::make_index_sequence<sizeof...(Ts) - 1>{}))::type;

    using reverse = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_type__::get<sizeof...(Ts) - 1 - i>...>>{};
    }(std::make_index_sequence<sizeof...(Ts)>{}))::type;
};

}  // namespace ndo