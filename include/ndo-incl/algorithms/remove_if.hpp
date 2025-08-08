#pragma once
#include <iostream>
namespace ndo {

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

};  // namespace ndo
