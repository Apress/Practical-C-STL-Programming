//-----------------------------------------------------------------------------
// Ch02_02_ex.cpp
//-----------------------------------------------------------------------------

#include <bitset>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <numbers>
#include <ostream>
#include <string>
#include "Ch02_02.h"
#include "Line.h"
#include "MF.h"

void Ch02_02_ex1()
{
    constexpr int a {100};
    constexpr long long b {-300};

    // bool output
    std::cout << "a == 100: ";
    std::cout << (a == 100);
    std::cout << '\n';
    std::cout << "a == 100: " << std::boolalpha << (a == 100) << '\n';

    // decimal output
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    // hex output
    std::cout << std::hex << std::showbase;
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    // hex output using uppercase and fill character
    constexpr int w = (sizeof(void*) <= 4) ? 8 : 16;
    std::uintptr_t a_addr = reinterpret_cast<uintptr_t>(&a);
    std::cout << std::noshowbase << std::uppercase << std::setfill('0');
    std::cout << "\na_addr: 0X" << std::setw(w) << a_addr << '\n';

    // hex output using lower case and same fill char
    std::cout << std::nouppercase;
    std::cout << "a_addr: 0x" << std::setw(w) << a_addr << '\n';

    // binary output
    std::bitset<sizeof(uintptr_t) * 8> a_addr_bin(a_addr);
    std::cout << "a_addr: 0b" << a_addr_bin << '\n';

    // reset std::cout to decimal
    std::cout << std::dec;
}

void Ch02_02_ex2(std::ostream& os)
{
    using namespace std::numbers;

    // save current flags and precision
    auto old_flags = os.flags();
    auto old_precision = os.precision(4);
    os << "old_precision: " << old_precision << '\n';

    // floating-point output using fixed
    os << std::fixed;
    os << "\ne:  " << e << '\n';
    os << "pi: " << pi << '\n';

    // floating-point output using setprecision()
    os << std::setprecision(10);
    os << "e:  " << e << '\n';
    os << "pi: " << pi << '\n';

    // floating-point output using scientific notation
    double a = e / 10000.0;
    double b = pi * 10000.0;
    os << std::scientific << std::setprecision(6);
    os << "\na: " << a << '\n';
    os << "b: " << b << '\n';

    // floating-point output using showpos
    a = -a;
    os << std::fixed << std::showpos;
    os << "\na: " << a << '\n';
    os << "b: " << b << '\n';

    // restore original flags and precision
    os.flags(old_flags);
    os.precision(old_precision);
}

void Ch02_02_ex3(std::ostream& os)
{
    constexpr int w {40};
    std::string s1 {"0123456789"};
    std::string s2 {"abcdefghijklmnopqrstuvwxyz"};

    // string output using left, right, and setw
    os << std::setfill('_');
    os << "s1: " << std::left << std::setw(w) << s1 << '\n';
    os << "s2: " << std::left << std::setw(w) << s2 << '\n';
    os << "s1: " << std::right << std::setw(w) << s1 << '\n';
    os << "s2: " << std::right << std::setw(w) << s2 << '\n';

    // string output using quoted
    os << std::setfill(' ');
    os << "\ns1 quoted: " << std::quoted(s1) << '\n';
    os << "s2 quoted: " << std::quoted(s2, '|') << '\n';
}

void Ch02_02_ex4()
{
    // open test file
    std::string fn = MF::mk_test_filename("ch02_02_ex4.txt");
    std::ofstream ofs {fn};

    // open success?
    if (!ofs.good())
    {
        std::println("open failed using file {}", fn);
        return;
    }

    // write to std::ofstream
    Ch02_02_ex2(ofs);
    ofs.close();
    std::println("results saved to file {}", fn);
}

void Ch02_02_ex()
{
    std::println("\n----- Ch02_02_ex1() -----");
    Ch02_02_ex1();

    std::println("\n----- Ch02_02_ex2() -----");
    Ch02_02_ex2(std::cout);

    std::println("\n----- Ch02_02_ex3() -----");
    Ch02_02_ex3(std::cout);

    std::println("\n----- Ch02_02_ex4() -----");
    Ch02_02_ex4();
}
