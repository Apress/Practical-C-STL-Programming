//-----------------------------------------------------------------------------
// Ch10_07_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <forward_list>
#include <list>
#include <numeric>
#include <string>
#include <vector>
#include "Ch10_07.h"
#include "MT.h"
#include "MTH.h"

template <class T>
void ch10_remove_if_and_erase(const char* msg, T& ctr)
{
    const char* fmt {"{:4d} "};
    constexpr size_t epl_max {15};

    // using std::remove_if and ctr.erase (erase-remove idiom)
    std::print("{:s} - before std::remove_if", msg);
    MT::print_ctr("\n", ctr, fmt, epl_max);

    auto iter = std::remove_if(ctr.begin(), ctr.end(),
        MTH::is_prime<typename T::value_type>);

    auto num_erased = std::distance(iter, ctr.end());

    ctr.erase(iter, ctr.end());

    std::print("{:s} - after ctr.erase", msg);
    MT::print_ctr("\n", ctr, fmt, epl_max);
    std::println("num_erased: {:d}", num_erased);
}

void Ch10_07_ex1()
{
    using ll_t = long long;
    constexpr size_t n {30};

    // using ch10_remove_and_erase_if with different sequence containers
    std::vector<ll_t> vec1(n);
    std::iota(vec1.begin(), vec1.end(), 0);
    ch10_remove_if_and_erase("\nvec1", vec1);

    std::deque<ll_t> deq1(n);
    std::iota(deq1.begin(), deq1.end(), n);
    ch10_remove_if_and_erase("\ndeq1", deq1);

    std::list<ll_t> list1(n);
    std::iota(list1.begin(), list1.end(), n * 2);
    ch10_remove_if_and_erase("\nlist1", list1);
}

template <class T> requires std::forward_iterator<typename T::iterator>
void ch10_erase_if(const char* msg, T& ctr)
{
    const char* fmt {"{:4d} "};
    constexpr size_t epl_max {15};

    // using std::erase_if (C++20)
    std::print("{:s} - before std::erase_if", msg);
    MT::print_ctr("\n", ctr, fmt, epl_max);

    auto num_erased = std::erase_if(ctr, MTH::is_prime<typename T::value_type>);

    std::print("{:s} - after std::erase_if", msg);
    MT::print_ctr("\n", ctr, fmt, epl_max);
    std::println("num_erased: {:d}", num_erased);
}

void Ch10_07_ex2()
{
#ifdef __cpp_lib_ranges_iota
    using ll_t = long long;
    constexpr size_t n {30};

    // using ch10_erase_if with different sequence containers
    std::vector<ll_t> vec1(n);
    std::ranges::iota(vec1, 0);
    ch10_erase_if("\nvec1", vec1);

    std::deque<ll_t> deq1(n);
    std::ranges::iota(deq1, n);
    ch10_erase_if("\ndeq1", deq1);

    std::list<ll_t> list1(n);
    std::ranges::iota(list1, n * 2);
    ch10_erase_if("\nlist1", list1);

    std::forward_list<ll_t> fw_list1(n);
    std::ranges::iota(fw_list1, n * 3);
    ch10_erase_if("\nfw_list1", fw_list1);
#else
    std::println("Ch10_07_ex2() requires __cpp_lib_ranges_iota (C++23)");
#endif
}

void Ch10_07_ex()
{
    std::println("\n----- Ch10_07_ex1() -----\n");
    Ch10_07_ex1();

    std::println("\n----- Ch10_07_ex2() -----\n");
    Ch10_07_ex2();
}
