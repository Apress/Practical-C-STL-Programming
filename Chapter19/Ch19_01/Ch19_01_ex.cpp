//-----------------------------------------------------------------------------
// Ch19_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <numeric>
#include <valarray>
#include "Ch19_01.h"
#include "MT.h"
#include "RN.h"

void Ch19_01_ex1()
{
    const char* fmt1 = "{:7d}";
    const char* fmt2 = "{:7.1f}";
    constexpr size_t epl_max {10};

    constexpr size_t n {25};
    constexpr int rng_min {1};
    constexpr int rng_max {500};
    constexpr unsigned int rng_seed {19011};

    // using std::valarray<int>
    std::valarray va1 = RN::get_valarray<int>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nva1:\n", va1, fmt1, epl_max);

    std::println("\nva1 - sum: {:d}, min: {:d}, max: {:d}",
        va1.sum(), va1.min(), va1.max());

    // using std::valarray<> operator+=
    va1 += 5;
    MT::print_ctr("\nva1 (after operator+=):\n", va1, fmt1, epl_max);

    // using std::valarray<double>
    std::valarray va2 = RN::get_valarray<double>(n, rng_min, rng_max, rng_seed + 1);
    MT::print_ctr("\nva2:\n", va2, fmt2, epl_max);

    std::println("\nva2 - sum: {:.1f}, min: {:.1f}, max: {:.1f}",
        va2.sum(), va2.min(), va2.max());

    // using std::valarray<> operator-=
    va2 -= 0.5;
    MT::print_ctr("\nva2 (after operator-=):\n", va2, fmt2, epl_max);

    // using operator[]
    for (size_t i = 0; i < n; ++i)
        va2[i] = static_cast<double>(va1[i] % 3);
    MT::print_ctr("\nva2 (after operator[] calculations):\n",
        va2, fmt2, epl_max);
}

void Ch19_01_ex2()
{
    const char* fmt = "{:7d}";
    constexpr size_t epl_max {10};

    // create test valarray<> objects
    std::valarray<int> va1 {10, 20, 30, 40, 50};
    std::valarray<int> va2 {100, 200, 300, 400, 500, 600, 700, 800};
    std::valarray<long long> va3 {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    MT::print_ctr("\nva1:\n", va1, fmt, epl_max);
    MT::print_ctr("\nva2:\n", va2, fmt, epl_max);
    MT::print_ctr("\nva3:\n", va3, fmt, epl_max);

    // using valarray<>::operator=
    va2 = va1;
    MT::print_ctr("\nva2 (after operator=):\n", va1, fmt, epl_max);

//  va3 = va1;    // illegal - different element types

    // using valarray<>::apply
    auto apply_op = [](int x) { return x * x - 1; };

    std::valarray<int> va4 = va1.apply(apply_op);
    MT::print_ctr("\nva4:\n", va4, fmt, epl_max);
}

void Ch19_01_ex3()
{
    const char* fmt = "{:12.4f}";
    constexpr size_t epl_max {5};

    // create test valarray<>
    // must use std::begin() and std::end() for std::valarray iterators
    constexpr size_t n {20};

    std::valarray<double> va1(n);
    std::iota(std::begin(va1), std::end(va1), 1.0);
    MT::print_ctr("\nva1:\n", va1, fmt, epl_max);

    // using std::valarray<> math overloads
    std::valarray<double> va2 = std::sqrt(va1);
    MT::print_ctr("\nva2 (after sqrt):\n", va2, fmt, epl_max);

    va2 = std::pow(va2, 3.0);
    MT::print_ctr("\nva2 (after pow):\n", va2, fmt, epl_max);
   
    va2 = std::log10(va1);
    MT::print_ctr("\nva2 (after log10):\n", va2, fmt, epl_max);
}

void Ch19_01_ex4()
{
    const char* fmt = "{:7.1f}";
    constexpr size_t epl_max {11};
    constexpr size_t n {10};

    // create test valarray<> objects
    std::valarray<float> va1(n);
    std::iota(std::begin(va1), std::end(va1), 1.0f);

    std::valarray<float> va2(va1);
    va2[0] += 1.0f;
    va2[n / 4] -= 2.0f;
    va2[n / 2] *= 3.0f;
    va2[n - 1] /= 4.0f;

    MT::print_ctr("\nva1:\n", va1, fmt, epl_max);
    MT::print_ctr("\nva2:\n", va2, fmt, epl_max);

    // using operator< (returns std::valarray<bool>)
    std::valarray<bool> va_lt = va1 < va2;
    MT::print_ctr("\nva_lt:\n", va_lt, "{:>7s}", epl_max);

    // using operator== (returns std::valarray<bool>)
    std::valarray<bool> va_eq = va1 == va2;
    MT::print_ctr("\nva_cmp:\n", va_eq, "{:>7s}", epl_max);

    // using operator> (returns std::valarray<bool>)
    std::valarray<bool> va_gt = va1 > va2;
    MT::print_ctr("\nva_gt:\n", va_gt, "{:>7s}", epl_max);
}

void Ch19_01_ex()
{
    std::println("\n----- Ch19_01_ex1() -----");
    Ch19_01_ex1();

    std::println("\n----- Ch19_01_ex2() -----");
    Ch19_01_ex2();

    std::println("\n----- Ch19_01_ex3() -----");
    Ch19_01_ex3();

    std::println("\n----- Ch19_01_ex4() -----");
    Ch19_01_ex4();
}
