#pragma once
#include <string>
#include <type_traits>

#include "name_of.hpp"

namespace ndo {

/**
 * \brief Provides a human-readable string representation of a type `T`.
 *
 * Recursively unwraps const qualifiers, pointers, and references
 * to build a descriptive string of the type.
 *
 * Example:
 * \code
 * using T = const int*&;
 * std::string desc = ndo::type_descriptor<T>::stringify();
 * // desc == "const int*&"
 * \endcode
 *
 * @tparam T The type to describe.
 */
template <typename T>
struct type_descriptor {
    constexpr static std::string stringify() {
        if constexpr (std::is_const_v<T>) {
            return "const " + type_descriptor<std::remove_const_t<T>>::stringify();
        }
        if constexpr (std::is_pointer_v<T>) {
            return type_descriptor<std::remove_pointer_t<T>>::stringify() + "*";
        }
        if constexpr (std::is_reference_v<T>) {
            return type_descriptor<std::remove_reference_t<T>>::stringify() + "&";
        }
        return name_of<T>::value;
    }
};

}  // namespace ndo
