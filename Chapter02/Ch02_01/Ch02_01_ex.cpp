//-----------------------------------------------------------------------------
// Ch02_01_ex.cpp
//-----------------------------------------------------------------------------

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <format>
#include <numbers>
#include <string>
#include "Ch02_01.h"

void Ch02_01_ex1(int a, unsigned long long b, double c, const std::string& d)
{
    std::printf("Values using std::printf()\n");
    std::printf("a: %d\n", a);
    std::printf("b: 0x%016llX\n", b);
    std::printf("c: %-10.8lf\n", c);
    std::printf("d: %40s\n", d.c_str());
}

void Ch02_01_ex2(int a, unsigned long long b, double c, const std::string& d)
{
    std::cout << "Values using ostream operator<<\n";
    std::cout << "a: " << a << '\n';
    std::cout << std::setfill('0')
              << "b: 0x" << std::hex << std::setw(16) << b << '\n';
    std::cout << std::setfill(' ')
              << "c: " << std::fixed << std::setprecision(8)
              << std::left << std::setw(10) << c << '\n';
    std::cout << "d: " << std::right << std::setw(40) << d << '\n';
}

void Ch02_01_ex3(int a, unsigned long long b, double c, const std::string& d)
{
    std::cout << "Values using std::format()\n";
    std::cout << std::format("a: {}\n", a);
    std::cout << std::format("b: 0x{:016X}\n", b);
    std::cout << std::format("c: {:<10.8f}\n", c);
    std::cout << std::format("d: {:>40s}\n", d);
}

void Ch02_01_ex4(int a, unsigned long long b, double c, const std::string& d)
{
    std::println("Values using std::println()");
    std::println("a: {}", a);
    std::println("b: 0x{:016X}", b);
    std::println("c: {:<10.8f}", c);
    std::println("d: {:>40s}", d);
}

void Ch02_01_ex()
{
    constexpr int a {100};
    constexpr unsigned long long b {0x4444'3333'2222'1111};
    constexpr double c {std::numbers::pi};
    std::string d {"Four score and seven years ago, ..."};

    std::println("\n----- Ch02_01_ex1() -----");
    Ch02_01_ex1(a, b, c, d);

    std::println("\n----- Ch02_01_ex2() -----");
    Ch02_01_ex2(a, b, c, d);

    std::println("\n----- Ch02_01_ex3() -----");
    Ch02_01_ex3(a, b, c, d);

    std::println("\n----- Ch02_01_ex4() -----");
    Ch02_01_ex4(a, b, c, d);
}
