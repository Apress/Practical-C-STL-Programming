//-----------------------------------------------------------------------------
// Ch02_03_ex.cpp
//-----------------------------------------------------------------------------

#include <format>
#include <fstream>
#include <iostream>
#include <numbers>
#include "Ch02_03.h"
#include "Line.h"
#include "MF.h"

void Ch02_03_ex1()
{
    constexpr int a {100};
    constexpr int b {-200};
    constexpr long long c {300};
    constexpr long long d {-400};

    // bool format
    std::cout << std::format("a == 100: {:d}\n", a == 100);
    std::cout << std::format("b == 400: {:d}\n", b == 400);
    std::cout << std::format("a == 100: {}\n", a == 100);
    std::cout << std::format("b == 400: {:s}\n", b == 400);

    // decimal format
    std::cout << std::format("\na: {}\n", a);
    std::cout << std::format("b: {:d}\n", b);

    // decimal format fill char, alignment, and width
    std::cout << std::format("\na: {:_>10d}\n", a);
    std::cout << std::format("a: {:_<10d}\n", a);
    std::cout << std::format("a: {:_^10d}\n", a);

    // hex format
    std::cout << std::format("\na: {:x}\n", a);
    std::cout << std::format("b: {:x}\n", b);       // includes leading minus sign

    std::cout << std::format("a: {:#010x}\n", static_cast<unsigned int>(a));
    std::cout << std::format("b: {:#010x}\n", static_cast<unsigned int>(b));
    std::cout << std::format("c: {:#018X}\n", static_cast<unsigned long long>(c));
    std::cout << std::format("d: {:#018X}\n", static_cast<unsigned long long>(d));

    // binary format
    std::cout << std::format("\na: {:#034b}\n", static_cast<unsigned int>(a));
    std::cout << std::format("b: {:#034b}\n", static_cast<unsigned int>(b));
    std::cout << std::format("c: {:#066b}\n", static_cast<unsigned int>(c));
    std::cout << std::format("b: {:#066b}\n", static_cast<unsigned long long>(d));

    // decimal format using arg ids
    std::cout << std::format("\na: {0:d} c: {2:d} b: {1:d} c: {2:d} a: {0:d}\n",
        a, b, c);
    std::cout << std::format("a: {0:_>10d} a: {0:_<10d} a: {0:_^10d}\n", a);
}

void Ch02_03_ex2(std::ostream& os)
{
    using namespace std::numbers;

    // floating-point format
    os << std::format("\ne: {}, pi: {}\n", e, pi);
    os << std::format("e: {:f}, pi: {:f}\n", e, pi);    // precision = 6

    // floating-point format using width & precision
    // (+ shows sign char for positive values)
    os << std::format("\ne: {:10.6f}, pi: {:10.6f}\n", e, pi);
    os << std::format("e: {:14.10f}, pi: {:14.10f}\n", e, pi);
    os << std::format("e: {:+10.6f}, pi: {:+10.6f}\n", e, pi);

    // floating-point format using fill char and alignment
    os << std::format("\ne: {:_<12.6f}, pi: {:_<12.6f}\n", e, pi);
    os << std::format("e: {:_>12.6f}, pi: {:_>12.6f}\n", e, pi);
    os << std::format("e: {:_^12.6f}, pi: {:_^12.6f}\n", e, pi);

    // floating-point format using nested replacement
    os << std::format("\ne:  {:{}.{}f}\n", e, 6, 3);
    os << std::format("pi: {:{}.{}f}\n", pi, 16, 8);

    // floating-point format using scientific notation
    double a = e * 10000.0;
    double b = pi / 100000.0;
    os << std::format("\na: {:8.4e}, b: {:8.4e}\n", a, b);
    os << std::format("a: {:16.8e}, b: {:16.8e}\n", a, b);
}

void Ch02_03_ex3(std::ostream& os)
{
    std::string s1 {"0123456789"};
    std::string s2 {"abcdefghijklmnopqrstuvwxyz"};
    std::string sr {"red"};
    std::string sg {"green"};
    std::string sb {"blue"};

    // string format (default)
    os << std::format("\ns1: {}\n", s1);
    os << std::format("s2: {}\n", s2);

    // string format using fill char and alignment
    os << std::format("\ns1: {:~<40s}\n", s1);
    os << std::format("s1: {:~>40s}\n", s1);
    os << std::format("s1: {:~^40s}\n", s1);

    // string format using arg ids
    os << std::format("\n{0:s} {0:s} {1:s} {1:s} {2:s} {2:s}\n",
        sr, sg, sb);
    os << std::format("{0:_>10s} {0:_<10s} {0:_^10s}\n", sg);
}

void Ch02_03_ex4(std::ostream& os)
{
    int x {10};
    float y{22.5f};
    std::string fmt1 {"{:d}, {:f}"};
    std::string fmt2 {"{:f}, {:d}"};

//    os << std::format("x: {:f}\n", x);            // bad - compiler error
//    os << std::format("y: {:d}\n", y);            // bad - compiler error

    try
    {
        auto args {std::make_format_args(x, y)};

        std::string s1 {std::vformat(fmt1, args)};  // ok
        os << s1 << '\n';

        std::string s2 {std::vformat(fmt2, args)};  // throws std::format_error
        os << s1 << '\n';
    }

    catch (const std::format_error& fe)
    {
        os << "\ncaught std::format_error exception" << '\n';
        os << "fe.what() text: " << fe.what() << '\n';
    }
}

void Ch02_03_ex5(std::ostream& os)
{
    Line<short> line1 {0, 0, 3, 4};
    Line<int> line2 {1, 12, 12, -1};
    Line<float> line3 {10.0f, 15.0f, 10.0f, 22.0f};
    Line<double> line4 {-8.0, 8.0, 8.0, -8.0};

    // Line format
    os << std::format("line1: {}\n", line1);
    os << std::format("line2: {}\n", line2);
    os << std::format("line3: {}\n", line3);
    os << std::format("line4: {}\n", line4);
}

void Ch02_03_ex()
{
    std::println("\n----- format_ex1 -----");
    format_ex1();

    std::println("\n----- Ch02_03_ex1() -----");
    Ch02_03_ex1();

    std::println("\n----- Ch02_03_ex2() -----");
    Ch02_03_ex2(std::cout);

    std::println("\n----- Ch02_03_ex3() -----");
    Ch02_03_ex3(std::cout);

    std::println("\n----- Ch02_03_ex4() -----");
    Ch02_03_ex4(std::cout);

    std::println("\n----- Ch02_03_ex5() -----");
    Ch02_03_ex5(std::cout);
}
