//-----------------------------------------------------------------------------
// Ch15_05_ex.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <numbers>
#include <utility>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include "Ch15_05.h"

void Ch15_05_ex1()
{
    // create vector of test bound values
    std::vector<int> n_vals { 100, 1'000, 1'000'000, 1'000'000'000 };

    // compile using /O2 or /O3 for best performance
    // iota_vw is type std::ranges::iota_view
    auto calc_pi = [](auto iota_vw)
    {
        double sum {};

        for (auto i : iota_vw)
        {
            auto num = std::pow(-1, i + 1);
            auto den = 2 * i - 1;
            sum += num / den;
        }

        return 4.0 * sum;
    };

    std::println("\nbegin test of std::views::iota, please wait");
    std::println("\npi (std::numbers::pi): {:.14f}", std::numbers::pi);

    for (auto n : n_vals)
    {
        std::println("\ncalculating pi, n: {:d}", n);

        // using std::views::iota - generates view of [1, n + 1)
        auto pi = calc_pi(std::views::iota(1, n + 1));
        auto delta = fabs(pi - std::numbers::pi);

        std::println("pi (calculated):       {:.14f}", pi);
        std::println("delta:                 {:e}", delta);
    }
}

void Ch15_05_ex2()
{
    constexpr size_t n {10};

    // using std::views::repeat (bounded view)
    for (auto v : std::views::repeat(42.0, n))
        std::print("{:6.1f} ", v);
    std::println("");

    // using std::views::repeat (unbounded view)
    std::string s {" hello"};
    for (auto v : std::views::repeat(s) | std::views::take(n))
        std::print("{:s} ", v);
    std::println("");
}

void Ch15_05_ex3()
{
    using pair_t = std::pair<int, std::string>;

    // create test vector
    std::vector<pair_t> vec1
    {
        pair_t(0, "1 2 3 4 5 6 7 8"),
        pair_t(1, "1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0"),
        pair_t(2, "one two three four five six seven eight"),

        pair_t(0, "1 2 3 4 a 5 6 7 8"),                     // invalid int value
        pair_t(1, "1.0 2.0 3.0 4.0 b 5.0 6.0 7.0 8.0"),     // invalid FP value
    };

    for (const auto& v : vec1)
    {
        auto iss = std::istringstream(v.second);

        if (v.first == 0)
        {
            // using std::views::istream<int>
            int result0 {};
            auto iss_view = std::views::istream<int>(iss);

            for (auto val : iss_view)
                result0 += val;
            std::println("result0: {:d}", result0);

        }
        else if (v.first == 1)
        {
            // using std::views::istream<double>
            double result1 {1.0};
            auto iss_view = std::views::istream<double>(iss);

            for (auto val : iss_view)
                result1 *= val;
            std::println("result1: {:.1f}", result1);
        }
        else if (v.first == 2)
        {
            // using std::views::istream<std::string>
            std::string result2 {"|"};
            auto iss_view = std::views::istream<std::string>(iss);

            for (auto val : iss_view)
                result2 += val + "|";
            std::println("result2: {:s}", result2);
        }
    }
}

void Ch15_05_ex()
{
    std::println("\n----- Ch15_05_ex1() -----");
    Ch15_05_ex1();

    std::println("\n----- Ch15_05_ex2() -----");
    Ch15_05_ex2();

    std::println("\n----- Ch15_05_ex3() -----");
    Ch15_05_ex3();
}
