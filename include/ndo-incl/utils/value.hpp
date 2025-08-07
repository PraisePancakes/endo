#pragma once
#include <iostream>

namespace ndo {
template <std::size_t C>
using value = std::integral_constant<std::size_t, C>;
}