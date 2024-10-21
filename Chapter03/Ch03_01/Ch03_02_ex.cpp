//-----------------------------------------------------------------------------
// Ch03_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <format>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Ch03_02.h"
#include "MT.h"
#include "Point2D.h"

void Ch03_02_ex1()
{
    const char* fmt = "{:6d}";

    // create test vectors
    std::vector<int> vec1 {10, 20, 30, 40, 50}; // vec1 = {10, 20, 30, 40, 50}
    std::vector<int> vec2(vec1.size());         // vec2 = {0, 0, 0, 0, 0}
    std::vector<int> vec3(vec1.size(), 7);      // vec3 = {7, 7, 7, 7, 7}

    MT::print_ctr("\nvec1: ", vec1, fmt);
    MT::print_ctr("vec2: ", vec2, fmt);
    MT::print_ctr("vec3: ", vec3, fmt);

    // using operator[] and .at()
    for (size_t i = 0; i < vec1.size(); ++i)
        vec2[i] = vec1.at(i) * vec3.at(i);
    MT::print_ctr("\nvec2 (after calculation): ", vec2, fmt);

    // create more test vectors
    std::vector<unsigned long long> vec4 {100, 200, 300, 400, 500, 600, 700, 800};
    std::vector<unsigned long long> vec5(vec4.size(), 100);
    std::vector<unsigned long long> vec6 {vec4.size()};        // vec6 = {8}
    std::vector<unsigned long long> vec7 {};                   // vec7 = {}

    MT::print_ctr("\nvec4:  ", vec4, fmt);
    MT::print_ctr("vec5:  ", vec5, fmt);
    MT::print_ctr("vec6: ", vec6, fmt);
    MT::print_ctr("vec7: ", vec7, fmt);

    // using iterators
    auto iter4 = vec4.begin();
    auto iter5 = vec5.begin();
    for (; iter4 != vec4.end(); ++iter4, ++iter5)
        *iter5 += *iter4 / 2;
    MT::print_ctr("\nvec5:  ", vec5, fmt);

    // using front() and back()
    std::println("\nvec4.front(): {:6d}", vec4.front());
    std::println("vec4.back():  {:6d}", vec4.back());

    // using clear()
    vec5.clear();
    MT::print_ctr("\nvec5 (after clear): ", vec5, fmt);
    std::println("vec5.size(): {:d}", vec5.size());
}

void Ch03_02_ex2()
{
    const char* fmt = "{:9.4f}  ";
    constexpr size_t epl_max {6};
    constexpr size_t n {10};
    std::vector<double> vec1 {};        // empty vector

    // lambdas expression for printing size attributes
    auto print_size_cap = [&vec1] ()
    {
        std::println("vec1.size(): {:d}  vec1.capacity(): {:d}",
            vec1.size(), vec1.capacity());
    };

    // add elements to vec1 using push_back()
    for (size_t i = 0; i < n; ++i)
        vec1.push_back(std::sqrt(static_cast<double>(i + 1)));
    MT::print_ctr("\nvec1 - initial values:\n", vec1, fmt, epl_max);
    print_size_cap();

    // remove elements from vec1 using pop_back()
    while (vec1.size() >= n / 2)
        vec1.pop_back();
    MT::print_ctr("\nvec1 - after pop_back operations:\n", vec1, fmt, epl_max);
    print_size_cap();

    // add elements to middle of vec1 using insert
    std::array<double, 8> arr1 {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0};
    vec1.insert(vec1.begin() + 2, arr1.begin(), arr1.end());
    MT::print_ctr("\nvec1 - after middle inserts:\n", vec1, fmt, epl_max);
    print_size_cap();

    // add elements to end of vec1 using insert
    std::array<double, 6> arr2 {-10.0, -20.0, -30.0, -40.0, -50.0, -60.0};
    vec1.insert(vec1.end(), arr2.begin(), arr2.end());
    MT::print_ctr("\nvec1 - after end inserts:\n", vec1, fmt, epl_max);
    print_size_cap();

    // remove elements from vec1 using member erase (erases vec1[3] and vec1[4])
    vec1.erase(vec1.begin() + 3, vec1.begin() + 5);
    MT::print_ctr("\nvec1 - after erase operation:\n", vec1, fmt, epl_max);
    print_size_cap();
}

