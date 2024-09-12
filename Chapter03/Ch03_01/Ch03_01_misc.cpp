//-----------------------------------------------------------------------------
// Ch03_01_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include "Ch03_01.h"
#include "MT.h"

void test_operators()
{
    std::array<int, 4> a {10, 20, 30, 40};
    std::array<int, 4> b {-10, -20, -30, -40};
    std::array<long, 4> c {100, 200, 300, 400};
    std::array<long, 5> d {100, 200, 300, 400, 500};

    bool b1 = a == b;       // ok
    bool b2 = a >= b;       // ok
    a = b;                  // ok

//  bool b3 = a == c;       // error - different types
//  bool b4 = c == d;       // error - different sizes
//  a = c;                  // error - different types and sizes

    const char* fmt = "{:d} ";
    std::println("\n----- TEST CODE -----\n");
    MT::print_ctr("a: ", a, fmt);
    MT::print_ctr("b: ", b, fmt);
    MT::print_ctr("c: ", c, fmt);
    MT::print_ctr("d: ", d, fmt);
    std::println("b1: {:s}  b2: {:s}", b1, b2); 
}