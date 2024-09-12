//-----------------------------------------------------------------------------
// Ch04_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <iterator>
#include <list>
#include <stdexcept>
#include "Ch04_02.h"
#include "MT.h"
#include "Point2D.h"

void Ch04_02_ex1()
{
    const char* fmt = "{:<5d}";
    std::list<int> list1 {20, 30, 40, 40, 50, 60, 70, 70, 70, 80};
    MT::print_ctr("list1 (initial values):\n", list1, fmt);

    // using list::push_front and list::push_back
    list1.push_front(10);
    list1.push_back(90);
    MT::print_ctr("\nlist1 (after push_front, push_back):\n", list1, fmt);
    std::print("list1.size():  {:d}\n", list1.size());
    std::print("list1.front(): {:d}\n", list1.front());
    std::print("list1.back():  {:d}\n", list1.back());

    // using std::advance
    auto iter_mid = list1.begin();
    std::advance(iter_mid, list1.size() / 2);

    // using list::insert
    std::array<int, 3> more_vals {-40, -50, -60};
    list1.insert(iter_mid, more_vals.begin(), more_vals.end());
    MT::print_ctr("\nlist1 (after insert):\n", list1, fmt);
    std::print("list1.size():  {:d}\n", list1.size());
    std::print("list1.front(): {:d}\n", list1.front());
    std::print("list1.back():  {:d}\n", list1.back());

    // using remove
    list1.remove(40);
    list1.remove(70);
    MT::print_ctr("\nlist1 (after remove):\n", list1, fmt);
    std::print("list1.size():  {:d}\n", list1.size());
    std::print("list1.front(): {:d}\n", list1.front());
    std::print("list1.back():  {:d}\n", list1.back());

    // using remove_if
    auto rem_op = [] (int x) { return x % 60 == 0; };
    list1.remove_if(rem_op);
    MT::print_ctr("\nlist1 (after remove_if):\n", list1, fmt);
    std::print("list1.size():  {:d}\n", list1.size());
    std::print("list1.front(): {:d}\n", list1.front());
    std::print("list1.back():  {:d}\n", list1.back());
}

void Ch04_02_ex2()
{
    const char* fmt = "{:s} ";

    // create lists
    std::list<std::string> list1 {"Jan", "Feb", "Mar", "Apr",
        "Sep", "Oct", "Nov", "Dec"};
    std::list<std::string> list2 {"May", "Jun", "Jul", "Aug"};

    MT::print_ctr("\nlist1 (initial values): ", list1, fmt);
    MT::print_ctr("list2 (initial values): ", list2, fmt);

    // using list::splice
    auto iter_splice = list1.begin();
    std::advance(iter_splice, 4);

    list1.splice(iter_splice, list2);
    MT::print_ctr("\nlist1 (after splice): ", list1, fmt);
    MT::print_ctr("list2 (after splice): ", list2, fmt);
}

void Ch04_02_ex3()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {4};

    // create lists
    using list_t = std::list<Point2D<double>>;
    list_t list1 { {10.0, 10.0}, {20.0, 20.0}, {30.0, 30.0}, {40.0, 40.0} };
    list_t list2 { {-1.0, -2.0}, {-3.0, -4.0}, {-5.0, -6.0}, {-7.0, -8.0} };
    list_t list3 (list1.size());

    if (list1.size() != list2.size())
        throw std::runtime_error("Ch04_02_ex3() - list size error");

    MT::print_ctr("\nlist1 (initial values): ", list1, fmt, epl_max);
    MT::print_ctr("list2 (initial values): ", list2, fmt, epl_max);
    MT::print_ctr("list3 (initial values): ", list3, fmt, epl_max);

    // using iterators
    auto iter1 = list1.cbegin();
    auto iter2 = list2.cbegin();
    auto iter3 = list3.begin();
    for (; iter1 != list1.cend(); ++iter1, ++iter2)
        *iter3++ = *iter1 + *iter2;

    MT::print_ctr("\nlist3 (after for loop): ", list3, fmt, epl_max);
}

void Ch04_02_ex4()
{
    const char* fmt = "{:14s} ";
    constexpr size_t epl_max {5};

    // using list::emplace_back and list::emplace_front
    std::list<std::string> list1 {};
    std::list<std::string> list2 {};
    list1.emplace_back("Alanine");
    list2.emplace_back("Arginine");
    list1.emplace_front("Asparagine");
    list2.emplace_front("Aspartate");
    list1.emplace_back("Cysteine");
    list2.emplace_back("Glutamine");
    list1.emplace_front("Glutamate");
    list2.emplace_front("Glycine");
    list1.emplace_back("Histidine");
    list2.emplace_back("Isoleucine");
    list1.emplace_front("Leucine");
    list2.emplace_front("Lysine");
    list1.emplace_back("Methionine");
    list2.emplace_back("Phenylalanine");
    list1.emplace_front("Proline");
    list2.emplace_front("Serine");
    list1.emplace_back("Threonine");
    list2.emplace_back("Tryptophan");
    list1.emplace_front("Tyrosine");
    list2.emplace_front("Valine");

    MT::print_ctr("\nlist1 (initial values):\n", list1, fmt, epl_max);
    MT::print_ctr("\nlist2 (initial values):\n", list2, fmt, epl_max);

    // using list::sort
    list1.sort();
    list2.sort();
    MT::print_ctr("\nlist1 (after sort):\n", list1, fmt, epl_max);
    MT::print_ctr("\nlist2 (after sort):\n", list2, fmt, epl_max);

    // using list::merge
    list1.merge(list2);
    MT::print_ctr("\nlist1 (after merge):\n", list1, fmt, epl_max);
    MT::print_ctr("\nlist2 (after merge):\n", list2, fmt, epl_max);

    // using list::reverse
    list1.reverse();
    MT::print_ctr("\nlist1 (after reverse):\n", list1, fmt, epl_max);
}

void Ch04_02_ex()
{
    std::print("\n----- Ch04_02_ex1() -----\n");
    Ch04_02_ex1();

    std::print("\n----- Ch04_02_ex2() -----\n");
    Ch04_02_ex2();

    std::print("\n----- Ch04_02_ex3() -----\n");
    Ch04_02_ex3();

    std::print("\n----- Ch04_02_ex4() -----\n");
    Ch04_02_ex4();
}
