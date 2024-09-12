//-----------------------------------------------------------------------------
// Ch19_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <numeric>
#include <string>
#include <valarray>
#include <vector>
#include "Ch19_05.h"
#include "MT.h"
#include "RN.h"

void Ch19_05_ex1()
{
    const char* fmt = "{:7.1f}";
    constexpr size_t epl_max {10};

    constexpr size_t n {10};
    constexpr int rng_min {1};
    constexpr int rng_max {50};
    constexpr unsigned int rng_seed {3400};

    // create test valarrays
    auto va1 = RN::get_valarray<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nva1:\n", va1, fmt, epl_max);

    auto va2 = RN::get_valarray<double>(n, rng_min, rng_max, rng_seed + 1);
    MT::print_ctr("\nva2:\n", va2, fmt, epl_max);

    // using std::inner_product
    double ip_va1_va2 = std::inner_product(std::begin(va1), std::end(va1),
        std::begin(va2), 0.0);

    std::println("\nip_va1_va2: {:7.1f}", ip_va1_va2); 
}

void Ch19_05_ex2()
{
    // create test vectors
    std::vector<std::string> vec1 {"A", "B", "C", "D", "E"};
    std::vector<std::string> vec2 {"a", "b", "c", "d", "e"};

    // binary operators for std::inner_product
    auto ip_op1 = [](const std::string& s1, const std::string& s2)
        { return s1 + " + " + s2; };

    auto ip_op2 = [](const std::string& s1, const std::string& s2)
        { return s1 + " * " + s2; };

    // operation performed below by std::inner_product:
    //
    //  acc = "#"; iter1 = vec1.begin(); iter2 = vec2.begin()
    //  while (iter1 != vec1.end())
    //  {
    //      acc = ip_op1(acc, ip_op2(*iter1, *iter2))
    //      ++iter1; ++iter2
    //  {

    std::string ip_vec1_vec2 = std::inner_product(vec1.begin(), vec1.end(),
        vec2.begin(), std::string("#"), ip_op1, ip_op2);

    std::println("\nip_vec1_vec2: {:s}", ip_vec1_vec2);
}

void Ch19_05_ex3()
{
    const char* fmt = "{:7.1f}";
    constexpr size_t epl_max {10};

    constexpr size_t n {20};
    constexpr int rng_min {1};
    constexpr int rng_max {50};
    constexpr unsigned int rng_seed {3400};

    auto vec1 = RN::get_vector<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::reduce (initial value = 0)
    double reduce1 = std::reduce(vec1.begin(), vec1.end());
    std::println("\nreduce1: {:7.1f}", reduce1);

    // using std::reduce (initial value = 1000.0)
    double reduce2 = std::reduce(vec1.begin(), vec1.end(), 1000.0);
    std::println("\nreduce2: {:7.1f}", reduce2);

    // using std::reduce (initial value = 1000.0, custom binary_op)
    std::println("");
    auto reduce_op = [](double sum, double x)
    {
        std::println("{:8.4f} {:8.4f} {:8.4f}", sum, x, sqrt(x));
        return sum + std::sqrt(x);
    };

    double reduce3 = std::reduce(vec1.begin(), vec1.end(), 0.0, reduce_op);
    std::println("\nreduce3: {:8.4f}", reduce3);
}

#define ENABLE_PRINT

void Ch19_05_ex4()
{
    const char* fmt = "{:5d}";
    constexpr size_t epl_max {10};
    constexpr size_t n {8};

    // create test vectors
    std::vector<int> vec1(n);
    std::ranges::iota(vec1, 1);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    std::vector<int> vec2(n);
    std::ranges::iota(vec2, 10);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);

    // using std::transform_reduce
    // uses default std::plus (reduce_op) and std::multiplies (transform_op)
    int tr1 = std::transform_reduce(vec1.begin(), vec1.end(), vec2.begin(), 0);
    std::println("\ntr1: {:d}\n", tr1);

    // using std::transform_reduce
    // calculates reduce_op2(transform_op2(vec1[i])) for all i
    auto reduce_op2 = [](int sum, int x)
    {
#ifdef ENABLE_PRINT
        std::println("reduce_op2: [sum: {:5d}, x: {:5d}]", sum, x);
#endif
        return sum + x;
    };

    auto transform_op2 = [](int x)
        { return x * x; };

    int tr2 = std::transform_reduce(vec1.begin(), vec1.end(), 0,
        reduce_op2, transform_op2);
    std::println("\ntr2: {:d}\n", tr2);

    // using std::transform_reduce
    // calculates reduce_op3(transform_op3(vec1[i], vec2[i])) for all i
    auto reduce_op3 = [](int sum, int z)
    {
#ifdef ENABLE_PRINT
        std::println("reduce_op3:    [sum: {:5d}, z: {:5d}]", sum, z);
#endif
        return sum + z;
    };

    auto transform_op3 = [](int x, int y)
    {
#ifdef ENABLE_PRINT
        std::println("transform_op3: [x:   {:5d}, y: {:5d}]", x, y);
#endif
        return 2 * x + 2 * y;
    };

    int tr3 = std::transform_reduce(vec1.begin(), vec1.end(), vec2.begin(), 0,
        reduce_op3, transform_op3);
    std::println("\ntr3: {:d}\n", tr3);
}

void Ch19_05_ex()
{
    std::println("\n----- Ch19_05_ex1() -----");
    Ch19_05_ex1();

    std::println("\n----- Ch19_05_ex2() -----");
    Ch19_05_ex2();

    std::println("\n----- Ch19_05_ex3() -----");
    Ch19_05_ex3();

    std::println("\n----- Ch19_05_ex4() -----");
    Ch19_05_ex4();
}
