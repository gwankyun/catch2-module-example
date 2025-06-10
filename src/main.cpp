module;
#include "catch2_macro.h"

module main;
import std;
import catch2;

#ifndef ON
#  define ON CATCH_ON
#endif // !ON

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

void factorials_are_computed()
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(3) == 6);
    REQUIRE(Factorial(10) == 3628800);
}

void vectors_can_be_sized_and_resized()
{
    using Catch::session;
    // This setup will be done 4 times in total, once for each section
    std::vector<int> v(5);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    session(
        "resizing bigger changes size and capacity",
        [&]
        {
            v.resize(10);

            REQUIRE(v.size() == 10);
            REQUIRE(v.capacity() >= 10);
        }
    );
    session(
        "resizing smaller changes size but not capacity",
        [&]
        {
            v.resize(0);

            REQUIRE(v.size() == 0);
            REQUIRE(v.capacity() >= 5);
        }
    );
    session(
        "reserving bigger changes capacity but not size",
        [&]
        {
            v.reserve(10);

            REQUIRE(v.size() == 5);
            REQUIRE(v.capacity() >= 10);
        }
    );
    session(
        "reserving smaller does not change size or capacity",
        [&]
        {
            v.reserve(0);

            REQUIRE(v.size() == 5);
            REQUIRE(v.capacity() >= 5);
        }
    );
}

void test_capture(int _value)
{
    Catch::require ON(_value == 1);
}

int main(int _argc, char* _argv[])
{
    using Catch::test_case;
    test_case("Factorials are computed", "[factorial]", &factorials_are_computed);
    test_case("vectors can be sized and resized", "[vector]", &vectors_can_be_sized_and_resized);

    {
        test_case(
            "base", "[lambda]",
            []
            {
                using namespace std::literals::string_literals;
                REQUIRE(1 + 2 == 3);
                REQUIRE("123"s + "456"s == "123456"s);
            }
        );
    }

    test_case(
        "without capture", "[lambda]",
        []
        {
            Catch::require ON(1 + 2 == 3);
            Catch::check ON(false);
        }
    );

    int value = 1;
    test_case("with capture", "[lambda]", [&value] { test_capture(value); });

    auto result = Catch::Session().run(_argc, _argv);
    return result;
}
