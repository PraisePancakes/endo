#pragma once
#include <iostream>
#include <tuple>

namespace ndo {
template <typename... Ts>
struct type_set;
}

namespace ndo::internal {

template <typename Tuple>
struct tuple_identity_to_multiset;

template <typename... Idents>
struct tuple_identity_to_multiset<std::tuple<Idents...>> {
    using type = ndo::type_set<typename Idents::type...>;
};
}  // namespace ndo::internal