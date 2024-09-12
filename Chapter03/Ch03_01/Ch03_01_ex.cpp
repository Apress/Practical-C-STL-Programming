//-----------------------------------------------------------------------------
// Ch03_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <format>
#include <numbers>
#include <numeric>
#include <string>
#include "Ch03_01.h"
#include "MT.h"
#include "RN.h"

void Ch03_01_ex1()
{
    std::array<int, 9> x_vals {100, 200, 300, 400, 500, 600, 700, 800, 900};

    // print elements of x_vals using operator[]
    std::println("\narray x_vals: ");
    for (size_t i = 0; i < x_vals.size(); ++i)
        std::print("{:6d} ", x_vals[i]);
    std::println("");
    std::println("x_vals.size(): {:d}", x_vals.size());

    // using at()
//  x_vals.at(42) *= 10;      // invalid index, throws exception

    // print elements of x_vals using forward iterator
    std::println("\narray x_vals: ");
    for (auto iter = x_vals.begin(); iter != x_vals.end(); ++iter)
        std::print("{:6d} ", *iter);
    std::println("");

    // print elements of x_vals using reverse iterator
    std::println("\nx_vals (reversed): ");
    for (auto iter = x_vals.rbegin(); iter != x_vals.rend(); ++iter)
        std::print("{:6d} ", *iter);
    std::println("");
}

void Ch03_01_ex2()
{
    // create array x_vals and print elements
    std::array<long, 10> x_vals {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::println("\nx_vals (original values): ");
    for (auto iter = x_vals.begin(); iter != x_vals.end(); ++iter)
        std::print("{:6d} ", *iter);
    std::println("");

    // add 5 to each element of x_vals[i] using forward iterators
    for (auto iter = x_vals.begin(); iter != x_vals.end(); ++iter)
        *iter += 5;

    // print modified elements
    std::println("\nx_vals (after adds): ");
    for (auto iter = x_vals.begin(); iter != x_vals.end(); ++iter)
        std::print("{:6d} ", *iter);
    std::println("");
}

void Ch03_01_ex3()
{
    using namespace std::numbers;

    std::array<double, 8> radii {1.0, 1.4, 2.0, 2.8, 4.0, 5.6, 8.0, 11.0};
    std::array<double, radii.size()> areas {};

    // using iterators to perform arithmetic calculation
    auto iter_a = areas.begin();
    for (auto iter_r = radii.begin(); iter_r != radii.end(); ++iter_r, ++iter_a)
        *iter_a = pi * *iter_r * *iter_r;

    // print results
    std::println("radius            area\n{:s}", std::string(25, '='));
    iter_a = areas.begin();
    for (auto iter_r = radii.begin(); iter_r != radii.end(); ++iter_r, ++iter_a)
        std::println("{:6.1f} {:15.6f}", *iter_r, *iter_a);
}

void Ch03_01_ex4()
{
    constexpr size_t n {20};
    constexpr int rng_min {1};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {3};

    // fill arr1 with random values
    std::array<int, n> arr1;
    RN::fill_ctr(arr1, rng_min, rng_max, rng_seed);

    // print elements of arr1
    const char* fmt = "{:7d}";
    constexpr size_t epl_max {10};
    MT::print_ctr("\nelements of arr1:\n", arr1, fmt, epl_max);

    // sum elements of arr1 using iterators
    int sum1 {};
    for (auto iter = arr1.begin(); iter != arr1.end(); ++iter)
        sum1 += *iter;
    std::println("sum1: {:d}", sum1);

    // sum elements of arr1 using std::accmulate()
    int sum2 = std::accumulate(arr1.begin(), arr1.end(), 0);
    std::println("sum2: {:d}", sum2);
}

void Ch03_01_ex5()
{
    const char* fmt = "{:15s}";
    constexpr size_t epl_max {5};

    // create test arrays of std::string
    std::array<std::string, 15> colors1 {"Red", "Green", "Blue", "Cyan", "Magenta",
        "Yellow", "Black", "White", "Gray", "Orange", "Brown", "Pink", "Purple",
        "Amber", "Teal"};

    auto colors2 {colors1};

    // using std::sort
    std::sort(colors1.begin(), colors1.end());
    MT::print_ctr("\ncolors1 - after std::sort():\n", colors1, fmt, epl_max);

    // using std::ranges::sort (C++20)
    std::ranges::sort(colors2);
    MT::print_ctr("\ncolors2 - after std::ranges::sort():\n",
        colors2, fmt, epl_max);

    // using operator==
    std::println("\ncolors1 == colors2: {:s}", colors1 == colors2);
}

void Ch03_01_ex()
{
    std::println("\n----- Ch03_01_ex1() -----");
    Ch03_01_ex1();

    std::println("\n----- Ch03_01_ex2() -----");
    Ch03_01_ex2();

    std::println("\n----- Ch03_01_ex3() -----");
    Ch03_01_ex3();

    std::println("\n----- Ch03_01_ex4() -----");
    Ch03_01_ex4();

    std::println("\n----- Ch03_01_ex5() -----");
    Ch03_01_ex5();
}
