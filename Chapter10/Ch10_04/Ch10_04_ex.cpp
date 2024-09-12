//-----------------------------------------------------------------------------
// Ch10_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch10_04.h"
#include "MT.h"
#include "Image.h"

void Ch10_04_ex1()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {1};

    std::vector<Image> vec1
    {
        {640, 480}, {800, 600}, {1024, 768}, {1280, 1024},
        {1600, 1200}, {1920, 1080}, {3840, 2160}, {7680, 4320},
    };

    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // using std::move - moves entire container
    std::vector<Image> vec2 {std::move(vec1)};
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, epl_max);

    // using std::move - moves container's elements
    std::vector<Image> vec3 {};

    for (auto& im : vec2)
        vec3.push_back(std::move(im));

    MT::print_ctr("\nvec2 (after std::move):\n", vec2, fmt, epl_max);
    MT::print_ctr("\nvec3 (after std::move):\n", vec3, fmt, epl_max);
}

void Ch10_04_ex2()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {1};

    std::vector<Image> vec1 {{10, 20}, {30, 40}, {50, 60}, {70, 80}};
    std::vector<Image> vec2 {{100, 200}, {300, 400}, {500, 600}, {700, 800}};
    std::vector<Image> vec3 {{1000, 2000}, {3000, 4000},
        {5000, 6000}, {7000, 8000}};

    // using std::swap_ranges
    std::println("\nBefore std::swap_ranges");
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);
    MT::print_ctr("\nvec3:\n", vec3, fmt, epl_max);

    std::swap_ranges(vec1.begin(), vec1.end(), vec2.begin());

    std::println("\nAfter std::swap_ranges");
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);
    MT::print_ctr("\nvec3:\n", vec3, fmt, epl_max);

    // using std::ranges::swap_ranges
    std::ranges::swap_ranges(vec1, vec3);
    std::println("\nAfter std::ranges::swap_ranges");
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);
    MT::print_ctr("\nvec3:\n", vec3, fmt, epl_max);
}

void Ch10_04_ex()
{
    std::println("\n----- Ch10_04_ex1() -----\n");
    Ch10_04_ex1();

    std::println("\n----- Ch10_04_ex2() -----\n");
    Ch10_04_ex2();
}
