//-----------------------------------------------------------------------------
// Ch20_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <execution>
#include <mutex>
#include <vector>
#include "Ch20_02.h"

namespace ex = std::execution;

void Ch20_02_ex1()
{
    // create test vectors
    constexpr size_t n {10'000'000};
    std::vector<long long> vec0(n);
    std::iota(vec0.begin(), vec0.end(), 0);
    std::vector<long long> vec1 {};
    std::vector<long long> vec2 {};
    std::vector<long long> vec3 {};

    // using std::for_each with ex::seq
    auto fe_op1 = [&vec1](long long x) { vec1.push_back(x + x); };

    std::for_each(ex::seq, vec0.begin(), vec0.end(), fe_op1);
    auto sum1 = std::accumulate(vec1.begin(), vec1.end(), 0LL);
    std::println("after std::for_each(ex::seq) - sum1: {:d}", sum1);

    // using std::for_each with ex::par and std::mutex
    std::mutex mtx2 {};

    auto fe_op2 = [&vec2, &mtx2](long long x)
    {
        mtx2.lock();
        vec2.push_back(x + x);
        mtx2.unlock();
    };

    std::for_each(ex::par, vec0.begin(), vec0.end(), fe_op2);
    auto sum2 = std::accumulate(vec2.begin(), vec2.end(), 0LL);
    std::println("after std::for_each(ex::par) - sum2: {:d}", sum2);

    // using std::for_each with ex::par, std::lock_guard, and std::mutex
    std::mutex mtx3 {};

    auto fe_op3 = [&vec3, &mtx3](long long x)
    {
        std::lock_guard<std::mutex> lg3(mtx3);
        vec3.push_back(x + x);
    };

    std::for_each(ex::par, vec0.begin(), vec0.end(), fe_op3);
    auto sum3 = std::accumulate(vec3.begin(), vec3.end(), 0LL);
    std::println("after std::for_each(ex::par) - sum3: {:d}", sum3);

    // verify sums
    std::println("\nsum1 == sum2: {:s} (expect true)", sum1 == sum2);
    std::println("sum2 == sum3: {:s} (expect true)", sum2 == sum3);

    // print location of first vec1/vec2 element mismatch (if any)
    auto mm_pair = std::mismatch(vec1.begin(), vec1.end(), vec2.begin());
    auto mm_pos = std::distance(vec1.begin(), mm_pair.first);

    if (mm_pos == n)
        std::println("\nvec1 and vec2 are identical");
    else
    {
        std::println("\nvec1 and vec2 are different");
        std::println("  vec1[{:d}]: {:d}", mm_pos, vec1[mm_pos]);
        std::println("  vec2[{:d}]: {:d}", mm_pos, vec2[mm_pos]);
    }
}

void Ch20_02_ex()
{
    std::println("\n----- Ch20_02_ex1() -----");
    Ch20_02_ex1();
}
