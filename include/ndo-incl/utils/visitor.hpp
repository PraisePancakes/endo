#pragma once
#include <iostream>

namespace ndo {

template <typename... Fs>
struct visitor : Fs... {
    using Fs::operator()...;
};

template <typename... Fs>
visitor(Fs...) -> visitor<Fs...>;

};  // namespace ndo