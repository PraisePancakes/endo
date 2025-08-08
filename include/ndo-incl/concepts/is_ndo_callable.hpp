#pragma once
#include <iostream>
#include <type_traits>

#include "../meta/function_traits.hpp"

namespace ndo {

/**
 * \concept ndo_callable
 * \brief Concept that checks if a type is callable and compatible with `function_traits`.
 *
 * This concept requires that:
 * - The type `T` has a callable `operator()` (for functors, lambdas).
 * - The `function_traits<T>` is well-formed.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept ndo_callable = requires {
    typename std::void_t<decltype(&std::remove_cvref_t<T>::operator())>;
} && requires {
    typename std::void_t<function_traits<T>>;
};

}  // namespace ndo
