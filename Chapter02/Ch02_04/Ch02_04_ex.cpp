//-----------------------------------------------------------------------------
// Ch02_04_ex.cpp
//-----------------------------------------------------------------------------

#include <iostream>
#include <numbers>
#include "Ch02_04.h"
#include "Line.h"
#include "MF.h"

void Ch02_04_ex1()
{
    constexpr int a {1000};
    constexpr int b {-2000};
    constexpr long long c {3000};

    // bool print
    std::println("b == 400: {:d}", b == 400);
    std::println("b == 400: {:s}", b == 400);

    // decimal print
    std::println("a: {}", a);
    std::println("b: {:d}", b);

    // decimal print using fill char, alignment and width specifier
    std::println("a: {:_>10d}", a);
    std::println("a: {:_<10d}", a);
    std::println("a: {:_^10d}", a);

    // hex print
    std::println("a: {:x}", a);
    std::println("c: {:X}", c);

    // binary print
    std::println("a: {:#034b}", a);
    std::println("c: {:#066b}", c);

    // decimal print using arg ids
    std::println("a: {0:d} c: {2:d} b: {1:d} c: {2:d} a: {0:d}", a, b, c);
}

void Ch02_04_ex2(std::ostream& os)
{
    using namespace std::numbers;

    // floating-point print
    std::println(os, "e: {:f}, pi: {:f}", e, pi);

    // floating-point print using width & precision
    std::println(os, "e: {:10.6f}, pi: {:10.6f}", e, pi);
    std::println(os, "e: {:14.10f}, pi: {:14.10f}", e, pi);

    // floating-point print using scientific notation
    double a = e * 10000.0;
    double b = pi / 100000.0;
    std::println(os, "a: {:8.4e}, b: {:8.4e}", a, b);
    std::println(os, "a: {:16.8e}, b: {:16.8e}", a, b);
}

void Ch02_04_ex3(std::ostream& os)
{
    std::string s1 {"0123456789"};
    std::string sr {"red"};
    std::string sg {"green"};
    std::string sb {"blue"};

    // string print using alignment and fill char
    std::println(os, "s1: {:~<40s}", s1);
    std::println(os, "s1: {:~>40s}", s1);
    std::println(os, "s1: {:~^40s}", s1);

    // string print using arg ids
    std::println(os, "{2:s} {1:s} {0:s} {0:s} {1:s} {2:s}", sr, sg, sb);
}

void Ch02_04_ex()
{
    std::println("\n----- Ch02_04_ex1() -----");
    Ch02_04_ex1();

    std::println("\n----- Ch02_04_ex2() -----");
    Ch02_04_ex2(std::cout);

    std::println("\n----- Ch02_04_ex3() -----");
    Ch02_04_ex3(std::cout);
}
