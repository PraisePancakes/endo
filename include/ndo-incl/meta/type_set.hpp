#pragma once
#include <iostream>
#include <tuple>
#include <variant>

#include "../concepts/satisfies_it.hpp"
#include "../utils/convert.hpp"
#include "../utils/value.hpp"

namespace ndo {

/**
 * \ingroup algebraic
 * \brief A compile-time set of types providing metaprogramming utilities.
 *
 * The `type_set` class represents a set of types and provides
 * compile-time operations such as containment checks, indexing,
 * appending, prepending, filtering, uniqueness, slicing, and more.
 *
 * It is primarily a utility for advanced template metaprogramming, enabling
 * manipulation and queries on type lists.
 *
 * @tparam Ts List of types contained in the set.
 */
template <typename... Ts>
class [[nodiscard]] type_set;

template <template <typename...> class T, typename... Ts>
struct type_set<T<Ts...>> : type_set<Ts...> {};

/**
 * @tparam Ts Variadic list of types forming the set.
 */
template <typename... Ts>
class [[nodiscard]] type_set {
    using this_t = type_set<Ts...>;

   public:
    /// Number of types in the set.
    constexpr static std::size_t cardinality = sizeof...(Ts);

    /// The set represented as a std::tuple of types.
    using as_tuple = std::tuple<Ts...>;

    /// The set represented as a std::variant of types.
    using as_variant = std::variant<Ts...>;

    /**
     * @brief Append types `Ls...` to the end of this type_set.
     */
    template <typename... Ls>
    struct append {
        using type = type_set<Ts..., Ls...>;
    };

    /**
     * @brief Prepend types `Ls...` to the front of this type_set.
     */
    template <typename... Ls>
    struct prepend {
        using type = type_set<Ls..., Ts...>;
    };

    /**
     * @brief Get the type at index `I` (zero-based).
     */
    template <std::size_t I>
    using get = std::tuple_element_t<I, std::tuple<Ts...>>;

    /**
     * @brief Checks if `T` is contained in the type_set.
     */
    template <typename T>
    constexpr static bool contains = (std::is_same_v<T, Ts> || ...);

    /**
     * @brief Returns the zero-based index of `T` in the type_set, or -1 if not found.
     *
     * The index is computed at compile-time using constexpr lambda and fold expressions.
     */
    template <typename T>
    constexpr static auto index = []() {
        return ((std::is_same_v<T, Ts> || ...) ? (([]() {
            signed i = 0;
            (... && (!std::is_same_v<T, Ts> && ++i));
            return i;
        }()))
                                               : -1);
    }();

    /**
     * @brief Checks if `T` appears in the type_set from index `idx` to the end.
     * @tparam idx The starting index.
     * @tparam T The type to check.
     */
    template <std::size_t idx, typename T>
    constexpr static bool contains_from = []<std::size_t... i>(std::index_sequence<i...>) constexpr noexcept {
        static_assert(idx < this_t::cardinality, "Index out of range");
        using type = std::tuple<Ts...>;
        return (std::is_same_v<std::tuple_element_t<idx + i, type>, T> || ...);
    }(std::make_index_sequence<this_t::cardinality - idx>{});

    /**
     * @brief Checks if `T` appears in the type_set from the beginning up to (but not including) index `idx`.
     * @tparam idx The ending index (exclusive).
     * @tparam T The type to check.
     */
    template <std::size_t idx, typename T>
    constexpr static bool contains_to = []<std::size_t... i>(std::index_sequence<i...>) constexpr noexcept {
        using type = std::tuple<Ts...>;
        return (... || std::is_same_v<std::tuple_element_t<i, type>, T>);
    }(std::make_index_sequence<idx>{});

    /**
     * @brief Returns a type_set with the first element removed.
     * If the set is empty, returns an empty type_set.
     */
    using pop_front = decltype([]() {
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
            return []<std::size_t... i>(std::index_sequence<i...>) {
                return std::type_identity<type_set<this_t::get<i + 1>...>>{};
            }(std::make_index_sequence<this_t::cardinality - 1>{});
        }
    }())::type;

    /**
     * @brief Returns a type_set with the last element removed.
     * If the set is empty, returns an empty type_set.
     */
    using pop_back = decltype([]() {
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
            return []<std::size_t... i>(std::index_sequence<i...>) {
                return std::type_identity<type_set<this_t::get<i>...>>{};
            }(std::make_index_sequence<this_t::cardinality - 1>{});
        }
    }())::type;

    /**
     * @brief Returns a type_set with elements in reverse order.
     */
    using reverse = decltype([]() {
        if constexpr (this_t::cardinality == 0) {
            return std::type_identity<type_set<>>{};
        } else {
            return []<std::size_t... i>(std::index_sequence<i...>) {
                return std::type_identity<type_set<this_t::get<this_t::cardinality - 1 - i>...>>{};
            }(std::make_index_sequence<this_t::cardinality>{});
        }
    }())::type;

    /**
     * @brief Helper struct to split the type_set at index `i`.
     *
     * The resulting `left` type_set contains elements [0, i)
     * The resulting `right` type_set contains elements [i, end)
     */
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

    /**
     * @brief Returns a unique-filtered version of the type_set,
     * removing duplicate types while preserving order of first occurrence.
     */
    using unique = internal::tuple_identity_to_multiset<
        decltype([]<std::size_t... i>(std::index_sequence<i...>) mutable constexpr {
            return std::tuple_cat(
                [nt = std::make_tuple(std::type_identity<Ts>{}...)]<std::size_t idx>(ndo::value<idx>) {
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
                }(ndo::value<i>{})...);
        }(std::make_index_sequence<this_t::cardinality>{}))>::type;

    /**
     * @brief Filter the type_set based on a compile-time predicate `Cond`.
     *
     * Only types `T` for which `Cond::template operator()<T>()` returns true
     * are included in the resulting type_set.
     *
     * @tparam Cond A callable with a templated operator() that takes a type and returns bool.
     */
    template <auto Cond>
    using filter = internal::tuple_identity_to_multiset<
        decltype([]<std::size_t... i>(std::index_sequence<i...>) mutable constexpr {
            return std::tuple_cat(
                [nt = std::make_tuple(std::type_identity<Ts>{}...)]<std::size_t idx>(ndo::value<idx>) {
                    if constexpr (ndo::satisfies_it<Cond, typename std::tuple_element_t<
                                                              idx, decltype(nt)>::type>) {
                        return std::make_tuple(std::get<idx>(nt));
                    } else {
                        return std::make_tuple();
                    }
                }(ndo::value<i>{})...);
        }(std::make_index_sequence<this_t::cardinality>{}))>::type;

    /// True if the type_set contains only unique types (no duplicates).
    constexpr static bool is_unique = []() constexpr { return this_t::cardinality == this_t::unique::cardinality; }();

    /**
     * @brief Remove the type at index `I` from the type_set.
     *
     * @tparam I Index of the type to remove.
     */
    template <std::size_t I>
    using remove_at = internal::tuple_identity_to_multiset<
        decltype([]<std::size_t... i>(std::index_sequence<i...>) mutable constexpr {
            return std::tuple_cat(
                [nt = std::make_tuple(std::type_identity<Ts>{}...)]<std::size_t idx>(ndo::value<idx>) {
                    if constexpr (idx == I) {
                        return std::make_tuple();
                    } else {
                        return std::make_tuple(std::get<idx>(nt));
                    }
                }(ndo::value<i>{})...);
        }(std::make_index_sequence<this_t::cardinality>{}))>::type;
};

}  // namespace ndo
