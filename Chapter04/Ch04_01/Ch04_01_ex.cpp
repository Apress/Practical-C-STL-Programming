//-----------------------------------------------------------------------------
// Ch04_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <string>
#include <version>
#include "Ch04_01.h"
#include "Line.h"
#include "MT.h"

void Ch04_01_ex1()
{
    const char* fmt = "{:5d} ";

    // create deques
    std::deque<int> deq1 {10, 20, 30, 40, 50};
    std::deque<int> deq2 (deq1.size());

    // access deque elements using operator[] and .at()
    for (size_t i = 0; i < deq1.size(); ++i)
        deq2[i] = deq1.at(i) * 5;

    MT::print_ctr("\ndeq1: ", deq1, fmt);
    MT::print_ctr("deq2: ", deq2, fmt);

    // create deques
    std::deque<long> deq3 {100, 200, 300, 400, 500, 600};
    std::deque<long> deq4(deq3.size(), 1000);

    // using iterators
    auto iter3 = deq3.begin();
    auto iter4 = deq4.begin();
    for (; iter3 != deq3.end(); ++iter3, ++iter4)
        *iter4 += *iter3 / 2;

    MT::print_ctr("\ndeq3: ", deq3, fmt);
    MT::print_ctr("deq4: ", deq4, fmt);
}

void Ch04_01_ex2()
{
    std::deque<double> deq1 {};
    const char* fmt {"{:7.1f} "};

    // using deque::push_back
    deq1.push_back(50.0);
    deq1.push_back(60.0);
    deq1.push_back(70.0);
    deq1.push_back(80.0);
    MT::print_ctr("\ndeq1 (after push_back operations):\n", deq1, fmt);

    // using deque::push_front
    deq1.push_front(40.0);
    deq1.push_front(30.0);
    deq1.push_front(20.0);
    deq1.push_front(10.0);
    MT::print_ctr("\ndeq1 (after push_front operations):\n", deq1, fmt);

    // using deque::pop_back
    deq1.pop_back();
    deq1.pop_back();
    MT::print_ctr("\ndeq1 (after pop_back operations):\n", deq1, fmt);

    // using deque::pop_front
    deq1.pop_front();
    deq1.pop_front();
    MT::print_ctr("\ndeq1 (after pop_front operations):\n", deq1, fmt);

    // add elements to "middle" of deq1 using insert
    std::array<double, 5> arr1 {1000.0, 2000.0, 3000.0, 4000.0, 5000.0};
    deq1.insert(deq1.begin() + 2, arr1.begin(), arr1.end());
    MT::print_ctr("\ndeq1 (after insert):\n", deq1, fmt);
}

void Ch04_01_ex3()
{
    using line_t = Line<double>;

    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // using deque::emplace_front
    std::deque<line_t> deq1 {};
    deq1.emplace_front(line_t {0.0, 0.0, 3.0, 4.0});
    deq1.emplace_front(line_t {0.0, 1.0, 3.0, 4.0});
    deq1.emplace_front(line_t {1.0, 0.0, 3.0, 4.0});
    deq1.emplace_front(line_t {1.0, 1.0, 3.0, 4.0});
    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt, epl_max);

    // using deque::emplace_back
    std::deque<line_t> deq2 {};
    deq2.emplace_back(line_t {10.0, 10.0, 30.0, 40.0});
    deq2.emplace_back(line_t {10.0, 20.0, 30.0, 40.0});
    deq2.emplace_back(line_t {20.0, 10.0, 30.0, 40.0});
    deq2.emplace_back(line_t {20.0, 20.0, 30.0, 40.0});
    MT::print_ctr("\ndeq2: (initial values):\n", deq2, fmt, epl_max);

    // using deque::insert_range (C++23)
    auto iter_insert = deq1.begin() + deq1.size() / 2;
#ifdef __cpp_lib_containers_ranges
    deq1.insert_range(iter_insert, deq2);
