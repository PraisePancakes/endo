#pragma once
#include <functional>

namespace ndo {
template <typename Ret, typename... Args>
struct function_traits_base {
    using return_t = Ret;
    using sig_t = Ret (*)(Args...);
    constexpr static std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    using arg_t = std::tuple_element_t<N, std::tuple<Args...>>;
};

template <typename F>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> : function_traits_base<Ret, Args...> {};

template <typename Ret, typename... Args>
struct function_traits<Ret (*)(Args...)> : function_traits_base<Ret, Args...> {};

template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...)> : function_traits_base<Ret, Args...> {};

template <typename Class, typename Ret, typename... Args>
struct function_traits<Ret (Class::*)(Args...) const> : function_traits_base<Ret, Args...> {};

template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits_base<Ret, Args...> {};

template <typename Func>
struct function_traits : function_traits<std::remove_cv_t<decltype(&Func::operator())>> {};
};  // namespace ndo