//-----------------------------------------------------------------------------
// Ch01_06_ex.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <functional>
#include <vector>
#include "Ch01_06.h"

namespace
{
    std::vector<int> s_ValuesInt
    {
         1,  4,  7,  9, 12, 13, 15, 22, 27, 33, 38, 44,
        51, 58, 63, 68, 71, 77, 82, 87, 93, 95, 98, 99
    };

    std::vector<double> s_ValuesDouble
    {
        10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0
    };
}

void Ch01_06_ex1()
{
    std::vector<int> vec1 {s_ValuesInt};

    // lambda expression
    auto is_even = [](int x) { return (x % 2) == 0; };

    // using is_even
    int sum_even {};
    for (int x : vec1)
    {
        if (is_even(x))
            sum_even += x;
    }

    std::println("sum_even: {}", sum_even);
}

int sum_if(const std::vector<int>& vec, const std::function<bool(int)>& predicate)
{
    int sum {};
    for (int x : vec)
    {
        if (predicate(x))
            sum += x;
    }

    return sum;
}

void Ch01_06_ex2()
{
    std::vector<int> vec1 {s_ValuesInt};

    // passing a lambda expression to another function
    auto is_even = [](int x) { return (x % 2) == 0; };
    int sum_even = sum_if(vec1, is_even);

    auto is_odd = [](int x) { return (x % 2) != 0; };
    int sum_odd = sum_if(vec1, is_odd);

    std::println("sum_even: {}, sum_odd: {}", sum_even, sum_odd);
}

void Ch01_06_ex3()
{
    double cap_val {2.0};
    std::vector<double> vec1 {s_ValuesDouble};

    // using a captured (by value) variable
    auto calc1 = [cap_val] (double x) { return std::sqrt(x) + cap_val; };

    for (double x : vec1)
    {
        double y = calc1(x);
        std::println("x: {:.2f}, y: {:.4f}", x, y);
    }
}

void Ch01_06_ex4()
{
    double cap_val {1.0};
    std::vector<double> vec1 {s_ValuesDouble};

    // using a captured (by reference) variable
    auto calc1 = [&cap_val] (double x) -> double
        { double y = std::sqrt(x + cap_val); cap_val *= 2.0; return y; };

    std::println("cap_val (before range for loop): {:.2f}", cap_val);

    for (double x : vec1)
    {
        double y = calc1(x);
        std::println("x: {:.2f}, y: {:.4f}", x, y);
    }

    std::println("cap_val (after range for loop): {:.2f}", cap_val);
}

void Ch01_06_ex5()
{
    std::vector<double> vec1 {s_ValuesDouble};

    // using a local captured variable (requires mutable)
    auto calc1 = [local_val = 1.0] (double x) mutable -> double
        { double y = std::sqrt(x + local_val); local_val *= 2.0; return y; };

    for (double x : vec1)
    {
        double y = calc1(x);
        std::println("x: {:.2f}, y: {:.4f}", x, y);
    }
}

void Ch01_06_ex()
{
    std::println("\n---- Ch01_06_ex1() -----");
    Ch01_06_ex1();

    std::println("\n---- Ch01_06_ex2() -----");
    Ch01_06_ex2();

    std::println("\n---- Ch01_06_ex3() -----");
    Ch01_06_ex3();

    std::println("\n---- Ch01_06_ex4() -----");
    Ch01_06_ex4();

    std::println("\n---- Ch01_06_ex5() -----");
    Ch01_06_ex5();
}
