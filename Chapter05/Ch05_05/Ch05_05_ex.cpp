//-----------------------------------------------------------------------------
// Ch05_05_ex.cpp
//-----------------------------------------------------------------------------

#include <any>
#include <numbers>
#include <typeinfo>
#include "Ch05_05.h"
#include "Rect.h"

void Ch05_05_ex1()
{
    using namespace std::string_literals;

    // using std::any - initial value is int
    std::any val1 {100};
    std::println("\nval1 type:  {:s}", val1.type().name());
    std::println("val1 value: {:d}", std::any_cast<int>(val1));

    // change val1 to std::string (literal suffix required)
    val1 = "one, two, three"s;
    std::println("\nval1 type:  {:s}", val1.type().name());
    std::println("val1 value: {:s}", std::any_cast<std::string>(val1));

    // using std::any - initial value is double
    std::any val2 {std::numbers::pi};
    std::println("\nval1 type:  {:s}", val2.type().name());
    std::println("val2 value: {:.4f}", std::any_cast<double>(val2));

    // throws std::bad_any_cast exception
//  auto val3 = std::any_cast<std::string>(val2);
}

void Ch05_05_ex2()
{
    std::any val1 {};

    // using emplace - change to Rect
    val1.emplace<Rect>(0, 0, 3, 4);

    if (val1.has_value())
    {
        if (val1.type() == typeid(Rect))
            std::println("val1: {}", any_cast<Rect>(val1));
    }

    // using emplace - change to std::string
    val1.emplace<std::string>("eins zwei drei");

    if (val1.has_value())
    {
        if (val1.type() == typeid(std::string))
            std::println("val1: {}", any_cast<std::string>(val1));
    }

    // manual reset
    val1.reset();

    if (val1.has_value())
        std::println("val1.reset() failed!");
    else
        std::println("val1.reset() successful");
}

void process_message(const std::any& val)
{
    if (val.type() == typeid(int))
        std::println("val: {:d}", any_cast<int>(val));

    if (val.type() == typeid(long))
        std::println("val: {:d}", any_cast<long>(val));

    else if (val.type() == typeid(double))
        std::println("val: {:f}", any_cast<double>(val));

    else if (val.type() == typeid(std::string))
        std::println("val: {:s}", any_cast<std::string>(val));

    else if (val.type() == typeid(Rect))
        std::println("val: {}", any_cast<Rect>(val));

    else 
        std::println("unexpected type: {:s}", val.type().name());
}

void Ch05_05_ex3()
{
    process_message(std::make_any<int>(100));
    process_message(std::make_any<long>(200L));
    process_message(std::make_any<long long>(300LL));
    process_message(std::make_any<double>(std::numbers::pi));
    process_message(std::make_any<std::string>("lemon lime orange"));
    process_message(std::make_any<Rect>(Rect {0, 0, 30, 40}));
    process_message(std::any {});
}

void Ch05_05_ex()
{
    std::println("\n----- Ch05_05_ex1() -----");
    Ch05_05_ex1();

    std::println("\n----- Ch05_05_ex2() -----");
    Ch05_05_ex2();

    std::println("\n----- Ch05_05_ex3() -----");
    Ch05_05_ex3();
}
