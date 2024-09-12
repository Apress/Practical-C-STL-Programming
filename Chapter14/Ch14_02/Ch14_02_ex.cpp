//-----------------------------------------------------------------------------
// Ch14_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <ranges>
#include <string>
#include "MT.h"
#include "RN.h"

// Common arguments structure
struct Args
{
    size_t NumElem {48};            // size of data vector
    unsigned int RngSeed {1003};    // random number generator seed val
    int RngMin {1};                 // random number generator min val
    int RngMax {2000};              // random number generator max val
    size_t NumDrop {5};             // number of dropped elements
    std::string Fmt {"{:6d}"};      // print format specifier
    size_t EplMax {12};             // max elements per line

    static inline auto IsEven = [](int x) { return (x % 2) == 0; };
};

void Ch14_02_ex1(const Args& args)
{
    // create vector of random values
    std::vector<int> vec1 = RN::get_vector<int>(args.NumElem, args.RngMin,
        args.RngMax, args.RngSeed);
    MT::print_ctr("\nvec1 (initial values):\n", vec1, args.Fmt, args.EplMax);

    // using std::views_filter (filters odd values)
    auto view2 = std::views::filter(vec1, args.IsEven);
    MT::print_ctr("\nview2:\n", view2, args.Fmt, args.EplMax);

    // using std::views_drop (deletes first NumDrop elements)
    auto view3 = std::views::drop(view2, args.NumDrop);
    MT::print_ctr("\nvec3:\n", view3, args.Fmt, args.EplMax);

    // using std::views::reverse (reverses order of elements)
    auto view4 = std::views::reverse(view3);
    MT::print_ctr("\nview4 (final result):\n", view4, args.Fmt, args.EplMax);

    MT::print_ctr("\nvec1 (after views::reverse):\n", vec1, args.Fmt, args.EplMax);
}

void Ch14_02_ex2(const Args& args)
{
    std::vector<int> vec1 = RN::get_vector<int>(args.NumElem, args.RngMin,
        args.RngMax, args.RngSeed);
    MT::print_ctr("\nvec1 (initial values):\n", vec1, args.Fmt, args.EplMax);

    // Using std::views::reverse, drop, and filter (call style)
    auto view2 = std::views::reverse(std::views::drop(std::views::filter(vec1,
        args.IsEven), args.NumDrop));

    MT::print_ctr("\nview2 (final result):\n", view2, args.Fmt, args.EplMax);
}

void Ch14_02_ex3(const Args& args)
{
    std::vector<int> vec1 = RN::get_vector<int>(args.NumElem, args.RngMin,
        args.RngMax, args.RngSeed);
    MT::print_ctr("\nvec1 (initial values):\n", vec1, args.Fmt, args.EplMax);
 
    // using composition of std::views::reverse, drop, filter
    auto view2 = vec1
               | std::views::filter(args.IsEven)
               | std::views::drop(args.NumDrop)
               | std::views::reverse;

    MT::print_ctr("\nview2 (final result):\n", view2, args.Fmt, args.EplMax);
}

void Ch14_02_ex4(const Args& args)
{
    std::vector<int> vec1 = RN::get_vector<int>(args.NumElem, args.RngMin,
        args.RngMax, args.RngSeed);
    MT::print_ctr("\nvec1 (initial values):\n", vec1, args.Fmt, args.EplMax);

    // copy even values
    std::vector<int> temp1 {};
    std::ranges::copy_if(vec1, std::back_inserter(temp1), args.IsEven);

    // drop values
    std::vector<int> temp2(temp1.size() - args.NumDrop);
    std::ranges::copy(temp1.begin() + args.NumDrop, temp1.end(), temp2.begin());

    // reverse order of remaining values
    std::ranges::reverse(temp2);
    MT::print_ctr("\ntemp2: (final result)\n", temp2, args.Fmt, args.EplMax);
}

void Ch14_02_ex()
{
    Args args {};

    std::println("\n----- Ch14_02_ex1() -----");
    Ch14_02_ex1(args);

    std::println("\n----- Ch14_02_ex2() -----");
    Ch14_02_ex2(args);

    std::println("\n----- Ch14_02_ex3() -----");
    Ch14_02_ex3(args);

    std::println("\n----- Ch14_02_ex4() -----");
    Ch14_02_ex4(args);
}
