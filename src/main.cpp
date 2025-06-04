module main;
import std;
import catch2;

#ifndef CATCH_STRING
#  define CATCH_STRING(_str) #_str
#endif // !CATCH_STRING

#ifndef CATCH_EXPRESSION
#  define CATCH_EXPRESSION(_expression) _expression, CATCH_STRING(_expression)
#endif // !CATCH_EXPRESSION

#ifndef REQUIRE
#  define REQUIRE(_expression) Catch::require(CATCH_EXPRESSION(_expression))
#endif // !REQUIRE

#ifndef CHECK
#  define CHECK(_expression) Catch::check(CATCH_EXPRESSION(_expression))
#endif // !CHECK

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
        "without macro", "[lambda]",
        []
        {
            Catch::require(1 + 2 == 3, "1 + 2 == 3");
            Catch::check(false, "false");
        }
    );

    auto result = Catch::Session().run(_argc, _argv);
    return result;
}
