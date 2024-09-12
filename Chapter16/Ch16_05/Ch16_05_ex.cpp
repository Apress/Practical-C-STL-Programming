//-----------------------------------------------------------------------------
// Ch16_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include "Ch16_05.h"
#include "BmTimer.h"
#include "RN.h"

void Ch16_05_ex1()
{
    constexpr int rng_min {1};
    constexpr int rng_max {2000};
    constexpr size_t vec_size {10'000'000};

    // create test vectors
    auto vec0 = RN::get_vector<float>(vec_size, rng_min, rng_max);
    auto vec1 = RN::get_vector<double>(vec_size, rng_min, rng_max);

    // create test transformation lambdas (std::cbrt(x) is cube root of x)
    auto tr_f32 = [](float x) { return x + std::cbrt(x); };
    auto tr_f64 = [](double x) { return x + std::cbrt(x); };

    // create BmTimer using steady clock
    constexpr size_t num_iter {40};
    constexpr size_t num_alg {2};
    BmTimerSteadyClk bm_timer(num_iter, num_alg);

    std::print("example Ch16_05_ex1 is running, please wait ");

    // execute test algorithms
    for (size_t i {0}; i < num_iter; ++i)
    {
        bm_timer.start(i, 0);
        std::ranges::transform(vec0, vec0.begin(), tr_f32);
        bm_timer.stop(i, 0);

        if (i % 4 == 0)
            std::cout << '.' << std::flush;
    }

    for (size_t i {0}; i < num_iter; ++i)
    {
        bm_timer.start(i, 1);
        std::ranges::transform(vec1, vec1.begin(), tr_f64);
        bm_timer.stop(i, 1);

        if (i % 4 == 0)
            std::cout << '.' << std::flush;
    }

    // save results to CSV file
    std::println("");
    std::string fn {"Ch16_05_ex1_results.csv"};
    bm_timer.save_to_csv(fn, "{:.2f}", BmTimerSteadyClk::EtUnit::MilliSec);
    std::println("Benchmark times save to file {:s}", fn);
}

void Ch16_05_ex()
{
    std::println("\n----- Ch16_05_ex1() -----");
    Ch16_05_ex1();
}
