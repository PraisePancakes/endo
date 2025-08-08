#pragma once
#include <iostream>

namespace ndo {

/**
 * \concept is_specialization_of
 * \brief Concept that checks if a type `T` is a specialization of a class template `Template`.
 *
 * Example:
 * \code
 * template <typename... Args> struct MyTemplate {};
 * static_assert(is_specialization_of<MyTemplate<int, double>, MyTemplate>);
 * \endcode
 *
 * @tparam T The type to check.
 * @tparam Template The class template to check against.
 */
template <class T, template <typename...> class Template>
concept is_specialization_of = requires(T const &t) {
    []<typename... Args>(Template<Args...> const &) { return true; }(t);
};

}  // namespace ndo
