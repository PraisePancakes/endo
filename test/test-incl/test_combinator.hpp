#pragma once
#include "../../include/ndo.hpp"
namespace ndo::test {

void test_combinator() {
    auto fact = make_y_combinator([](auto self, int n) -> int {
        return n <= 1 ? 1 : n * self(n - 1);
    });

    auto logger = [](auto f) {
        return [xf = std::forward<decltype(f)>(f)](auto&&... args) mutable {
            std::cout << xf(std::forward<decltype(args)>(args)...) << std::endl;
        };
    };

    auto fact_log = logger(fact);

    fact_log(5);
};
};  // namespace ndo::test