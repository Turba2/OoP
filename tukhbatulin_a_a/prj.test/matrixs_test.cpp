#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <matrixs/matrixs.hpp>
#include <iostream>

TEST_CASE("[matrixs] - MatrixS throws") {
    MatrixS a;
    a = MatrixS(2, 2);
    int b = 0;
    CHECK_THROWS(a.at(-1, 0));
    CHECK_THROWS(a.at(2, 0));
    CHECK_THROWS(a.at(-1, 0) = 1);
    CHECK_THROWS(a.at(2, 0) = 1);
}