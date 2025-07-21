#include <iostream>

#include "test/test.hpp"

int main(int argc, char** argv) {
    ndo::test::test_maybe();
    ndo::test::test_function_traits();
    ndo::test::test_either();
    return 0;
}