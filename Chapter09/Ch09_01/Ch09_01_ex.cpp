//-----------------------------------------------------------------------------
// Ch09_01_ex.cpp
//-----------------------------------------------------------------------------

#include <deque>
#include <ranges>
#include <stack>
#include <string>
#include "Ch09_01.h"
#include "TowerOfHanoi.h"

void Ch09_01_ex1()
{
    // print words lambda
    auto print_words = [](const char* msg, const std::stack<std::string>& words)
    {
        auto stk {words};

        std::println("{:s} (size = {:d})", msg, stk.size());

        while (!stk.empty())
        {
            // using top() and pop()
            std::print("| {:s} ", stk.top());
            stk.pop();
        }

        std::println("|");
    };

    // create stack (std::stack doesn't support initializer lists)
    const auto il1 = {"brought ...", "fathers", "our", "ago", "years", "and"};
    std::stack<std::string> words1(il1.begin(), il1.end());
    print_words("\nwords1 (initial values)", words1);

    // using push and emplace
    words1.push("score");
    words1.emplace("four");
    print_words("\nwords1 (after push and emplace)", words1);

    // create stack (constructor initialized using std::deque)
    const std::deque<std::string> deq2
        {"apple", "banana cream", "blueberry"};

    std::stack<std::string> words2(deq2);
    print_words("\nwords2 (initial values)", words2);
    
    // using push_range
    std::stack<std::string> words3 {words2};
    print_words("\nwords3 (initial values)", words3);

    const auto il3 = {"cherry", "key lime", "peach", "pecan", "turtle"};
#ifdef __cpp_lib_containers_ranges
    words3.push_range(il3);
    print_words("\nwords3 (after push_range)", words3);
#else
    for (const auto& s : il3)
        words3.push(s);
    print_words("\nwords3 (after push operations)", words3);
#endif
}

//#define TOH_VERBOSE_TEST

void Ch09_01_ex2()
{
    // verbose mode test
#ifdef TOH_VERBOSE_TEST
    TowerOfHanoi tow0 {};
    TowerOfHanoi::uint_t num_discs0 {7};

    std::println("\nbegin run0");
    tow0.run(num_discs0, true);
#endif

    // using even number of discs
    TowerOfHanoi tow1 {};
    TowerOfHanoi::uint_t num_discs1 {20};

    std::println("\nbegin run1");
    tow1.run(num_discs1, false);

    // using odd number of discs
    TowerOfHanoi tow2 {};
    TowerOfHanoi::uint_t num_discs2 {21};

    std::println("\n\nbegin run2");
    tow2.run(num_discs2, false);
}

void Ch09_01_ex()
{
    std::println("\n----- Ch09_01_ex1() -----");
    Ch09_01_ex1();

    std::println("\n----- Ch09_01_ex2() -----");
    Ch09_01_ex2();
}
