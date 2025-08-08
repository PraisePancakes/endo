#include <iostream>
#include <string>

#include "test/test.hpp"

int main(int argc, char** argv) {
    ndo::echo(std::cout, std::vector<int>{1, 2, 3, 4});
    return 0;
}