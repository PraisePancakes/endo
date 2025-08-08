#pragma once
#include "name_of.hpp"

namespace ndo {
template <typename T>
struct type_descriptor {
    constexpr static std::string stringify() {
        if constexpr (std::is_const_v<T>) {
            return "const " + type_descriptor<std::remove_const_t<T>>().stringify();
        }
        if constexpr (std::is_pointer_v<T>) {
            return type_descriptor<std::remove_pointer_t<T>>().stringify() + "*";
        }
        if constexpr (std::is_reference_v<T>) {
            return type_descriptor<std::remove_reference_t<T>>().stringify() + "&";
        }

        return name_of<T>::value;
    };
};
}  // namespace ndo