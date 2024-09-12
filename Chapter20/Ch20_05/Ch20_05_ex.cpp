//-----------------------------------------------------------------------------
// Ch20_05_ex.cpp
//-----------------------------------------------------------------------------

#include <iostream>
#include <valarray>
#include "Ch20_05.h"
#include "BmTimer.h"
#include "ConvData.h"

using fp_t = float;

ConvData<fp_t> init_conv_data(fp_t end_time, std::valarray<fp_t>& kernel)
{
    constexpr size_t num_rs {3};
    ConvData<fp_t> cd(num_rs);

    // generate test signal
    cd.StartTime = fp_t {0.0};
    cd.EndTime = end_time;
    cd.StepTime = fp_t {1.0 / 256.0};

    cd.Amplitudes  = std::valarray {fp_t{1.0}, fp_t{0.8},  fp_t{1.20}};
    cd.Frequencies = std::valarray {fp_t{5.0}, fp_t{9.0},  fp_t{14.0}};
    cd.PhaseAngles = std::valarray {fp_t{0.0}, fp_t{60.0}, fp_t{90.0}};

    cd.generate_signal_x(true);
    std::println("SignalX.size(): {:d}", cd.SignalX.size());

    // generate convolution kernel
    kernel = std::valarray<fp_t>
        { 1.0 / 64.0, 6.0 / 64.0, 15.0 / 64.0,
          20.0 / 64.0,
          15.0 / 64.0, 6.0 / 64.0, 1.0 / 64.0 };

    return cd;
}

void Ch20_05_ex1()
{
    // initialize convolution data struct
    std::valarray<fp_t> kernel {};
    ConvData<fp_t> cd = init_conv_data(1.0, kernel);

    // perform convolution using 1 thread
    ConvData<fp_t>::convolve(cd, kernel, 1);
    cd.save_data("ch20_05_ex1_cd_data-a.csv");

    // perform convolution using 3 threads
    ConvData<fp_t>::convolve(cd, kernel, 3);
    cd.save_data("ch20_05_ex1_cd_data-b.csv");

    // perform convolution using 7 threads
    ConvData<fp_t>::convolve(cd, kernel, 7);
    cd.save_data("ch20_05_ex1_cd_data-c.csv");
}

void Ch20_05_ex2()
{
    std::println("example Ch20_05_ex2() is running, please wait ");

    // initialize convolution data struct
    std::valarray<fp_t> kernel {};
    ConvData<fp_t> cd = init_conv_data(250'000.0, kernel);

    // initailize BmTimer using steady clock
    constexpr size_t num_iter {40};
    constexpr size_t num_threads_max {8};
    BmTimerSteadyClk bm_timer(num_iter, num_threads_max);

    // run test convolutions
    for (size_t i = 0; i < num_iter; ++i)
    {
        for (size_t j = 0; j < num_threads_max; ++j)
        {
            bm_timer.start(i, j);
            ConvData<fp_t>::convolve(cd, kernel, j + 1);
            bm_timer.stop(i, j);
        }

        std::cout << '.' << std::flush;
    }

    // save measurements to CSV file
    std::println("");
    std::string fn {"Ch20_05_ex2-results.csv"};
    bm_timer.save_to_csv(fn, "{:.2f}", BmTimerSteadyClk::EtUnit::MilliSec);
    std::println("Benchmark times save to file {:s}", fn);
}

void Ch20_05_ex()
{
    std::println("\n----- Ch20_05_ex1() -----");
    Ch20_05_ex1();

    std::println("\n----- Ch20_05_ex2() -----");
    Ch20_05_ex2();
}
