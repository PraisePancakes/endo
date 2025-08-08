#pragma once

namespace ndo {

/**
 * \concept satisfies_it
 * \brief Concept that checks if a template lambda or functor `F` can be invoked with template parameters `Ts...`.
 *
 * This checks if `F.template operator()<Ts...>()` is a valid expression.
 *
 * @tparam F A template callable with a templated `operator()`.
 * @tparam Ts Template parameter pack to test the call with.
 */
template <auto F, typename... Ts>
concept satisfies_it = requires { F.template operator()<Ts...>(); };

}  // namespace ndo
