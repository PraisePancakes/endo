#pragma once
#include <iostream>
#include <tuple>

namespace ndo {

template <typename... Ts>
class type_multiset {
   public:
    template <typename T>
    using append = type_multiset<Ts..., T>;

    template <typename T>
    using prepend = type_multiset<T, Ts...>;

    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<Ts...>>;

    template <typename T>
    constexpr static bool contains = (std::is_same_v<T, Ts> || ...);
};

template <template <typename...> class T, typename... Ts>
class type_multiset<T<Ts...>> : public type_multiset<Ts...> {};

}  // namespace ndo