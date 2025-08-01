#pragma once
#include <iostream>
#include <tuple>

namespace ndo {
template <typename... Ts>
class [[nodiscard]] type_multiset;

template <>
class type_multiset<> {
    using this_t = type_multiset<>;

   public:
    constexpr static std::size_t cardinality = 0;
    using as_tuple = std::tuple<>;
    using as_variant = std::variant<>;
    template <typename... Ls>
    struct append {
        using type = type_multiset<Ls...>;
    };
    template <typename... Ls>
    struct prepend {
        using type = type_multiset<Ls...>;
    };
    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<>>;
    template <typename T>
    constexpr static auto index = -1;
    template <typename T>
    constexpr static bool contains = false;
    template <std::size_t idx, typename T>
    constexpr static bool contains_from = false;
    using pop_front = this_t;
    using pop_back = this_t;
    using reverse = this_t;
    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_t::cardinality, "splice index out of range of type set");
            using left = this_t;
            using right = this_t;
        };
    };

   public:
    constexpr static bool is_unique = true;
    using unique = this_t;
};

namespace internal {
template <typename... Ts>
struct unique_impl;

template <>
struct unique_impl<> {
    using rest = std::tuple<>;
    using type = std::tuple<>;
};

template <typename T, typename... Ts>
struct unique_impl<T, Ts...> {
    using rest = unique_impl<Ts...>::type;
    constexpr static bool contains_it = (std::is_same_v<T, Ts> || ...);
    using type = std::conditional_t<
        contains_it,
        rest,
        decltype(std::tuple_cat(std::declval<std::tuple<T>>(), std::declval<rest>()))>;
};

};  // namespace internal

template <typename... Ts>
class [[nodiscard]] type_multiset {
    using this_t = type_multiset<Ts...>;

   public:
    constexpr static std::size_t cardinality = sizeof...(Ts);
    using as_tuple = std::tuple<Ts...>;
    using as_variant = std::variant<Ts...>;

    template <typename T>
    struct as_this;

    template <template <typename...> class T, typename... Us>
    struct as_this<T<Us...>> {
        using type = type_multiset<Us...>;
    };

    template <typename... Ls>
    struct append {
        using type = type_multiset<Ts..., Ls...>;
    };

    template <typename... Ls>
    struct prepend {
        using type = type_multiset<Ls..., Ts...>;
    };

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

   public:
    using unique = as_this<typename internal::unique_impl<Ts...>::type>::type;
};

}  // namespace ndo