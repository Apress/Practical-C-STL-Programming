//-----------------------------------------------------------------------------
// Ch09_03_ex.cpp
//-----------------------------------------------------------------------------

#include <deque>
#include <functional>
#include <queue>
#include "Ch09_03.h"
#include "MT.h"
#include "RegPolygon.h"

void Ch09_03_ex1()
{
    const char* fmt = "{}";
    constexpr size_t epl_max {1};

    // create priority queue of RegPolygons
    // RegPolygon::operator<=> uses area
    const auto il1 =
        {RegPolygon {3, 1.0}, RegPolygon {4, 3.0}, RegPolygon {5, 2.0}};

    std::priority_queue<RegPolygon> polygons1(il1.begin(), il1.end());

    std::println("{:s}", RegPolygon::title_str());
    MT::print_priority_queue("\npolygons1 (initial values):\n",
        polygons1, fmt, epl_max);

    // add more polygons
    polygons1.push(RegPolygon {6, 4.0});
    polygons1.push(RegPolygon {4, 8.0});
    polygons1.emplace(RegPolygon {8, 5.0});
    polygons1.emplace(RegPolygon {10, 3.0});

    MT::print_priority_queue("\npolygons1 (after push/emplace operations):\n",
        polygons1, fmt, epl_max);
    std::println("\npolygons1.size(): {}", polygons1.size());
    std::println("\npolygons1.top():\n{}", polygons1.top());

    // remove elements
    polygons1.pop();
    polygons1.pop();

    MT::print_priority_queue("\npolygons1 (after pop operations):\n",
        polygons1, fmt, epl_max);
    std::println("\npolygons1.size(): {}", polygons1.size());
    std::println("\npolygons1.top():\n{}", polygons1.top());
}

// type aliases for custom priority_queue
using value_t = RegPolygon;
using container_t = std::deque<RegPolygon>;
using cmp_t = std::greater<RegPolygon>;
using pq_t = std::priority_queue<value_t, container_t, cmp_t>;

void Ch09_03_ex2()
{
    const char* fmt = "{}";
    constexpr size_t epl_max {1};

    // create priority queue of RegPolygons
    // add polygons using push_range
    pq_t polygons1 {};

    const auto il1 = {RegPolygon {3, 1.0}, RegPolygon {4, 3.0},
        RegPolygon {5, 2.0}, RegPolygon {6, 4.0}};

#ifdef __cpp_lib_containers_ranges
    polygons1.push_range(il1);
#else
    for (const auto rp : il1)
        polygons1.push(rp);
#endif

    std::println("{:s}", RegPolygon::title_str());
    MT::print_priority_queue("\npolygons1 (initial values):\n",
        polygons1, fmt, epl_max);

    // add more polygons
    polygons1.emplace(RegPolygon {3, 0.5});
    polygons1.emplace(RegPolygon {10, 0.25});
    polygons1.emplace(RegPolygon {12, 0.0125});

    MT::print_priority_queue("\npolygons1 (after emplace operations):\n",
        polygons1, fmt, epl_max);

    // remove elements
    polygons1.pop();
    polygons1.pop();
    MT::print_priority_queue("\npolygons1 (after pop operations):\n",
        polygons1, fmt, epl_max);
}

void Ch09_03_ex()
{
    std::println("\n----- Ch09_03_ex1() -----");
    Ch09_03_ex1();

    std::println("\n----- Ch09_03_ex2() -----");
    Ch09_03_ex2();
}
