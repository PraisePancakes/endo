#pragma once
#include <iostream>

namespace ndo {

template <std::size_t N>
using index_type = std::integral_constant<std::size_t, N>;

template <typename... Fs>
struct visitor : Fs... {
    using Fs::operator()...;
};

template <typename... Fs>
visitor(Fs...) -> visitor<Fs...>;

};  // namespace ndo