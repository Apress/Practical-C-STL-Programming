//-----------------------------------------------------------------------------
// Ch12_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include "Ch12_03.h"
#include "MT.h"
#include "MTH.h"

void Ch12_03_ex1()
{
    const char* fmt = "{:3d} ";
    constexpr size_t epl_max {20};
    constexpr size_t n {100};

    // initialize test vector of integers
    std::vector<int> vec1(n);
    std::iota(vec1.begin(), vec1.end(), 1);
    MT::print_ctr("\nvec1 (before partition):\n", vec1, fmt, epl_max);

    // using std::ranges::is_partitioned
    bool is_par = std::ranges::is_partitioned(vec1, MTH::is_prime<int>);
    std::println("is_partitioned (before partition): {:s}", is_par);

    // using std::ranges::partition (returns iterator subrange to false group)
    std::ranges::partition(vec1, MTH::is_prime<int>);
    MT::print_ctr("\nvec1 (after partition):\n", vec1, fmt, epl_max);

    is_par = std::ranges::is_partitioned(vec1, MTH::is_prime<int>);
    std::println("is_partitioned (after partition): {:s}", is_par);

    // using std::ranges::partition_point
    auto iter_pp = std::ranges::partition_point(vec1, MTH::is_prime<int>);
    std::println("\n*iter_pp: {:d}", *iter_pp);
}

void Ch12_03_ex2()
{
    // print_sr prints elements of [iter_b, iter_e)
    auto print_sr = [](const char* msg, auto iter_b, auto iter_e)
    {
        int add_nl {};
        std::println("\n{:s}", msg);

        for (auto iter = iter_b; iter != iter_e; ++iter)
        {
            std::print("{:3d} ", *iter);
            if (++add_nl % 20 == 0)
                std::println("");
        }

        std::println("");
    };

    // create test vector
    std::vector<int> vec1(100);
    std::iota(vec1.begin(), vec1.end(), 101);

    // using std::ranges::partition
    auto iter_sr = std::ranges::partition(vec1, MTH::is_prime<int>);

    print_sr("prime numbers", vec1.begin(), iter_sr.begin());
    print_sr("non-prime numbers", iter_sr.begin(), iter_sr.end());
}

void Ch12_03_ex()
{
    std::println("\n----- Ch12_03_ex1() -----");
    Ch12_03_ex1();

    std::println("\n----- Ch12_03_ex2() -----");
    Ch12_03_ex2();
}
