#pragma once
#include <array>
#include <iostream>
#include <tuple>

#include "../utils/value.hpp"

namespace ndo {

template <typename Container, typename F>
    requires(std::is_invocable_v<F, typename Container::value_type>)
[[nodiscard]] constexpr auto map_from(const Container& cont, F&& f) noexcept(
    noexcept(std::is_nothrow_invocable_v<F, typename Container::value_type>)) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        const auto v = *it;
        ret.insert(ret.end(), std::move(std::invoke(std::forward<F>(f), std::move(v))));
    }
    return ret;
};

template <typename Container, typename Cond>
    requires(std::is_invocable_r_v<bool, Cond, typename Container::value_type>)
[[nodiscard]] constexpr auto keep_if(const Container& cont, Cond&& c) noexcept(
    noexcept(std::is_nothrow_invocable_v<Cond, typename Container::value_type>)) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        const auto v = *it;
        if (std::invoke(c, v)) {
            ret.insert(ret.end(), std::move(v));
        }
    };
    return ret;
};

template <typename Container, typename Cond>
    requires(std::is_invocable_r_v<bool, Cond, typename Container::value_type>)
[[nodiscard]] constexpr auto remove_if(const Container& cont, Cond&& c) noexcept(
    noexcept(std::is_nothrow_invocable_v<Cond, typename Container::value_type>)) {
    Container ret{};
    for (auto it = cont.cbegin(); it != cont.cend(); ++it) {
        const auto v = *it;
        if (!std::invoke(c, v)) {
            ret.insert(ret.end(), std::move(v));
        }
    };
    return ret;
};

template <typename Container>
[[nodiscard]] constexpr auto reverse(const Container& cont) noexcept {
    Container ret{};
    for (auto it = cont.crbegin(); it != cont.crend(); ++it) {
        const auto v = *it;
        ret.insert(ret.end(), std::move(v));
    }
    return ret;
};

template <typename T1, typename T2>
    requires(std::tuple_size_v<T1> == std::tuple_size_v<T2>)
[[nodiscard]] constexpr auto zip(const T1& t1, const T2& t2) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::make_tuple([&]<std::size_t idx>(ndo::value<idx>) {
            return std::make_pair(std::get<idx>(t1), std::get<idx>(t2));
        }(ndo::value<i>{})...);
    }(std::make_index_sequence<std::tuple_size_v<T1>>{});
};

template <typename T>
[[nodiscard]] constexpr auto unzip(const T& t) noexcept {
    return [&]<std::size_t... i>(std::index_sequence<i...>) {
        return std::tuple_cat([&]<std::size_t idx>(ndo::value<idx>) {
            return std::make_pair(std::get<idx>(t).first, std::get<idx>(t).second);
        }(ndo::value<i>{})...);
    }(std::make_index_sequence<std::tuple_size_v<T>>{});
}

};  // namespace ndo
