//-----------------------------------------------------------------------------
// Ch06_01_misc.cpp
//-----------------------------------------------------------------------------

#include "Ch06_01.h"

void test_ptr1()
{
    // pointer to a fundamental type
    int i {10};
    int* ip = &i;

    *ip += 20;
    i -= 5;
    std::println("i: {:d}", i);
}

struct X
{   
    int ValA {20};
    double ValB {30.0};
};

void test_ptr2()
{
    // pointer to a struct
    X* xp = new X {};

    xp->ValA *= 10;
    xp->ValB /= 5.0;
    std::println("xp->ValA: {:d}  xp->ValB: {:f}", xp->ValA, xp->ValB);
    delete xp;
}

void test_ptr3()
{
    // pointer to C-style array
    constexpr int n {5};
    int* p = new int[n];

    auto f = [](int* p, int n)
    {
        for (int i = 0; i < n; ++i)
        {
            p[i] = 3 * i * i + 2 * i + 4;
            std::println("p[{:d}]: {:d}", i, p[i]);
        }
    };

    f(p, n);
    delete[] p;
}

void test_ptr()
{
    std::println("");
    test_ptr1();

    std::println("");
    test_ptr2();

    std::println("");
    test_ptr3();
}
