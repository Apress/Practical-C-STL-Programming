//-----------------------------------------------------------------------------
// Ch11_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>
#include <numeric>
#include "Ch11_01.h"
#include "MT.h"

void Ch11_01_ex1()
{
    using namespace std::numbers;
    const char* fmt = "{:9.2f} ";
    size_t epl_max {8};

    // initialize test array of radii
    std::array<double, 8> radii {};
    std::iota(radii.begin(), radii.end(), 1);
    MT::print_ctr("sphere radii:\n", radii, fmt, epl_max);

    // using std::for_each to print sphere areas
    auto sphere_area = [](double r)
        { std::print("{:9.2f} ", 4.0 * pi * r * r); };

    std::println("\nsphere surface areas:");
    std::for_each(radii.begin(), radii.end(), sphere_area);
    std::println("");

    // using std::ranges::for_each to print sphere volumes
    auto sphere_vol = [](double r)
        { std::print("{:9.2f} ", 4.0 * pi * r * r * r / 3.0); };

    std::println("\nsphere volumes:");
    std::ranges::for_each(radii, sphere_vol);
    std::println("");
}

void Ch11_01_ex2()
{
    using namespace std::numbers;
    const char* fmt = "{:9.2f} ";
    size_t epl_max {8};

    // initialize test array of edge lengths
    std::array<double, 8> edge_lengths {};
    std::iota(edge_lengths.begin(), edge_lengths.end(), 1);
    MT::print_ctr("octahedron edge lengths:\n", edge_lengths, fmt, epl_max);

    // using std::for_each_n to print octahedron areas
    auto octahedron_area = [](double el)
        { std::print("{:9.2f} ", 2.0 * sqrt3 * el * el); };

    std::println("\noctahedron surface areas:");
    std::for_each_n(edge_lengths.begin(), edge_lengths.size(), octahedron_area);
    std::println("");

    // using std::ranges::for_each_n to print octahedron volumes
    auto octahedron_vol = [](double el)
        { std::print("{:9.2f} ", sqrt2 * el * el * el / 3.0); };

    std::println("\noctahedron volumes:");
    std::ranges::for_each_n(edge_lengths.begin(), edge_lengths.size(),
        octahedron_vol);
    std::println("");
}

void Ch11_01_ex3()
{
    using namespace std::numbers;
    const char* fmt = "{:9.2f} ";
    size_t epl_max {8};

    // using std::ranges::for_each to calculate dodecahedron areas
    std::array<double, 8> areas {};
    std::iota(areas.begin(), areas.end(), 1);
    MT::print_ctr("dodecahedron edge lengths:\n", areas, fmt, epl_max);

    auto dodecahedron_area = [](double& x)
        { x *= 15.0 * phi / std::sqrt(3.0 - phi); };

    std::ranges::for_each(areas, dodecahedron_area);
    MT::print_ctr("\ndodecahedron surface areas:\n", areas, fmt, epl_max);

    // using std::ranges::for_each to calculate dodecahedron volumes
    std::array<double, 8> volumes {};
    std::iota(volumes.begin(), volumes.end(), 1);

    auto dodecahedron_vol = [](double& x)
        { x *= 5.0 * phi * phi * phi / (6.0 - 2.0 * phi); };

    std::ranges::for_each(volumes, dodecahedron_vol);
    MT::print_ctr("\ndodecahedron volumes:\n", volumes, fmt, epl_max);
}

void Ch11_01_ex()
{
    std::println("\n----- Ch11_01_ex1() -----\n");
    Ch11_01_ex1();

    std::println("\n----- Ch11_01_ex2() -----\n");
    Ch11_01_ex2();

    std::println("\n----- Ch11_01_ex3() -----\n");
    Ch11_01_ex3();
}
