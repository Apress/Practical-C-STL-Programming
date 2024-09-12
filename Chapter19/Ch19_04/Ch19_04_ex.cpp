//-----------------------------------------------------------------------------
// Ch19_04_ex.cpp
//-----------------------------------------------------------------------------

#include <iostream>
#include <valarray>
#include "Ch19_04.h"
#include "BmTimer.h"
#include "CovData.h"

void Ch19_04_ex1()
{
    using fp_t = double;
    constexpr size_t num_vars {8};
    constexpr size_t num_obvs {100};
    constexpr fp_t rng_min {0.0};
    constexpr fp_t rng_max {25.0};
    constexpr unsigned int rng_seed {1111};

    // create CovData object
    CovData<fp_t> cov_data(num_vars, num_obvs);
    cov_data.generate_data(rng_min, rng_max, rng_seed);

    // calculate covariance matrix
    cov_data.covariance();
    cov_data.save_results("Ch19_04_ex1-results.txt", "{:9.4f}");
}

void Ch19_04_ex2()
{
    using fp_t = float;
    constexpr size_t num_vars {8};
    constexpr size_t num_obvs {1'000'000};
    constexpr fp_t rng_min {0.0};
    constexpr fp_t rng_max {25.0};
    constexpr unsigned int rng_seed {1111};

    // create CovData objects
    CovData<fp_t> cov_data1(num_vars, num_obvs);
    cov_data1.generate_data(rng_min, rng_max, rng_seed);

    CovData<fp_t> cov_data2(num_vars, num_obvs);
    cov_data2.generate_data(rng_min, rng_max, rng_seed);

    // create BmTimer using steady clock
    constexpr size_t num_iter {50};
    constexpr size_t num_alg {2};
    BmTimerSteadyClk bm_timer(num_iter, num_alg);

    std::print("example Ch19_04_ex2 is running, please wait ");

    // execute test algorithms
    for (size_t i = 0; i < num_iter; ++i)
    {
        bm_timer.start(i, 0);
        cov_data1.covariance();         // uses slices
        bm_timer.stop(i, 0);

        if (i % 5 == 0)
            std::cout << '.' << std::flush;
    }

    for (size_t i = 0; i < num_iter; ++i)
    {
        bm_timer.start(i, 1);
        cov_data2.covariance_indx();    // uses integer indices
        bm_timer.stop(i, 1);

        if (i % 5 == 0)
            std::cout << '.' << std::flush;
    }

    // save measurements to CSV file
    std::println("");
    std::string fn {"Ch19_04_ex2-results.csv"};
    bm_timer.save_to_csv(fn, "{:.2f}", BmTimerSteadyClk::EtUnit::MilliSec);
    std::println("Benchmark times save to file {:s}", fn);
}

void Ch19_04_ex()
{
    std::println("\n----- Ch19_04_ex1() -----");
    Ch19_04_ex1();

    std::println("\n----- Ch19_04_ex2() -----");
    Ch19_04_ex2();
}