#else
    deq1.insert(iter_insert, deq2.begin(), deq2.end());
#endif
    MT::print_ctr("\ndeq1 (after insert_range):\n", deq1, fmt, epl_max);
}

void Ch04_01_ex4()
{
    const char* fmt {"{:5s}"};

    // initialize deque of strings
    std::deque<std::string> deq1 {"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt);

    // using append_range (C++23)
    std::array<std::string, 6> arr1 {"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

#ifdef __cpp_lib_containers_ranges
    deq1.append_range(arr1);
#else
    deq1.insert(deq1.end(), arr1.begin(), arr1.end());
#endif
    MT::print_ctr("\ndeq1 (after append_range):\n", deq1, fmt);

    // using std::sort
    std::sort(deq1.begin(), deq1.end());
    MT::print_ctr("\ndeq1 (after sort using operator<):\n", deq1, fmt);

    std::sort(deq1.begin(), deq1.end(), std::greater<>());
    MT::print_ctr("deq1 (after sort using operator>):\n", deq1, fmt);

    // using std::ranges::sort
    std::deque deq2 {deq1};
    std::ranges::sort(deq2);
    MT::print_ctr("\ndeq2 (after ranges::sort using operator<):\n", deq2, fmt);

    std::ranges::sort(deq2, std::greater<>());
    MT::print_ctr("deq2 (after ranges::sort using operator>):\n", deq2, fmt);

    // using relational operators
    std::println("\ndeq1 == deq2: {:s}", deq1 == deq2);
    std::swap(deq1[5], deq1[7]);
    std::println("deq1 <= deq2: {:s}", deq1 <= deq2);
    std::println("deq1 >= deq2: {:s}", deq1 >= deq2);
}

void Ch04_01_ex5()
{
    const char* fmt = "{:6.1f}";
    constexpr size_t epl_max {10};
    constexpr double rem_val {-1.0};
    std::println("\nrem_val: {:.1f}", rem_val);

    // create test deques
    std::deque<double> deq1 {10.0, 20.0, rem_val, 30.0, 40.0,
        rem_val, 50.0, rem_val, 60.0, 70.0};
    std::deque<double> deq2 {deq1};

    MT::print_ctr("\ndeq1 (initial values):\n", deq1, fmt, 10);
    std::println("deq1.size(): {:d}", deq1.size());

    // using std::remove and std::deque::erase (erase-remove idiom)
    auto iter_rem = std::remove(deq1.begin(), deq1.end(), rem_val);
    MT::print_ctr("\ndeq1 (after std::remove):\n", deq1, fmt, epl_max);
    std::println("deq1.size(): {:d}", deq1.size());

    auto num_erased1 = deq1.end() - iter_rem;
    deq1.erase(iter_rem, deq1.end());
    MT::print_ctr("\ndeq1 (after erase):\n", deq1, fmt, epl_max);
    std::println("num_erased1: {:d}", num_erased1);
    std::println("deq1.size(): {:d}", deq1.size());

    // using std::erase (C++20)
    MT::print_ctr("\ndeq2 (initial values):\n", deq2, fmt, 10);
    std::println("deq2.size(): {:d}", deq2.size());
    auto num_erased2 = std::erase(deq2, rem_val);
    MT::print_ctr("\ndeq2 (after std::erase):\n", deq2, fmt, epl_max);
    std::println("num_erased2: {:d}", num_erased2);
    std::println("deq2.size(): {:d}", deq2.size());
}

void Ch04_01_ex()
{
    std::println("\n----- Ch04_01_ex1() -----");
    Ch04_01_ex1();

    std::println("\n----- Ch04_01_ex2() -----");
    Ch04_01_ex2();

    std::println("\n----- Ch04_01_ex3() -----");
    Ch04_01_ex3();

    std::println("\n----- Ch04_01_ex4() -----");
    Ch04_01_ex4();

    std::println("\n----- Ch04_01_ex5() -----");
    Ch04_01_ex5();
}
