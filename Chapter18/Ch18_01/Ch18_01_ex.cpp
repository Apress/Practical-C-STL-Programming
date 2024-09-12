//-----------------------------------------------------------------------------
// Ch18_01_ex.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <concepts>
#include <numbers>
#include <numeric>
#include <vector>
#include "Ch18_01.h"
#include "MT.h"

void Ch18_01_ex1()
{
    // calculate Fibonacci numbers using golden ratio
    bool add_nl {false};
    std::println("\nFibonacci numbers using golden ratio");

    for (int n = 0; n < 20; ++n)
    {
        auto t1 = std::pow(std::numbers::phi, n);
        auto t2 = std::pow(-std::numbers::phi, -n);
        auto fib = (t1 - t2) / (2.0 * std::numbers::phi - 1.0);

        const char* s = (add_nl) ? "\n" : "    ";
        std::print("{:4d}  {:10.4f} {:s}", n, fib, s);
        add_nl = !add_nl;
    }
}

void Ch18_01_ex2()
{
    const char* fmt = "{:12.6f} ";
    constexpr size_t epl_max {5};
    constexpr size_t n {10};

    std::vector<float> radii_f(n);
    std::vector<double> radii_d(n);
    std::iota(radii_f.begin(), radii_f.end(), 1.0f);
    std::iota(radii_d.begin(), radii_d.end(), 1.0);

    // using std::numbers::pi_v<T>
    auto calc_area = []<typename T>(T r) requires std::floating_point<T>
        { return r * r * std::numbers::pi_v<T>; };

    // calculate circle areas (float)
    std::vector<float> areas_f {};
    for (auto r : radii_f)
        areas_f.push_back(calc_area(static_cast<float>(r)));
    MT::print_ctr("\nareas_f:\n", areas_f, fmt, epl_max);

    // calculate circle areas (double)
    std::vector<double> areas_d {};
    for (auto r : radii_d)
        areas_d.push_back(calc_area(static_cast<double>(r)));
    MT::print_ctr("\nareas_d:\n", areas_d, fmt, epl_max);
}

void Ch18_01_ex3()
{
    using namespace std::numbers;

    const char* fmt = "{:8.4f}";
    constexpr size_t epl_max {10};
    constexpr size_t n_f {81};
    constexpr size_t n_d {125};
    
    std::vector<float> vec0_f(n_f);
    std::vector<double> vec0_d(n_d);
    std::iota(vec0_f.begin(), vec0_f.end(), 1.0f);
    std::iota(vec0_d.begin(), vec0_d.end(), 1.0);

    // calculate log base b of x
    auto log_b_x = []<typename T>(T b, T x) requires std::floating_point<T>
        { return std::log(x) * log10e_v<T> / std::log10(b); };

    // calculate log3 values (float)
    std::println("\nlog3 values of [{:d}, {:d}]: ", 1, n_f);
    std::vector<float> vec_f {};
    for (auto x : vec0_f)
        vec_f.push_back(log_b_x(3.0f, static_cast<float>(x)));
    MT::print_ctr("", vec_f, fmt, epl_max);

    // calculate log5 values (double)
    std::println("\nlog5 values of [{:d}, {:d}]: ", 1, n_d);
    std::vector<double> vec_d {};
    for (auto x : vec0_d)
        vec_d.push_back(log_b_x(5.0, static_cast<double>(x)));
    MT::print_ctr("", vec_d, fmt, epl_max);
}

void Ch18_01_ex()
{
    std::println("\n----- Ch18_01_ex1() -----");
    Ch18_01_ex1();

    std::println("\n----- Ch18_01_ex2() -----");
    Ch18_01_ex2();

    std::println("\n----- Ch18_01_ex3() -----");
    Ch18_01_ex3();
}