void Ch03_02_ex3()
{
    const char* fmt = "{:s} ";
    std::vector<std::string> planets1;
    const char* planets_cstr1[] {"Mercury", "Venus", "Earth", "Mars"};
    const char* planets_cstr2[] {"Jupiter", "Saturn", "Uranus", "Neptune"};

    // using std::copy
    std::copy(std::begin(planets_cstr1), std::end(planets_cstr1),
        std::back_inserter(planets1));
    MT::print_ctr("planets1: ", planets1, fmt);

    // using assignment ctor and emplace_back
    std::vector<std::string> planets2 {planets1};
    planets2.emplace_back(planets_cstr2[0]);
    planets2.emplace_back(planets_cstr2[1]);
    planets2.emplace_back(planets_cstr2[2]);
    planets2.emplace_back(planets_cstr2[3]);
    MT::print_ctr("planets2: ", planets2, fmt);

    // using std::find
    auto iter_mars = std::find(planets2.begin(), planets2.end(), "Mars");
    bool found_mars = iter_mars != planets2.end();
    std::println("\nfound_mars:  {:s}", found_mars);

    // using std::ranges::find (C++20)
    auto iter_pluto = std::ranges::find(planets2, "Pluto");
    bool found_pluto = iter_pluto != planets2.end();
    std::println("found_pluto: {:s}", found_pluto);

    // using std::sort
    auto planets3 {planets2};
    std::sort(planets2.begin(), planets2.end());
    MT::print_ctr("\nplanets2 sorted: ", planets2, fmt);

    // using std::ranges::sort (C++20)
    std::ranges::sort(planets3);
    MT::print_ctr("planets3 sorted: ", planets3, fmt);

    // using operators
    std::println("planets2 == planets3 (expect true): {:s}", planets2 == planets3);
    std::swap(planets2[3], planets2[4]);
    MT::print_ctr("\nplanets2 after swap: ", planets2, fmt);
    MT::print_ctr("planets3 after swap: ", planets3, fmt);
    std::println("planets2 >  planets3 (expect true):  {:s}", planets2 > planets3);
    std::println("planets2 <  planets3 (expect false): {:s}", planets2 < planets3);
}

void Ch03_02_ex4()
{
    const char* fmt {"{} "};
    constexpr size_t epl_max {6};

    // create  point vectors
    std::vector<Point2D<int>> points {{3, 4}, {7, 9}, {-2, -4}, {-5, 6}, {12,10},
        {3, -4}, {10, 2}, {3, -4}, {12, 10}, {-9, -2}, {-6, 4}, {12, 10}};
    std::vector<Point2D<int>> points_to_erase
        {{3, -4}, {-7, 6}, {7, 9}, {12,10}};

    MT::print_ctr("\nvector points (initial values):\n", points, fmt, epl_max);
    std::println("points.size(): {:d}\n", points.size());

    // perform erasures
    for (const auto& point : points_to_erase)
    {
        // using std::erase (C++20) - erases all occurrences of point from points
        auto num_erased = std::erase(points, point); 

        // print results
        std::print("current point {} - ", point);

        if (num_erased)
        {
            std::string s = (num_erased > 1) ? "s\n" : "\n";
            std::print("erased {:d} point{:s}", num_erased, s);
        }                
        else
            std::print("not found\n");
    }

    MT::print_ctr("\nvector points (after erasures):\n", points, fmt, epl_max);
    std::println("points.size(): {:d}", points.size());
}

void Ch03_02_ex()
{
    std::println("\n----- Ch03_02_ex1() -----");
    Ch03_02_ex1();

    std::println("\n----- Ch03_02_ex2() -----");
    Ch03_02_ex2();

    std::println("\n----- Ch03_02_ex3() -----");
    Ch03_02_ex3();

    std::println("\n----- Ch03_02_ex4() -----");
    Ch03_02_ex4();
}
