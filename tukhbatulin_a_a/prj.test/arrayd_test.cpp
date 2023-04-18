#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayd/arrayd.hpp>
#include <iostream>

TEST_CASE("test ctor"){
    ArrayD a(3), b(3);
    a = ArrayD();
    b = ArrayD(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayD(-3));
}


TEST_CASE("[arrayd] - ArrayD size & capacity") {
    ArrayD a(1, 0);
    CHECK(a[0] == 0);
    a.push_back(1);
    CHECK(a[1] == 1);
    a.insert(2, 2);
    CHECK(a[2] == 2);
    a.insert(1, 3);
    CHECK(a[1] == 3);
    CHECK(a[2] == 1);
    a.pop_back();
    CHECK(a[2] == 1);
    a.remove(0);
    CHECK(a[1] == 1);
}


