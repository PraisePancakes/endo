#pragma once
#include <iostream>

namespace ndo {
template <class T, template <typename...> class Template>
concept is_specialization_of = requires(T const &t) {
    []<typename... Args>(Template<Args...> const &) { return true; }(t);
};
}  // namespace ndo