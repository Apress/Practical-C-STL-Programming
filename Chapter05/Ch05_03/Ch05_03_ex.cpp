//-----------------------------------------------------------------------------
// Ch05_03_ex.cpp
//-----------------------------------------------------------------------------

#include <numbers>
#include <utility>
#include <variant>
#include "Ch05_03.h"
#include "Rect.h"

void Ch05_03_ex1()
{
    std::variant<double, int> var1 {};

    // using var1 with double
    var1 = std::numbers::pi;
    std::println("\nstd::get<0>(var1):      {}", std::get<0>(var1));
    std::println("std::get<double>(var1): {}", std::get<double>(var1));

    // using var1 with int
    var1 = 100;
    std::println("\nstd::get<1>(var1):      {}", std::get<1>(var1));
    std::println("std::get<int>(var1):    {}", std::get<int>(var1));

    // bad variant access generates exception
    try
    {
        auto bad_access = std::get<double>(var1);
        std::println("\nbad_access: {}", bad_access);
    }

    catch (const std::bad_variant_access& ex)
    {
        std::println("\ncaught exception:       {}", ex.what());
    }

    // using std::get_if (example 1)
    std::print("\nget_if<double>(var1):   ");
    if (const double* p_double = std::get_if<double>(&var1))
        std::println("*p_double = {}", *p_double);
    else
        std::println("failed as expected\n");

    // using std::get_if (example 2)
    std::print("get_if<int>(var1):      ");
    if (const int* p_int = std::get_if<1>(&var1))
        std::println("*p_int = {}", *p_int);
    else
        std::println("unexpected error");
}

void Ch05_03_ex2()
{
    std::variant<Rect, std::string> var1 {};

    // using emplace and holds_alternative (example 1)
    var1.emplace<0>(Rect(10, 20, 30, 40));
    if (std::holds_alternative<Rect>(var1))
        std::println("\nvar1 (Rect):   {}", std::get<Rect>(var1));
    std::println("var1.index(): {:d}", var1.index());

    // using emplace and holds_alternative (example 2)
    var1.emplace<1>("one, two, three, four");
    if (std::holds_alternative<std::string>(var1))
        std::println("\nvar1 (std::string): {}", std::get<std::string>(var1));
    std::println("var1.index(): {:d}", var1.index());
}

void Ch05_03_ex3()
{
    using namespace std::string_literals;
    using var_t = std::variant<std::string, int>;

    var_t var1 {"red"s};
    var_t var2 {"red"s};
    var_t var3 {"green"s};
    var_t var4 {10};

    // relational operators (same index, same value)
    std::println("\nvar1 == var2: {:s}", var1 == var2);
    std::println("var1 != var2: {:s}", var1 != var2);
    std::println("var1 <  var2: {:s}", var1 <  var2);
    std::println("var1 <= var2: {:s}", var1 <= var2);
    std::println("var1 >  var2: {:s}", var1 >  var2);
    std::println("var1 >= var2: {:s}", var1 >= var2);

    // relational operators (same index, different value)
    std::println("\nvar1 == var3: {:s}", var1 == var3);
    std::println("var1 != var3: {:s}", var1 != var3);
    std::println("var1 <  var3: {:s}", var1 <  var3);
    std::println("var1 <= var3: {:s}", var1 <= var3);
    std::println("var1 >  var3: {:s}", var1 >  var3);
    std::println("var1 >= var3: {:s}", var1 >= var3);

    // relational operators (different index, different value)
    std::println("\nvar1 == var4: {:s}", var1 == var4);
    std::println("var1 != var4: {:s}", var1 != var4);
    std::println("var1 <  var4: {:s}", var1 <  var4);
    std::println("var1 <= var4: {:s}", var1 <= var4);
    std::println("var1 >  var4: {:s}", var1 >  var4);
    std::println("var1 >= var4: {:s}", var1 >= var4);
}

void Ch05_03_ex()
{
    std::print("\n----- Ch05_03_ex1() -----\n");
    Ch05_03_ex1();

    std::print("\n----- Ch05_03_ex2() -----\n");
    Ch05_03_ex2();

    std::print("\n----- Ch05_03_ex3() -----\n");
    Ch05_03_ex3();
}
