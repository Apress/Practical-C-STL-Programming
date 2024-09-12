//-----------------------------------------------------------------------------
// Ch13_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <vector>
#include "Ch13_01.h"
#include "MT.h"
#include "RegPolygon.h"

namespace
{
    // parameters for random RegPolygon generation
    constexpr unsigned int c_Seed1a {17};
    constexpr unsigned int c_Seed2a {13};
    constexpr unsigned int c_Seed1b {19};
    constexpr unsigned int c_Seed2b {23};
    constexpr size_t c_NumPolygons1 {10};
    constexpr size_t c_NumPolygons2 {6};
}

void Ch13_01_ex1()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {1};

    // create two containers of random RegPolygons
    std::vector<RegPolygon> polygons1 = RegPolygon::get_random_polygons(
        c_NumPolygons1, c_Seed1a, c_Seed2a);

    std::vector<RegPolygon> polygons_temp = RegPolygon::get_random_polygons(
        c_NumPolygons2, c_Seed1b, c_Seed2b);

    std::deque<RegPolygon> polygons2 {};
    std::ranges::copy(polygons_temp, std::back_inserter(polygons2));

    // sort polygon containers (uses RegPolygon::operator<)
    std::ranges::sort(polygons1);
    std::println("\npolygons1 (after sort)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons1, fmt, epl_max);

    std::ranges::sort(polygons2);
    std::println("\npolygons2 (after sort)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons2, fmt, epl_max);

    // using std::ranges::merge
    std::vector<RegPolygon> polygons3 {};
    std::ranges::merge(polygons1, polygons2, std::back_inserter(polygons3));

    std::println("\npolygons3 (after merge)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons3, fmt, epl_max);
}

void Ch13_01_ex2()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {1};

    // create two vectors of random RegPolygons
    std::vector<RegPolygon> polygons1 = RegPolygon::get_random_polygons(
        c_NumPolygons1, c_Seed1a * 2, c_Seed2a * 2);

    std::vector<RegPolygon> polygons2 =  RegPolygon::get_random_polygons(
        c_NumPolygons2, c_Seed2a * 2 , c_Seed2b * 2 );

    // comparison operator
    auto cmp_op = [](const RegPolygon& rp1, const RegPolygon& rp2)
        { return rp1.NumSides() > rp2.NumSides(); };

    // sort polygon vectors using cmp_op
    std::ranges::sort(polygons1, cmp_op);
    std::println("\npolygons1 (after sort)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons1, fmt, epl_max);

    std::ranges::sort(polygons2, cmp_op);
    std::println("\npolygons2 (after sort)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons2, fmt, epl_max);

    // move elements from polygons2 to end of polygons1
    std::ranges::move(polygons2, std::back_inserter(polygons1));
    std::println("\npolygons1 (after move)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons1, fmt, epl_max);

    // using std::ranges::inplace_merge (uses cmp_op)
    auto iter_mid = std::ranges::next(polygons1.begin(), c_NumPolygons1);
    std::ranges::inplace_merge(polygons1, iter_mid, cmp_op);

    std::println("\npolygons1 (after inplace_merge)");
    std::println("{:s}", RegPolygon::title_str());
    MT::print_ctr("", polygons1, fmt, epl_max);
}

void Ch13_01_ex()
{
    std::println("\n----- Ch13_01_ex1() -----");
    Ch13_01_ex1();

    std::println("\n----- Ch13_01_ex2() -----");
    Ch13_01_ex2();
}
