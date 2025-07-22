#pragma once
#include <iostream>

#include "function_traits.hpp"
namespace ndo {

// f(int, char, bool) -> (F) => g(int)(char)(bool)
template <typename TF>
constexpr decltype(auto) curry(TF&& f) {
    if constexpr (std::is_invocable_v<TF>) {
        return std::forward<TF>(f)();
    } else {
        
    };
}

};  // namespace ndo