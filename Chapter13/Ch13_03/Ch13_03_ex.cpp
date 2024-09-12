//-----------------------------------------------------------------------------
// Ch13_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <list>
#include <numeric>
#include <stdexcept>
#include <vector>
#include "Ch13_03.h"
#include "MT.h"

static std::initializer_list<std::string> s_StringVals {"zero", "one", "two",
    "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

void Ch13_03_ex1()
{
    const char* fmt = "{:6s} ";
    constexpr size_t epl_max {12};

    // create test vector of strings
    std::vector<std::string> vec1 {s_StringVals};
    MT::print_ctr("vec1 (initial values)\n", vec1, fmt, epl_max);

    // using std::ranges::rotate (rotates left)
    std::ranges::rotate(vec1, vec1.begin() + 2);
    MT::print_ctr("\nvec1 (after std::ranges::rotate)\n", vec1, fmt, epl_max);

    // using std::ranges::rotate_copy (makes copy)
    std::vector<std::string> vec2 {};
    std::ranges::rotate_copy(vec1, vec1.begin() + 3, std::back_inserter(vec2));
    MT::print_ctr("\nvec1 (after std::ranges::rotate_copy)\n", vec1, fmt, epl_max);
    MT::print_ctr("\nvec2 (after std::ranges::rotate_copy)\n", vec2, fmt, epl_max);
}

auto rotate_left(auto& ctr, size_t n)
{
    // rotate ctr left by n elements
    if (n > ctr.size())
        throw std::runtime_error("rotate_left - invalid 'n'");

    // std::ranges::rotate() returns iterators
    // { ctr.begin() + (ctr.end() - middle), ctr.end() }
    auto middle = std::ranges::next(ctr.begin(), n);
    return std::ranges::rotate(ctr, middle);
}

auto rotate_right(auto& ctr, size_t n)
{
    // rotate ctr right by n elements
    if (n > ctr.size())
        throw std::runtime_error("rotate_right - invalid 'n'");

    auto middle = std::ranges::next(ctr.begin(), ctr.size() - n);
    return std::ranges::rotate(ctr, middle);
}

void Ch13_03_ex2()
{
    const char* fmt = "{:6s} ";
    constexpr size_t epl_max {12};

    // prints elements of range returned by rotate_left() and rotate_right()
    auto print_rotate_result = [](const char* msg, auto rng)
    {
        std::print("{}", msg);
        for (auto iter = rng.begin(); iter != rng.end(); ++iter)
            std::print("{:6s} ", *iter);
        std::println("");
    };

    // using rotate_left (list)
    std::list<std::string> list1 {s_StringVals};
    MT::print_ctr("list1 (initial values):\n", list1, fmt, epl_max);

    auto result_l = rotate_left(list1, 4);
    MT::print_ctr("\nlist1 (after rotate_left, n = 4):\n", list1, fmt, epl_max);
    print_rotate_result("\nresult_l:\n", result_l);

    // using rotate_right (deque)
    std::deque<std::string> deq1 {s_StringVals};
    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt, epl_max);

    auto result_r = rotate_right(deq1, 4);
    MT::print_ctr("\ndeq1 (after rotate_right, n = 4):\n", deq1, fmt, epl_max);
    print_rotate_result("\nresult_r:\n", result_r);
}

void Ch13_03_ex3()
{
#if __cpp_lib_shift >= 202202L
    const char* fmt = "{:6s} ";
    constexpr size_t epl_max {12};

    // transformation op for empty string
    auto tr_op = [](std::string& s) { return (s == "") ? "-----" : s; };

    // using std::ranges::shift_left (moves strings)
    std::vector<std::string> vec1 {s_StringVals};
    MT::print_ctr("vec1 (initial values):\n", vec1, fmt, epl_max);
    std::ranges::shift_left(vec1, 3);
    std::ranges::transform(vec1, vec1.begin(), tr_op);
    MT::print_ctr("\nvec1 (after shift_left, 3):\n", vec1, fmt, epl_max);

    // using std::ranges::shift_right (moves strings)
    std::vector<std::string> vec2 {s_StringVals};
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, epl_max);
    std::ranges::shift_right(vec2, 3);
    std::ranges::transform(vec2, vec2.begin(), tr_op);
    MT::print_ctr("\nvec2 (after shift_right, 3):\n", vec2, fmt, epl_max);
#else
    std::println("Ch13_03_ex3() requires __cpp_lib_shift >= 202202L (C++23)");
#endif
}

void Ch13_03_ex()
{
    std::println("\n----- Ch13_03_ex1() -----\n");
    Ch13_03_ex1();

    std::println("\n----- Ch13_03_ex2() -----\n");
    Ch13_03_ex2();

    std::println("\n----- Ch13_03_ex3() -----\n");
    Ch13_03_ex3();
}
