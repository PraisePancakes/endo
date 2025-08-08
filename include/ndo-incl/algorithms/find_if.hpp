#pragma once
#include <iostream>

#include "../algebraic/maybe.hpp"
namespace ndo {

template <typename F, typename Cont>
    requires(std::is_invocable_r_v<bool, F, typename Cont::value_type>)
[[nodiscard]] constexpr static auto find_if(const Cont& cont, F&& f) noexcept {
    using maybe_t = ndo::maybe<typename Cont::value_type>;
    maybe_t mayb;
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            typename Cont::value_type ret{v};
            mayb = ret;
        }
    }
    return mayb;
};

};  // namespace ndo