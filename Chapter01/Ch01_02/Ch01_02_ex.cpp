//-----------------------------------------------------------------------------
// Ch01_02_ex.cpp
//-----------------------------------------------------------------------------

#include <typeinfo>
#include <vector>
#include "Ch01_02.h"

void Ch01_02_ex1()
{
    std::vector<int> x_vals {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // access element using operator[]
    for (std::size_t i = 0; i < x_vals.size(); ++i)
        std::print("{} ", x_vals[i]);
    std::println("");

    // access elements using at()
    for (std::size_t i = 0; i < x_vals.size(); ++i)
        std::print("{} ", x_vals.at(i));
    std::println("");

//  x_vals[42] = -1         // error, no exception, trouble
//  x_vals.at(42) = -1;     // error, throws exception
}

void Ch01_02_ex2()
{
    std::vector<long long> y_vals {10, 20, 30, 40, 50,
        60, 70, 80, 90, 100};

    // print elements of y_vals using iterators
    for (auto iter = y_vals.begin(); iter != y_vals.end(); ++iter)
        std::print("{} ", *iter);
    std::println("");

    // print iterator type
    std::println("\nvector<long long> iterator type:\n{}\n",
        typeid(y_vals.begin()).name());

    // print elements of y_vals in reverse order
    for (auto iter = y_vals.rbegin(); iter != y_vals.rend(); ++iter)
        std::print("{} ", *iter);
    std::println("\n");

    // using std::begin() and std::end()
    for (auto iter = std::begin(y_vals); iter != std::end(y_vals); ++iter)
    {
        *iter *= 5;
        std::print("{} ", *iter);
    }
    std::println("");
}

void Ch01_02_ex3()
{
    std::vector<std::string> s_vals
        {"adenine", "cytosine", "guanine", "thymine", "uracil"};

    // display s_vals - in order, const iterator
    for (auto iter = s_vals.cbegin(); iter != s_vals.cend(); ++iter)
        std::print("{} ", *iter);
    std::println("");

    // display s_vals, reverse order, const iterator
    for (auto iter = s_vals.crbegin(); iter != s_vals.crend(); ++iter)
        std::print("{} ", *iter);
    std::println("");
}

void Ch01_02_ex()
{
    std::println("\n---- Ch01_02_ex1() -----");
    Ch01_02_ex1();

    std::println("\n---- Ch01_02_ex2() -----");
    Ch01_02_ex2();

    std::println("\n---- Ch01_02_ex3() -----");
    Ch01_02_ex3();
}
