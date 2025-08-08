#pragma once
#include <iostream>

#include "../algebraic/maybe.hpp"
namespace ndo {

template <typename F, typename Cont>
    requires(std::is_invocable_r_v<bool, F, typename Cont::value_type>)
[[nodiscard]] constexpr static auto all_of(const Cont& cont, F&& f) noexcept {
    Cont out{};
    for (const auto& v : cont) {
        if (std::invoke(f, v)) {
            out.insert(out.end(), v);
        }
    }
    return out;
};

};  // namespace ndo