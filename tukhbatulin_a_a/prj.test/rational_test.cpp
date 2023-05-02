
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.hpp>
#include <sstream>

TEST_CASE("Comparing Rationals with themselfs and integers") {

    SUBCASE("comparing rationals")
    {
        Rational R = Rational(3, 2);
        Rational A;
        Rational B = Rational(20, 3);
        Rational C = Rational(3, 2);

        CHECK((R == B) == false);
        CHECK((R == C) == true);

        CHECK((R != B) == true);
        CHECK((R != C) == false);

        CHECK((R < B) == true);
        CHECK((R < C) == false);
        CHECK((R < A) == false);

        CHECK((R > B) == false);
        CHECK((R > C) == false);
        CHECK((R > A) == true);

        CHECK((R >= B) == false);
        CHECK((R >= C) == true);
        CHECK((R >= A) == true);

        CHECK((R <= B) == true);
        CHECK((R <= C) == true);
        CHECK((R <= A) == false);
    }
    SUBCASE("comparing rationals-integers")
    {
        Rational R = Rational(3, 3);
        int32_t A = 0;
        int32_t B = 20;
        int32_t C = 1;

        CHECK((R == B) == false);
        CHECK((R == C) == true);

        CHECK((R != B) == true);
        CHECK((R != C) == false);

        CHECK((R < B) == true);
        CHECK((R < C) == false);
        CHECK((R < A) == false);

        CHECK((R > B) == false);
        CHECK((R > C) == false);
        CHECK((R > A) == true);

        CHECK((R >= B) == false);
        CHECK((R >= C) == true);
        CHECK((R >= A) == true);

        CHECK((R <= B) == true);
        CHECK((R <= C) == true);
        CHECK((R <= A) == false);
    }
}

TEST_CASE("Operator ...=") {
    SUBCASE("+=")
    {
        Rational R = Rational(3, 2);
        R += 1;
        CHECK(R == Rational(5, 2));
        R += Rational(4, 9);
        CHECK(R == (Rational(53, 18)));
    }
    SUBCASE("-=")
    {
        Rational R = Rational(3, 2);
        R -= 1;
        CHECK(R == Rational(1, 2));
        R -= Rational(4, 9);
        CHECK(R == Rational(1, 18));
        R -= 1;
        CHECK(R == Rational(-17, 18));
    }
    SUBCASE("*=")
    {
        Rational R = Rational(3, 2);
        R *= 3;
        CHECK(R == Rational(9, 2));
        R *= Rational(5, 3);
        CHECK(R == Rational(15, 2));
        R *= 0;
        CHECK(R == Rational(0, 1));

    }
    SUBCASE("/=")
    {
        Rational R = Rational(3, 2);
        R /= 3;
        CHECK(R == Rational(1, 2));
        R /= Rational(5, 3);
        CHECK(R == Rational(3, 10));
        CHECK_THROWS(R /= 0);

    }

    SUBCASE("pref ++")
    {
        Rational R = Rational(1, 2);
        CHECK(++R == Rational(3, 2));
        CHECK(R == Rational(3, 2));
        R = Rational(1, 2);
        CHECK(R++ == Rational(1, 2));
        CHECK(R == Rational(3, 2));
        CHECK_THROWS(R /= 0);
    }
}

TEST_CASE("Operator ...")
{
    Rational A = Rational(3, 2);
    Rational B = Rational(4, 5);
    Rational C = Rational(0, 1);
    Rational D = Rational(1, 1);
    int32_t E = 1;
    Rational A1 = A;
    SUBCASE("+")
    {   
        CHECK(E + D == Rational(2, 1));
        CHECK(A == A1);
        A1 += B;
        CHECK((A + B) == A1);
        CHECK((A + C) == A);
        A1 = A;
        A1 += D;
        CHECK((A + D) == A1);
    }
    SUBCASE("-")
    {
        A1 = A;
        A1 -= B;
        CHECK((A - B) == A1);
        CHECK((A - C) == A);
        A1 = A;
        A1 -= D;
        CHECK((A - D) == A1);
    }
    SUBCASE("*")
    {
        A1 = A;
        A1 *= B;
        CHECK((A * B) == A1);
        CHECK((A * C) == 0);
        CHECK((A * D) == A);
    }
    SUBCASE("/")
    {
        A1 = A;
        A1 /= B;
        CHECK((A / B) == A1);
        CHECK_THROWS(A / C);
        CHECK((A / D) == A);
    }
}

TEST_CASE("Streams")
{
    Rational a(0);
    std::stringstream strm;
    strm << "1/1\n";
    strm >> a;
    CHECK(a == 1);
    strm << "-1/1\n";
    strm >> a;
    CHECK(a == -1);
    strm << "0/1\n";
    strm >> a;
    CHECK(a == 0);
    strm << "1/2 2/3 3/4\n";
    strm >> a;
    CHECK(a == Rational(1, 2));
    strm >> a;
    CHECK(a == Rational(2, 3));
    strm >> a;
    CHECK(a == Rational(3, 4));


    a = 0;
    strm << "1/k";
    strm >> a;
    CHECK(strm.good() == 0);

    a = 0;
    strm << "k/1";
    strm >> a;
    CHECK(a == 0);
}

TEST_CASE("Throws")
{
    CHECK_THROWS(Rational(0, 0));
}
