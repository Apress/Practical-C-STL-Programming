//-----------------------------------------------------------------------------
// Ch10_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <string>
#include <deque>
#include "Ch10_05.h"
#include "MT.h"

namespace
{
    const std::initializer_list<std::string> s_Strings {"one", "two", "three",
    "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve"};
}

void Ch10_05_ex1()
{
    const char* fmt {"{:s} "};
    constexpr size_t epl_max {15};

    // using std::reverse
    std::deque<std::string> deq1 {s_Strings};
    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt, epl_max);
    std::reverse(deq1.begin(), deq1.end());
    MT::print_ctr("\ndeq1 (after std::reverse):\n", deq1, fmt, epl_max);

    // using std::ranges::reverse
    std::deque<std::string> deq2 {s_Strings};
    MT::print_ctr("\ndeq2 (initial values):\n", deq2, fmt, epl_max);
    std::ranges::reverse(deq2);
    MT::print_ctr("\ndeq2 (after std::ranges::reverse):\n", deq2, fmt, epl_max);
}

void Ch10_05_ex2()
{
    const char* fmt {"{:s} "};
    constexpr size_t epl_max {15};

    std::deque<std::string> deq1 {s_Strings};
    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt, epl_max);

    // using std::reverse_copy
    std::deque<std::string> deq2 {};
    std::reverse_copy(deq1.begin(), deq1.end(), std::back_inserter(deq2));
    MT::print_ctr("\ndeq2 (after std::reverse_copy):\n", deq2, fmt, epl_max);

    // using std::ranges::reverse_copy
    std::deque<std::string> deq3 {};
    std::ranges::reverse_copy(deq1, std::back_inserter(deq3));
    MT::print_ctr("\ndeq3 (after std::ranges::reverse_copy):\n", deq3, fmt,epl_max);
}

void Ch10_05_ex()
{
    std::println("\n----- Ch10_05_ex1() -----");
    Ch10_05_ex1();

    std::println("\n----- Ch10_05_ex2() -----");
    Ch10_05_ex2();
}
