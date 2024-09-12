//-----------------------------------------------------------------------------
// Ch11_08_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include "Ch11_08.h"
#include "MF.h"
#include "MT.h"
#include "RN.h"

void Ch11_08_ex1()
{
    const char* fmt = "{:7.1f} ";
    constexpr size_t epl_max {10};

    // create vector of random values
    constexpr size_t n {20};
    constexpr int rng_min {1};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {5};
    std::vector vec1 {RN::get_vector<double>(n, rng_min, rng_max, rng_seed)};
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::accumulate
    double sum1 = std::accumulate(vec1.begin(), vec1.end(), 0.0);
    double sum2 = std::accumulate(vec1.begin(), vec1.end(), 1'000'000'000.0);
    std::println("\nsum1: {:7.1f}  sum2: {:7.1f}", sum1, sum2);

    // using std::accumulate with binary operator
    auto acc_op = [](double x, double y) { return x - y; };
    double acc1 = std::accumulate(vec1.begin(), vec1.end(), 0.0, acc_op);
    std::println("\nacc1: {:7.1f}", acc1);
}

void Ch11_08_ex2()
{
#ifdef __cpp_lib_ranges_fold
    const char* fmt = "{:7.1f} ";
    constexpr size_t epl_max {10};

    // create vector of random values
    std::vector<double> vec1 {10.0, 20.0, 30.0, 40.0, 50.0};
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::ranges::fold_left, std::ranges::fold_right (associative op)
    auto left1 = std::ranges::fold_left(vec1, 0.0, std::plus<double>());
    auto right1 = std::ranges::fold_right(vec1, 0.0, std::plus<double>());
    std::println("\nleft1: {:7.1f}  right1: {:7.1f}", left1, right1);

    // using std::ranges::fold_left, std::ranges::fold_right (non-associative op)
    auto left2 = std::ranges::fold_left(vec1, 0.0, std::minus<double>());
    auto right2 = std::ranges::fold_right(vec1, 0.0, std::minus<double>());
    std::println("\nleft2: {:7.1f}  right2: {:7.1f}", left2, right2);

    // using std::ranges::fold_left_first, std::ranges::fold_right_last (assoc)
    // left3, right3 are std::optional<double>
    auto left3 = std::ranges::fold_left_first(vec1, std::plus<double>());
    auto right3 = std::ranges::fold_right_last(vec1, std::plus<double>());
    std::println("\nleft3: {:7.1f}  right3: {:7.1f}", left3.value(), right3.value());

    // using std::ranges::fold_left_first, std::ranges::fold_right_last (non-assoc)
    // left4, right4 are std::optional<double>
    auto left4 = std::ranges::fold_left_first(vec1, std::minus<double>());
    auto right4 = std::ranges::fold_right_last(vec1, std::minus<double>());
    std::println("\nleft4: {:7.1f}  right4: {:7.1f}", left4.value(), right4.value());

    // using std::ranges::fold_left_first, empty container
    std::vector<double> vec2 {};
    auto left5 = std::ranges::fold_left_first(vec2, std::plus<double>());

    if (left5)
        std::println("\nleft5: {:7.1f}", left5.value());
    else
        std::println("\nleft5: empty container");
#else
    std::println("Ch11_08_ex2() requires __cpp_lib_ranges_fold (C++23)");
#endif
}

void Ch11_08_ex3()
{
#ifdef __cpp_lib_ranges_fold
    const char* fmt = "{:8s} ";
    constexpr size_t epl_max {10};

    // create test vector
    std::vector<std::string> vec1
        {"zero", "one", "two", "three", "four", "five", "six", "seven"};
    MT::print_ctr("\nvec1: ", vec1, fmt, epl_max);

    // define binary operators for left and right folds
    auto fold_op_left = [](const std::string& s1, const std::string& s2)
    {
        std::println("s1: {:35s} s2: {:35s}", s1, s2);
        auto s2_temp {s2};
        return s1 + " " + MF::to_upper(s2_temp);
    };

    auto fold_op_right = [](const std::string& s1, const std::string& s2)
    {
        std::println("s1: {:35s} s2: {:35s}", s1, s2);
        auto s1_temp {s1};
        return MF::to_upper(s1_temp) + " " + s2;
    };

    // using std::ranges::fold_left_first
    std::println("\nexecuting std::ranges::fold_left_first()");
    auto left1 = std::ranges::fold_left_first(vec1, fold_op_left);
    std::println("\nleft1:  {:s}", left1.value());

    // using std::ranges::fold_left_right
    std::println("\nexecuting std::ranges::fold_right_last()");
    auto right1 = std::ranges::fold_right_last(vec1, fold_op_right);
    std::println("\nright1: {:s}", right1.value());
#else
    std::println("Ch11_08_ex3() requires __cpp_lib_ranges_fold (C++23)");
#endif
}

void Ch11_08_ex()
{
    std::println("\n----- Ch11_08_ex1() -----");
    Ch11_08_ex1();

    std::println("\n----- Ch11_08_ex2() -----");
    Ch11_08_ex2();

    std::println("\n----- Ch11_08_ex3() -----");
    Ch11_08_ex3();
}
