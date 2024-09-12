//-----------------------------------------------------------------------------
// Ch10_08_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <numeric>
#include <vector>
#include "Ch10_08.h"
#include "MT.h"
#include "Rect.h"

namespace
{
    const std::vector<Rect> s_Rectangles
    {
        {0, 0, 640, 480}, {0, 0, 800, 600}, {0, 0, 1024, 768},
        {0, 0, 1280, 1024}, {0, 0, 1600, 1200}, {0, 0, 1920, 1080},
        {0, 0, 3840, 2160}, {0, 0, 7680, 4320}
    };
}

void Ch10_08_ex1()
{
    const char* fmt {"{:4d} "};
    constexpr size_t epl_max {10};

    // using std::fill
    std::vector<int> vec1(10);
    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);

    std::fill(vec1.begin(), vec1.end(), -1);
    MT::print_ctr("\nvec1 (after std::fill):\n", vec1, fmt, epl_max);

    // using std::ranges::fill
    std::vector<int> vec2(10);
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, epl_max);

    std::ranges::fill(vec2, -2);
    MT::print_ctr("\nvec1 (after std::ranges::fill):\n", vec2, fmt, epl_max);
}

void Ch10_08_ex2()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {2};
    const Rect fill_val {0, 0, 96, 72};

    // using std::fill
    std::vector<Rect> vec1 {s_Rectangles};
    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);
    std::fill(vec1.begin(), vec1.end(), fill_val);
    MT::print_ctr("\nvec1 (after std::fill):\n", vec1, fmt, epl_max);

    // using std::ranges::fill
    std::vector<Rect> vec2 {s_Rectangles};
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, epl_max);
    std::ranges::fill(vec2, fill_val);
    MT::print_ctr("\nvec2 (after std::fill):\n", vec2, fmt, epl_max);
}

void Ch10_08_ex3()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {2};

    std::vector<Rect> vec1 {s_Rectangles};
    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);
    
    // using std::ranges::fill_n
    auto iter_beg = vec1.begin() + 1;
    auto num_elem = std::distance(vec1.begin() + 1, vec1.end() - 1);
    std::println("\nnum_elem = {:d}", num_elem);
    std::ranges::fill_n(iter_beg, num_elem, Rect{10, 20, 30, 40});
    MT::print_ctr("\nvec1 (after std::fill_n):\n", vec1, fmt, epl_max);
}

void Ch10_08_ex()
{
    std::println("\n----- Ch10_08_ex1() -----\n");
    Ch10_08_ex1();

    std::println("\n----- Ch10_08_ex2() -----\n");
    Ch10_08_ex2();

    std::println("\n----- Ch10_08_ex3() -----\n");
    Ch10_08_ex3();
}
