//-----------------------------------------------------------------------------
// Ch04_04_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <deque>
#include <forward_list>
#include <iterator>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>
#include <typeinfo>
#include "Ch04_04.h"

template <typename T> 
void print_concepts(const char* msg, T& ctr)
{
    // test for const iterator
    std::string s{};
    auto iter = ctr.begin();
    auto citer = std::make_const_iterator(iter);
    bool is_const_iter = typeid(iter) == typeid(citer);

    // add surrounding {} or []
    auto mk_str = [is_const_iter](const char* s1)
    {
        // {} used for const iterator, [] for non-const
        std::string s2 {};
        s2 += (is_const_iter) ? "{" : "[";
        s2 += s1;
        s2 += (is_const_iter) ? "} " : "] ";
        return s2;
    };

    // construct string of iterator concepts for ctr
    if (std::input_iterator<decltype(iter)>)
        s += mk_str("input");
    if (std::forward_iterator<decltype(iter)>)
        s += mk_str("forward");
    if (std::bidirectional_iterator<decltype(iter)>)
        s += mk_str("bidirectional");
    if (std::random_access_iterator<decltype(iter)>)
        s += mk_str("random access");
    if (std::contiguous_iterator<decltype(iter)>)
        s += mk_str("contiguous");

    std::println("\niterator concepts for {:s}:\n{:s}", msg, s);
}

void Ch04_04_ex1()
{
    // print iterator concepts for different container types
    std::string str1 {};
    print_concepts("str1", str1);
    std::array<int, 2> arr1 {};
    print_concepts("arr1", arr1);

    std::vector<int> vec1 {};
    print_concepts("vec1", vec1);
    std::deque<int> deq1 {};
    print_concepts("deq1", deq1);

    std::list<int> list1 {};
    print_concepts("list1", list1);
    std::forward_list<int> fw_list1 {};
    print_concepts("fw_list1", fw_list1);

    std::set<int> set1 {};
    print_concepts("set1", set1);
    std::unordered_set<int> uno_set1 {};
    print_concepts("uno_set1", uno_set1);
}

void Ch04_04_ex()
{
    std::println("\n----- Ch04_04_ex1() -----");
    Ch04_04_ex1();
}
