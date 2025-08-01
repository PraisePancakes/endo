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

namespace helper {
template <typename... T>
struct unique_impl;

template <>
struct unique_impl<> {
    using type = std::tuple<>;
};
template <typename H, typename... Tail>
struct unique_impl<H, Tail...> {
    constexpr static bool is_dup = (... || std::is_same_v<H, Tail>);
    using tail = unique_impl<Tail...>::type;
    using type = std::conditional_t<
        is_dup,
        tail,
        decltype(std::tuple_cat(std::tuple<H>{}, tail{}))>;
};
template <typename T>
struct from_tuple;

template <typename... Us>
struct from_tuple<std::tuple<Us...>> {
    using type = type_multiset<Us...>;
};

}  // namespace helper

template <>
struct type_multiset<> {
    using this_t = type_multiset<>;

   public:
    using pop_front = this_t;

    using pop_back = this_t;

    using reverse = this_t;

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

    using as_tuple = std::tuple<>;
    using as_variant = std::variant<>;

    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_t::cardinality, "splice index out of range of type set");
            using left = this_t;
            using right = this_t;
        };
    };
};

template <typename... Ts>
class [[nodiscard]] type_multiset {
    using this_t = type_multiset<Ts...>;

   public:
    constexpr static std::size_t cardinality = sizeof...(Ts);
    using as_tuple = std::tuple<Ts...>;
    using as_variant = std::variant<Ts...>;

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

    template <std::size_t idx, typename T>
    constexpr static bool contains_from = []<std::size_t... i>(std::index_sequence<i...>) {
        using ts = type_multiset<this_t::get<i + idx>...>;
        static_assert(idx >= 0 || idx < ts::cardinality, "index out of constexpr range of type set");
        return ts::template contains<T>;
    }(std::make_index_sequence<sizeof...(Ts) - idx>{});

    using pop_front = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_t::get<i + 1>...>>{};
    }(std::make_index_sequence<this_t::cardinality - 1>{}))::type;

    using pop_back = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_t::get<i>...>>{};
    }(std::make_index_sequence<this_t::cardinality - 1>{}))::type;

    using reverse = decltype([]<std::size_t... i>(std::index_sequence<i...>) {
        return std::type_identity<type_multiset<this_t::get<this_t::cardinality - 1 - i>...>>{};
    }(std::make_index_sequence<this_t::cardinality>{}))::type;

    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_t::cardinality, "splice index out of range of type set");
            using left = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_multiset<this_t::get<is>...>>{};
            }(std::make_index_sequence<i>{}))::type;

            using right = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_multiset<this_t::get<i + is>...>>{};
            }(std::make_index_sequence<this_t::cardinality - i>{}))::type;
        };
    };

    constexpr static bool is_unique = []<std::size_t... i>(std::index_sequence<i...>) constexpr {
        return ((!this_t::contains_from<i + 1, Ts>) && ...);
    }(std::make_index_sequence<sizeof...(Ts)>{});

   private:
   public:
    using unique = typename helper::from_tuple<typename helper::unique_impl<Ts...>::type>::type;
};

}  // namespace ndo