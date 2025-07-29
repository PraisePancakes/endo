#pragma once
#include <iostream>
#include <tuple>

namespace ndo {
template <typename... Ts>
class [[nodiscard]] type_multiset;

template <template <typename...> class Ts, typename... T1>
struct [[nodiscard]] type_multiset<Ts<T1...>> : public type_multiset<T1...> {
};

template <template <typename...> class Ts, typename... T1, typename... T2>
struct [[nodiscard]] type_multiset<Ts<T1...>, Ts<T2...>> : public type_multiset<T1..., T2...> {};

template <>
struct type_multiset<> {
    using this_type__ = type_multiset<>;

   public:
    constexpr static std::size_t cardinality = 0;
    template <typename... Ls>
    struct append {
        using type = type_multiset<Ls...>;
    };

    template <template <typename...> class T, typename... Us>
    struct append<T<Us...>> : append<Us...> {};

    template <typename... Ls>
    struct prepend {
        using type = type_multiset<Ls...>;
    };

    template <template <typename...> class T, typename... Us>
    struct prepend<T<Us...>> : prepend<Us...> {};

    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<>>;

    template <typename T>
    constexpr static auto index = -1;

    template <typename T>
    constexpr static bool contains = false;

    using pop_front = this_type__;

    using pop_back = this_type__;

    using reverse = this_type__;

    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_type__::cardinality, "splice index out of range of type set");
            using left = this_type__;
            using right = this_type__;
        };
    };
};

template <typename... Ts>
class [[nodiscard]] type_multiset {
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
    }(std::make_index_sequence<this_type__::cardinality - 1>{}))::type;

    using pop_back = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_type__::get<i>...>>{};
    }(std::make_index_sequence<this_type__::cardinality - 1>{}))::type;

    using reverse = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_type__::get<this_type__::cardinality - 1 - i>...>>{};
    }(std::make_index_sequence<this_type__::cardinality>{}))::type;

    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_type__::cardinality, "splice index out of range of type set");
            using left = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_multiset<this_type__::get<is>...>>{};
            }(std::make_index_sequence<i>{}))::type;

            using right = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_multiset<this_type__::get<i + is>...>>{};
            }(std::make_index_sequence<this_type__::cardinality - i>{}))::type;
        };
    };
};

}  // namespace ndo