//-----------------------------------------------------------------------------
// Ch04_03_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <forward_list>
#include <functional>
#include <iterator>
#include <string>
#include "Ch04_03.h"
#include "MT.h"

void Ch04_03_ex1()
{
    const char* fmt = "{:3d} ";

    // create forward_list
    std::forward_list<int> fw_list1 {10, 20, 30, 40, 50, 60, 70, 80};
    MT::print_ctr("\nfw_list1 (initial values):\n", fw_list1, fmt);

    // using forward_list::push_front
    fw_list1.push_front(15);
    fw_list1.push_front(25);
    fw_list1.push_front(35);
    fw_list1.push_front(45);
    fw_list1.push_front(55);
    fw_list1.push_front(65);
    fw_list1.push_front(75);
    MT::print_ctr("\nfw_list1 (after push_front):\n", fw_list1, fmt);

    // calculate num_elements
    auto num_elements = std::distance(fw_list1.begin(), fw_list1.end());
    std::println("num_elements: {:d}", num_elements);

    // using forward_list::sort
    fw_list1.sort();
    MT::print_ctr("\nlist1 (after sort):\n", fw_list1, fmt);

    // using forward_list::reverse
    fw_list1.reverse();
    MT::print_ctr("\nlist1 (after reverse):\n", fw_list1, fmt);
}

void Ch04_03_ex2()
{
    const char* fmt = "{:s} ";
    constexpr size_t epl {6};
    using fw_list_t = std::forward_list<std::string>;

    // initialize lists
    fw_list_t fw_list1 {"lemon", "lime", "orange", "tangerine", "grapefruit"};
    MT::print_ctr("\nfw_list1 (initial values):\n", fw_list1, fmt, epl);

    fw_list_t fw_list2 {"raspberry", "strawberry", "blueberry", "blackberry"};
    MT::print_ctr("\nfw_list2 (initial values):\n", fw_list2, fmt, epl);

    // using forward_list::splice
    auto iter_splice = fw_list1.begin();
    std::advance(iter_splice, 3);
    fw_list1.splice_after(iter_splice, fw_list2);
    MT::print_ctr("\nfw_list1 (after splice):\n", fw_list1, fmt, epl);
    MT::print_ctr("\nfw_list2 (after splice):\n", fw_list2, fmt, epl);

    // using forward_list::remove_if
    const std::string find_ss {"berry"};
    auto rem_op = [&find_ss](std::string s)
        {return s.find(find_ss) != std::string::npos;};

    fw_list1.remove_if(rem_op);
    MT::print_ctr("\nfw_list1 (after remove_if):\n", fw_list1, fmt, epl);
}

void Ch04_03_ex3()
{
    const char* fmt = "{:4d} ";
    constexpr size_t epl_max {10};

    // create forward_list
    std::forward_list<int> fw_list1 {60, 70, 80, 90, 100};
    MT::print_ctr("\nfw_list1 (initial values):\n", fw_list1, fmt, epl_max);

    // using forward_list::prepend_range
    const std::array<int, 5> arr1 {10, 20, 30, 40, 50};

#ifdef __cpp_lib_containers_ranges
    fw_list1.prepend_range(arr1);
#else
    fw_list1.insert_after(fw_list1.before_begin(), arr1.cbegin(), arr1.cend());
#endif
    MT::print_ctr("\nfw_list1 (after prepend_range):\n", fw_list1, fmt, epl_max);

    // using forward_list::insert_range_after
    auto iter = fw_list1.begin();
    std::advance(iter, 3);
    const std::array<int, 9> arr2 {41, 42, 43, 44, 45, 46, 47, 48, 49};

#ifdef __cpp_lib_containers_ranges
    fw_list1.insert_range_after(iter, arr2);
#else
    fw_list1.insert_after(iter, arr2.begin(), arr2.end());
#endif
    MT::print_ctr("\nfw_list1 (after insert_range_after):\n", fw_list1, fmt,
        epl_max);

    // using std::erase_if
    std::erase_if(fw_list1, [](int x) { return x % 3 == 0; });
    MT::print_ctr("\nfw_list1 (after erase_if):\n", fw_list1, fmt, epl_max);
}

void Ch04_03_ex()
{
    std::println("\n----- Ch04_03_ex1() -----");
    Ch04_03_ex1();

    std::println("\n----- Ch04_03_ex2() -----");
    Ch04_03_ex2();

    std::println("\n----- Ch04_03_ex3() -----");
    Ch04_03_ex3();
}
