#pragma once
#include <iostream>
#include <sstream>

#include "../concepts/is_standard_container.hpp"
#include "../concepts/streamable.hpp"

namespace ndo {
namespace internal {
template <typename T>
struct is_vector : std::false_type {};

template <typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type {};

template <typename T>
concept Vector = is_vector<T>::value;

template <Vector T>
constexpr static void handler(std::ostream& os, T arg) noexcept {
    os << '[';
    for (std::size_t i = 0; i < arg.size(); i++) {
        os << arg[i];
        if (i < arg.size() - 1) {
            os << ',';
        }
    };
    os << ']';
};

template <ndo::Streamable T>
constexpr static void handler(std::ostream& os, T arg) noexcept {
    os << arg;
};
}  // namespace internal

template <typename... Ts>
constexpr static void echo(std::ostream& os, Ts&&... args) noexcept {
    ((internal::handler(os, args)), ...);
};
}  // namespace ndo