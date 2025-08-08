#pragma once
#include <type_traits>

namespace ndo {

/**
 * \brief Trait to detect if a function type is declared `noexcept`.
 *
 * Primary template defaults to `false`.
 *
 * @tparam F The function type to check.
 */
template <typename F>
struct is_noexcept : std::false_type {};

/**
 * \brief Specialization for `noexcept` function types sets to `true`.
 *
 * Matches function types declared with `noexcept`.
 */
template <typename F, typename... Args>
struct is_noexcept<F(Args...) noexcept> : std::true_type {};

}  // namespace ndo
