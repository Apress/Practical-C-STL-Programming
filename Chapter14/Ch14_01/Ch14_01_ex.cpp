//-----------------------------------------------------------------------------
// Ch14_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>
#include "Ch14_01.h"
#include "MT.h"
#include "MTH.h"
#include "RN.h"

auto get_test_vector()
{
    // return test vector of random integers
    return RN::get_vector<int>(60, -500, 500, 13);
}

void Ch14_01_ex1()
{
    const char* fmt = "{:6d}";
    constexpr size_t epl_max {12};

    // create test vector of random numbers
    std::vector<int> vec1 = get_test_vector();
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    auto pred = [](int x) { return x > 0 && x % 10 == 0; };

    // using std::views::filter (can also use std::ranges::views::filter)
    auto view1 = std::views::filter(vec1, pred);

    bool is_empty1 = view1.empty();
    std::println("\nview1 is empty: {:s}", is_empty1);

    // copy-construct view2 using view1
    auto view2 {view1};

    bool is_empty2 = view2.empty();
    std::println("\nview2 is empty: {:s}", is_empty2);
}

void Ch14_01_ex2()
{
    const char* fmt = "{:6d}";
    constexpr size_t epl_max {12};

    // create test vector of random numbers
    std::vector<int> vec1 = get_test_vector();
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    auto pred = [](int x) { return x > 0 && x % 10 == 0; };

    // using std::views::filter
    auto view1 = std::views::filter(vec1, pred);

    // empty view?
    if (view1)
    {
        // print elements of view1
        std::println("\nprinting elements of view1 using iterators");
        for (auto iter = view1.begin(); iter != view1.end(); ++iter)
            std::print("{:d} ", *iter);
        std::println("");

        std::println("\nprinting elements of view1 using range for loop");
        for (auto val : view1)
            std::print("{:d} ", val);
        std::println("");
    }
    else
        std::println("view1 is empty");
}

void Ch14_01_ex3()
{
    const char* fmt = "{:7d}";
    constexpr size_t epl_max {10};

    // initialize test vector
    std::vector<int> vec1(50);
#ifdef __cpp_lib_ranges_iota        // C++23
    std::ranges::iota(vec1, 1);
#else
    std::iota(vec1.begin(), vec1.end(), 1);
#endif
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);
    
    // using std::views::filter
    auto view1 = std::views::filter(vec1, MTH::is_prime<int>);

    // using std::views::transform
    auto view2 = std::views::transform(view1, [](int x) { return -x; });

    // print elements specfied by view1 and view2
    MT::print_ctr("\nview1 (std::views::filter):\n", view1, fmt, epl_max);
    MT::print_ctr("\nview2 (std::views::transform):\n", view2, fmt, epl_max);

    // print elements of vec1 (same as initial values)
    MT::print_ctr("\nvec1 (unaltered by std::views::filter, transform):\n",
        vec1, fmt, epl_max);

    // using std::ranges::to<std::vector> (C++23)
#ifdef __cpp_lib_ranges_to_container
    std::vector<int> vec2 = view2 | std::ranges::to<std::vector>();
    MT::print_ctr("\nvec2 (result of view2 | std::ranges::to<std::vector>):\n",
        vec2, fmt, epl_max);
#else
    std::println("std::ranges::to<std::vector>() requires C++23)");
#endif
}

void Ch14_01_ex()
{
    std::println("\n----- Ch14_01_ex1() -----");
    Ch14_01_ex1();

    std::println("\n----- Ch14_01_ex2() -----");
    Ch14_01_ex2();

    std::println("\n----- Ch14_01_ex3() -----");
    Ch14_01_ex3();
}
