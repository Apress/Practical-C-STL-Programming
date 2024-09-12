//-----------------------------------------------------------------------------
// Ch09_02_ex.cpp
//-----------------------------------------------------------------------------

#include <deque>
#include <queue>
#include <string>
#include "Ch09_02.h"
#include "MT.h"

void Ch09_02_ex1()
{
    const char* fmt = "{:4d}";
    constexpr size_t epl_max {15};

    // create queue (std::queue doesn't support initializer lists)
    std::deque<int> x {10, 20, 30, 40};
    std::queue<int> queue1(x);
    MT::print_queue("\nqueue1 (initial values):\n", queue1, fmt, epl_max);

    // using push() and emplace()
    queue1.push(50);
    queue1.emplace(60);
    MT::print_queue("\nqueue1 (after insertions):\n", queue1, fmt, epl_max);

    // using front(), back(), size(), and empty()
    std::println("\nqueue1.front(): {:d}", queue1.front());
    std::println("queue1.back():  {:d}", queue1.back());
    std::println("queue1.size():  {:d}", queue1.size());
    std::println("queue1.empty(): {:s}", queue1.empty());

    // using pop()
    queue1.pop();
    queue1.pop();
    MT::print_queue("\nqueue1 (after pop operations):\n", queue1, fmt, epl_max);

    // using relational operators
    std::queue<int> queue2 {queue1};
    MT::print_queue("\nqueue2 (initial values):\n", queue2, fmt, epl_max);

    std::println("\nqueue1 == queue2: {:s}", queue1 == queue2);
    std::println("queue1 != queue2: {:s}", queue1 != queue2);
    std::println("queue1 <  queue2: {:s}", queue1 <  queue2);
    std::println("queue1 <= queue2: {:s}", queue1 <= queue2);
    std::println("queue1 >  queue2: {:s}", queue1 >  queue2);
    std::println("queue1 >= queue2: {:s}", queue1 >= queue2);
}

void Ch09_02_ex2()
{
    const char* fmt = "{:20s}";
    constexpr size_t epl_max {4};
    using queue_t = std::queue<std::string>;

    const auto il1 = {"apple", "banana cream",
        "blueberry", "cherry", "key lime", "peach", "pecan", "turtle"};

    // initialize queue1 (ctor is C++23)
#ifdef __cpp_lib_adaptor_iterator_pair_constructor
    queue_t queue1(il1.begin(), il1.end());
#else
    queue_t queue1 {};
    for (auto s : il1)
        queue1.push(s);
#endif

    MT::print_queue("\nqueue1 (initial values):\n", queue1, fmt, epl_max);

    // initialize queue2 (push_range is C++23)
    const auto il2 = {"pumpkin", "raspberry", "custard", "coconut cream",
            "lemon meringue", "strawberry"};

    queue_t queue2 {};
#ifdef __cpp_lib_containers_ranges
    queue2.push_range(il2);
    MT::print_queue("\nqueue2 (using push_range):\n", queue2, fmt, epl_max);
#else
    for (const auto& s : il2)
        queue2.push(s);
    MT::print_queue("\nqueue2 (using push ops):\n", queue2, fmt, epl_max);
#endif

    // swap queue1 and queue2
    queue1.swap(queue2);
    MT::print_queue("\nqueue1 (after swap):\n", queue1, fmt, epl_max);
    MT::print_queue("\nqueue2 (after swap):\n", queue2, fmt, epl_max);
}

void Ch09_02_ex()
{
    std::println("\n----- Ch09_02_ex1() -----");
    Ch09_02_ex1();

    std::println("\n----- Ch09_02_ex2() -----");
    Ch09_02_ex2();
}
