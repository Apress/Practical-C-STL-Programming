//-----------------------------------------------------------------------------
// Ch07_02_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <functional>
#include <set>
#include <string>
#include "Ch07_02.h"
#include "MT.h"

void Ch07_02_ex1()
{
    const char* fmt = "{:6d}";
    constexpr size_t epl_max {10};

    // create multiset of integers
    std::multiset<int> mset1 {20, 40, 100, 50, 90, 70, 10, 80, 30};
    MT::print_ctr("\nmset1 (initial values):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());

    // add more elements to mset1 using insert
    mset1.insert(110);
    mset1.insert(90);
    mset1.insert(80);
    mset1.insert(60);
    MT::print_ctr("\nmset1 (after insertions):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());

    // add more elements to mset1 using insert_range (C++23)
#ifdef __cpp_lib_containers_ranges
    std::array<int, 5> vals1 {70, 80, 40, 80, 30};

    mset1.insert_range(vals1);
    MT::print_ctr("\nmset1 (after insert_range):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());
#else
    std::println("\nstd::multiset::insert_range() requires C++23");
#endif

    // count occurences of count_val in mset1
    int count_val {80};
    auto n = mset1.count(count_val);
    std::println("\nmset1.count({:d}) = {:d}", count_val, n);
}

void Ch07_02_ex2()
{
    const char* fmt = "{:12s}";
    constexpr size_t epl_max {5};

    // set of strings (sorted using operator>)
    std::multiset<std::string, std::greater<std::string>> mset1
        {"Pittsburg", "Atlanta", "Charlotte", "Denver", "Seattle", "Miami",
         "Atlanta", "Dallas", "Denver", "Boise"};

    MT::print_ctr("\nmset1 (initial values):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());

    // add new elements using emplace
    mset1.emplace("Portland");
    mset1.emplace("Atlanta");
    mset1.emplace("Cleveland");
    mset1.emplace("Detroit");
    MT::print_ctr("\nmset1 (after emplacements):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());

    // erase element using value
    mset1.erase("Atlanta");
    MT::print_ctr("\nmset1 (after first erase):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());

    // erase all cities that begin with a 'D'
    auto iter = mset1.begin();

    while (iter != mset1.end())
    {
        // *iter is type std::string
        if ((*iter)[0] == 'D')
            iter = mset1.erase(iter);
        else
            ++iter;
    }

    MT::print_ctr("\nmset1 (after erase loop):\n", mset1, fmt, epl_max);
    std::println("mset1.size(): {:d}", mset1.size());
}

void Ch07_02_ex()
{
    std::println("\n----- Ch07_02_ex1() -----");
    Ch07_02_ex1();

    std::println("\n----- Ch07_02_ex2() -----");
    Ch07_02_ex2();
}
