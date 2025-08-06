#pragma once
#include <iostream>
#include <tuple>
#include <variant>

namespace ndo {
template <typename... Ts>
class [[nodiscard]] type_set;

template <template <typename...> class T, typename... Ts>
struct type_set<T<Ts...>> : type_set<Ts...> {};

namespace internal {
template <typename Tuple>
struct tuple_identity_to_multiset;

template <typename... Idents>
struct tuple_identity_to_multiset<std::tuple<Idents...>> {
    using type = type_set<typename Idents::type...>;
};

template <std::size_t C>
using value = std::integral_constant<std::size_t, C>;
}  // namespace internal

template <auto F, typename... Ts>
concept satisfies_it = requires { F.template operator()<Ts...>(); };

template <typename... Ts>
class [[nodiscard]] type_set {
    using this_t = type_set<Ts...>;

   public:
    constexpr static std::size_t cardinality = sizeof...(Ts);
    using as_tuple = std::tuple<Ts...>;
    using as_variant = std::variant<Ts...>;

    template <typename... Ls>
    struct append {
        using type = type_set<Ts..., Ls...>;
    };

    template <typename... Ls>
    struct prepend {
        using type = type_set<Ls..., Ts...>;
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
    constexpr static bool contains_from = []<std::size_t... i>(std::index_sequence<i...>) constexpr noexcept {
        static_assert(idx < this_t::cardinality, "Index out of range");
        using type = std::tuple<Ts...>;
        return (std::is_same_v<std::tuple_element_t<idx + i, type>, T> || ...);
    }(std::make_index_sequence<this_t::cardinality - idx>{});

    template <std::size_t idx, typename T>
    constexpr static bool contains_to = []<std::size_t... i>(std::index_sequence<i...>) constexpr noexcept {
        using type = std::tuple<Ts...>;
        return (... || std::is_same_v<std::tuple_element_t<i, type>, T>);
    }(std::make_index_sequence<idx>{});

    using pop_front = decltype([]() {
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
            return []<std::size_t... i>(std::index_sequence<i...>) {
                return std::type_identity<type_set<this_t::get<i + 1>...>>{};
            }(std::make_index_sequence<this_t::cardinality - 1>{});
        }
    }())::type;

    using pop_back = decltype([]() { 
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
        return []<std::size_t... i>(std::index_sequence<i...>) {
                                         return std::type_identity<type_set<this_t::get<i>...>>{};
                                     }(std::make_index_sequence<this_t::cardinality - 1>{}); } }())::type;

    using reverse = decltype([]() { 
         if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
        return []<std::size_t... i>(std::index_sequence<i...>) {
                                        return std::type_identity<type_set<this_t::get<this_t::cardinality - 1 - i>...>>{};
                                    }(std::make_index_sequence<this_t::cardinality>{}); } }())::type;

    struct splicer {
        template <std::size_t i>
        struct at {
            static_assert(i < this_t::cardinality, "splice index out of range of type set");
            using left = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_set<this_t::get<is>...>>{};
            }(std::make_index_sequence<i>{}))::type;

            using right = decltype([]<std::size_t... is>(std::index_sequence<is...>) {
                return std::type_identity<type_set<this_t::get<i + is>...>>{};
            }(std::make_index_sequence<this_t::cardinality - i>{}))::type;
        };
    };

    using unique = internal::tuple_identity_to_multiset<decltype([ot = std::make_tuple(std::type_identity<Ts>{}...)]<std::size_t... i>(std::index_sequence<i...>) mutable constexpr {
        return std::tuple_cat([nt = std::forward<decltype(ot)>(ot)]<std::size_t idx>(internal::value<idx>) {
            if constexpr (idx == 0) {
                return std::make_tuple(std::get<0>(nt));
            } else if constexpr (idx > 0 && idx < this_t::cardinality &&
                                 !this_t::template contains_to<
                                     idx, typename std::tuple_element_t<
                                              idx, decltype(nt)>::type>) {
                return std::make_tuple(std::get<idx>(nt));
            } else {
                return std::make_tuple();
            }
        }(internal::value<i>{})...);
    }(std::make_index_sequence<this_t::cardinality>{}))>::type;

    // eczbeck dont get mad, i like this idea
    template <auto Cond>
    using filter = internal::tuple_identity_to_multiset<decltype([xt = std::make_tuple(std::type_identity<Ts>{}...)]() mutable constexpr {
        return std::apply([](auto&&... args) {
            return std::tuple_cat([](auto&& arg) {
                if constexpr (satisfies_it<Cond, typename std::remove_reference_t<decltype(arg)>::type>) {
                    return std::make_tuple(arg);
                } else {
                    return std::make_tuple();
                }
            }(args)...);
        },
                          std::forward<decltype(xt)>(xt));
    }())>::type;

    constexpr static bool is_unique = []() constexpr { return this_t::cardinality == this_t::unique::cardinality; }();
};
};  // namespace ndo
