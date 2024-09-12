//-----------------------------------------------------------------------------
// Ch10_06_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <format>
#include <numeric>
#include <string>
#include <vector>
#include "Ch10_06.h"
#include "MT.h"
#include "MTH.h"

using namespace std::string_literals;

namespace
{
    const std::initializer_list<std::string> s_Strings {"one", "two", "three",
      "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve"};
}

void Ch10_06_ex1()
{
    const char* fmt {"{:8s} "};
    constexpr size_t epl_max {6};

    // initialize deque of strings
    std::deque<std::string> deq1 {s_Strings};
    MT::print_ctr("deq1 (initial values):\n", deq1, fmt, epl_max);

    // using std::replace
    std::replace(deq1.begin(), deq1.end(), "five"s, "5"s);
    MT::print_ctr("\ndeq1 (after std::replace):\n", deq1, fmt, epl_max);

    // using std::ranges::replace
    std::deque<std::string> deq2 {deq1};
    deq2.emplace_back("ten");
    deq2.emplace_front("ten");
    MT::print_ctr("\ndeq2 (initial values):\n", deq2, fmt, epl_max);

    std::ranges::replace(deq2, "ten"s, "10"s);
    MT::print_ctr("\ndeq2 (after std::ranges::replace):\n", deq2, fmt, epl_max);
}

void Ch10_06_ex2()
{
    using ll_t = long long;
    constexpr size_t n {40};
    const char* fmt {"{:5d} "};
    constexpr size_t epl_max {10};

    // using std::iota
    std::vector<ll_t> vec1(n);
    std::iota(vec1.begin(), vec1.end(), 0);
    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);

    // using std::replace_if
    std::replace_if(vec1.begin(), vec1.end(), MTH::is_prime<ll_t>, -999);
    MT::print_ctr("\nvec1 (after std::replace_if):\n", vec1, fmt, epl_max);

    // using std::ranges::iota (C++23)
    std::vector<ll_t> vec2(n);

#ifdef __cpp_lib_ranges_iota
    std::ranges::iota(vec2, 0);
#else
    std::iota(vec2.begin(), vec2.end(), 0);
#endif
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, epl_max);

    // using std::ranges::replace_if
    std::ranges::replace_if(vec2, MTH::is_prime<ll_t>, -999);
    MT::print_ctr("\nvec2 (after std::ranges::replace_if):\n", vec2, fmt, epl_max);
    std::println("\nstd::ranges::iota() requires C++23");
}

void Ch10_06_ex3()
{
    const char* fmt {"{:8s} "};
    constexpr size_t epl_max {6};

    // initialize deque of strings
    std::deque<std::string> deq1 {s_Strings};
    MT::print_ctr("deq1 (initial values):\n", deq1, fmt, epl_max);

    // using std::replace_copy
    std::deque<std::string> deq2 {};
    std::replace_copy(deq1.begin(), deq1.end(), std::back_inserter(deq2),
        "five"s, "5"s);
    MT::print_ctr("\ndeq2 (after std::replace_copy):\n", deq2, fmt, epl_max);

    // using std::ranges::replace_copy
    std::deque<std::string> deq3 {};
    std::ranges::replace_copy(deq1, std::back_inserter(deq3), "five"s, "5"s);
    MT::print_ctr("\ndeq3 (after std::ranges::replace_copy):\n", deq3, fmt,epl_max);
}

void Ch10_06_ex4()
{
    using ll_t = long long;
    constexpr size_t n {40};
    const char* fmt {"{:5d} "};
    constexpr size_t epl_max {10};

    // initialize vector of integers
    std::vector<ll_t> vec1(n);

#ifdef __cpp_lib_ranges_iota
    std::ranges::iota(vec1, 0);
#else
    std::iota(vec1.begin(), vec1.end(), 0);
#endif

    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);

    // using std::ranges::replace_copy_if
    std::vector<ll_t> vec2 {};

    std::ranges::replace_copy_if(vec1, std::back_inserter(vec2),
        MTH::is_prime<ll_t>, -999);

    MT::print_ctr("\nvec2 (after std::ranges::replace_copy_if):\n",
        vec2, fmt, epl_max);
}

void Ch10_06_ex()
{
    std::println("\n----- Ch10_06_ex1() -----\n");
    Ch10_06_ex1();

    std::println("\n----- Ch10_06_ex2() -----\n");
    Ch10_06_ex2();

    std::println("\n----- Ch10_06_ex3() -----\n");
    Ch10_06_ex3();

    std::println("\n----- Ch10_06_ex4() -----\n");
    Ch10_06_ex4();
}
