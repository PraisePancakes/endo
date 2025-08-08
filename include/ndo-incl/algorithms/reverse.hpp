#pragma once
#include <iostream>
namespace ndo {

template <typename Container>
[[nodiscard]] constexpr auto reverse(const Container& cont) noexcept {
    Container ret{};
    for (auto it = cont.crbegin(); it != cont.crend(); ++it) {
        const auto v = *it;
        ret.insert(ret.end(), std::move(v));
    }
    return ret;
};

};  // namespace ndo
