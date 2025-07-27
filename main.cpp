#include <iostream>

#include "test/test.hpp"

int main(int argc, char** argv) {
    ndo::test::test_maybe();
    ndo::test::test_function_traits();
    ndo::test::test_either();
    ndo::test::test_compositor();
    ndo::test::test_curry();
    ndo::test::test_uncurry();
    ndo::test::test_combinator();
    ndo::test::test_transform();
    ndo::test::test_type_multiset();
    return 0;
}