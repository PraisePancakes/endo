#pragma once
#include <iostream>
#include <tuple>

namespace ndo {
template <typename... Ts>
class type_multiset;

template <template <typename...> class Ts, typename... T1>
struct type_multiset<Ts<T1...>> : public type_multiset<T1...> {};

template <template <typename...> class Ts, typename... T1, typename... T2>
struct type_multiset<Ts<T1...>, Ts<T2...>> : public type_multiset<T1..., T2...> {};

namespace internal {
template <typename T>
struct pop_front_type_multiset;

template <typename First, typename... Rest>
struct pop_front_type_multiset<type_multiset<First, Rest...>> {
    using type = type_multiset<Rest...>;
};

template <>
struct pop_front_type_multiset<type_multiset<>> {
    using type = type_multiset<>;
};
}  // namespace internal

template <typename... Ts>
class type_multiset {
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

    using pop_front = typename internal::pop_front_type_multiset<type_multiset<Ts...>>::type;
};

}  // namespace ndo