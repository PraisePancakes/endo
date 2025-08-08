#pragma once
#include <iostream>

namespace ndo {

template <typename F, typename Container>
    requires(std::is_invocable_r_v<bool, F, typename Container::value_type>)
[[nodiscard]] constexpr static bool has_if(const Container& cont, F&& f) noexcept(
    noexcept(std::is_nothrow_invocable_r_v<bool, F, typename Container::value_type>)) {
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            return true;
        }
    };
    return false;
};

}  // namespace ndo