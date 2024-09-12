//-----------------------------------------------------------------------------
// Ch10_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include "Ch10_03.h"
#include "MT.h"
#include "Rect.h"

void Ch10_03_ex1()
{
    const char* fmt {"{:d} "};
    constexpr size_t epl_max {15};

    // create array of ints
    std::array<int, 10> arr1 {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    MT::print_ctr("\narr1: ", arr1, fmt, epl_max);

    // using std::copy - destination iterator
    std::vector<int> vec1(arr1.size());
    std::copy(arr1.begin(), arr1.end(), vec1.begin());
    MT::print_ctr("\nvec1: ", vec1, fmt, epl_max);

    // using std:copy - std::back_inserter
    std::vector<int> vec2 {-10, 0};
    std::copy(vec1.begin(), vec1.end(), std::back_inserter(vec2));
    MT::print_ctr("\nvec2: ", vec2, fmt, epl_max);

    // using std::ranges::copy - different data types
    std::vector<double> vec3 {};
    std::ranges::copy(vec2, std::back_inserter(vec3));
    MT::print_ctr("\nvec3: ", vec3, "{:.1f} ", epl_max);

    // using std::ranges::copy
    std::vector<double> vec4(vec3.size());
    std::ranges::copy(vec3, vec4.begin());
    MT::print_ctr("\nvec4: ", vec4, "{:.1f} ", epl_max);
}

namespace
{
    std::initializer_list<Rect> s_Rects
    {
        {0, 0, 640, 480},   {0, 0, 800, 600},
        {0, 0, 1024, 768}, {0, 0, 1280, 1024},
        {0, 0, 1600, 1200}, {0, 0, 1920, 1080},
        {0, 0, 3840, 2160}, {0, 0, 7680, 4320},
    };
}

void Ch10_03_ex2()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {2};

    // initialize vector of Rects
    std::vector<Rect> vec1 {s_Rects};
    MT::print_ctr("\nvec1 (orginal values):\n", vec1, fmt, epl_max);

    //copy _if predicate
    auto copy_pred = [](const Rect& rect)
        { return rect.area() >= 500'000 && rect.area() <= 4'000'000; };

    // using std::copy_if
    std::vector<Rect> vec2 {};
    std::copy_if(vec1.begin(), vec1.end(), std::back_inserter(vec2), copy_pred);
    MT::print_ctr("\nvec2 (after copy_if):\n", vec2, fmt, epl_max);

    // using std::ranges::copy_if
    std::vector<Rect> vec3 {};
    std::ranges::copy_if(vec1, std::back_inserter(vec3), copy_pred);
    MT::print_ctr("\nvec3 (after ranges::copy_if):\n", vec3, fmt, epl_max);
}

void Ch10_03_ex3()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {2};

    std::vector<Rect> vec1 {s_Rects};
    MT::print_ctr("\nvec1 (orginal values):\n", vec1, fmt, epl_max);

    // calculation of iter_beg and num_elem skips first and last elements of vec1
    auto iter_beg = vec1.begin() + 1;
    auto num_elem = std::distance(iter_beg, vec1.end() - 1);
    std::println("\nnum_elem = {}", num_elem);

    // using std::copy_n (copies n elements starting from specified iterator)
    std::vector<Rect> vec2 {};
    std::copy_n(iter_beg, num_elem, std::back_inserter(vec2));
    MT::print_ctr("\nvec2 (after copy_n):\n", vec2, fmt, epl_max);

    // using std::ranges::copy_n (copies n elements starting from specified iterator)
    std::vector<Rect> vec3 {};
    std::ranges::copy_n(iter_beg, num_elem, std::back_inserter(vec3));
    MT::print_ctr("\nvec3 (after ranges::copy_n):\n", vec3, fmt, epl_max);
}

void Ch10_03_ex()
{
    std::println("\n----- Ch10_03_ex1() -----");
    Ch10_03_ex1();

    std::println("\n----- Ch10_03_ex2() -----");
    Ch10_03_ex2();

    std::println("\n----- Ch10_03_ex3() -----");
    Ch10_03_ex3();
}
