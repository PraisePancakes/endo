#pragma once
#include <functional>
#include <tuple>
#include <type_traits>

namespace ndo {

/**
 * \brief Extracts type traits from callable types.
 *
 * Provides information such as return type, argument types,
 * and arity (number of arguments) for various callable types,
 * including function pointers, member function pointers,
 * functors (lambdas), and std::function.
 *
 * Usage example:
 * \code
 * auto lambda = [](int a, double b) -> bool { return a < b; };
 * using traits = ndo::function_traits<decltype(lambda)>;
 * static_assert(std::is_same_v<traits::return_t, bool>);
 * static_assert(traits::arity == 2);
 * using first_arg = traits::arg_t<0>; // int
 * \endcode
 *
 * @tparam F Callable type to inspect.
 */
template <typename Ret, typename... Args>
struct function_traits_meta {
    using return_t = Ret;
    using sig_t = Ret (*)(Args...);
    constexpr static std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    using arg_t = std::tuple_element_t<N, std::tuple<Args...>>;

    using args = std::tuple<Args...>;
};

// Primary template: Deduce operator() for functors (lambdas)
template <typename F>
struct function_traits : function_traits<std::remove_cvref_t<decltype(&F::operator())>> {};

// Function type specialization
template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> : function_traits_meta<Ret, Args...> {};

// Function pointer specialization
template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> : function_traits_meta<Ret, Args...> {};

// Member function pointer specialization (non-const)
template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...)> : function_traits_meta<Ret, Args...> {};

// Member function pointer specialization (const)
template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...) const> : function_traits_meta<Ret, Args...> {};

// std::function specialization
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits_meta<Ret, Args...> {};

}  // namespace ndo
