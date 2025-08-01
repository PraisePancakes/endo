#pragma once
#include <iostream>
#include <tuple>
#include <variant>

namespace ndo {
template <typename... Ts>
class [[nodiscard]] type_multiset;

template <typename T>
struct as_type_multiset;

template <template <typename...> class T, typename... Ts>
struct as_type_multiset<T<Ts...>> : type_multiset<Ts...> {};

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

    template <typename... Ls>
    struct prepend {
        using type = type_multiset<Ls..., Ts...>;
    };

    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<Ts...>>;

    template <typename T>
    constexpr static bool contains = (std::is_same_v<T, Ts> || ...);

    template <typename T>
    constexpr static auto index = []() {
        return ((std::is_same_v<T, Ts> || ...) ? (([]() {
            signed i = 0;
            (... && (!std::is_same_v<T, Ts> && ++i));
            return i;
        }()))
                                               : -1);
    }();

    template <std::size_t idx, typename T>
    constexpr static bool contains_from = []<std::size_t... i>(std::index_sequence<i...>) {
        using ts = type_multiset<this_t::get<i + idx>...>;
        static_assert(idx >= 0 || idx < ts::cardinality, "index out of constexpr range of type set");
        return ts::template contains<T>;
    }(std::make_index_sequence<sizeof...(Ts) - idx>{});

    using pop_front = decltype([]() {
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_multiset<>>{};
        } else {
            return []<std::size_t... i>(std::index_sequence<i...>) {
                return std::type_identity<type_multiset<this_t::get<i + 1>...>>{};
            }(std::make_index_sequence<this_t::cardinality - 1>{});
        }
    }())::type;

    using pop_back = decltype([]() { 
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_multiset<>>{};
        } else {
        return []<std::size_t... i>(std::index_sequence<i...>) {
                                         return std::type_identity<type_multiset<this_t::get<i>...>>{};
                                     }(std::make_index_sequence<this_t::cardinality - 1>{}); } }())::type;

    using reverse = decltype([]() { 
         if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_multiset<>>{};
        } else {
        return []<std::size_t... i>(std::index_sequence<i...>) {
                                        return std::type_identity<type_multiset<this_t::get<this_t::cardinality - 1 - i>...>>{};
                                    }(std::make_index_sequence<this_t::cardinality>{}); } }())::type;

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
    using strictly_unique = decltype([](std::tuple<std::type_identity<Ts>...>&& tup) consteval {
        return std::apply([](auto&&... args) {
            return std::tuple_cat([](auto&& arg) {
                using extract = typename std::remove_reference_t<decltype(arg)>::type;
                constexpr bool contains_it = this_t::template contains_from<this_t::template index<extract> + 1, extract>;
                if constexpr (!contains_it) {
                    return std::make_tuple(std::forward<decltype(arg)>(arg));
                } else {
                    return std::make_tuple();
                }
            }(std::forward<decltype(args)>(args))...);
        },
                          tup);
    }(std::make_tuple(std::type_identity<Ts>{}...)));
};
};  // namespace ndo
