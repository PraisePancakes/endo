#pragma once
#include <iostream>

#include "../include/ndo.hpp"
namespace ndo::examples {
void either_ex() {
    ndo::either<std::string, int> e;

    e = 0;

    if (e.has_value()) {
        std::cout << "has it : " << e.just_or_throw() << std::endl;
    } else {
        std::cout << "doesnt have it : " << e.error_or_default() << std::endl;
    };

    auto v = e.and_then([](int x) { return "hi"; }).and_then([](const char* v) { return 10; });

    std::cout << v.just_or(0) << std::endl;
};

void maybe_ex() {
    ndo::maybe<int> may5{10};
    auto lam = [](int x) { return "hello"; };
    std::string ctad = may5.map_or_throw(lam);
    std::size_t strict = may5.map_or_throw<std::string>(lam).size();
    std::cout << ctad << " : " << strict << std::endl;

    ndo::maybe<std::vector<int>> may7{{56, 1, 2, 3}};

    auto lam3 = [](std::vector<int> v) {
        return 4;
    };

    auto lam4 = [](int v) {
        return ndo::ndo_nothing;
    };

    auto v = may7.and_then(lam3).and_then(lam4).and_then(lam4);

    std::cout << std::boolalpha << v.has_value() << std::endl;
};
}  // namespace ndo::examples