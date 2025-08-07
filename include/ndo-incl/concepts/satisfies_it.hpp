#pragma once

namespace ndo {
template <auto F, typename... Ts>
concept satisfies_it = requires { F.template operator()<Ts...>(); };
} 