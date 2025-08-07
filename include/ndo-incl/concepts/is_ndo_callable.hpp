#pragma once
#include <iostream>

#include "../meta/function_traits.hpp"

namespace ndo {
template <typename T>
concept ndo_callable = requires {
    typename std::void_t<decltype(&std::remove_cvref_t<T>::operator())>;
} && requires {
    typename std::void_t<function_traits<T>>;
};
}  // namespace ndo