#pragma once
#include <iostream>
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

};  // namespace ndo
