//-----------------------------------------------------------------------------
// ConvData.h
//-----------------------------------------------------------------------------

#ifndef CONV_DATA_H_
#define CONV_DATA_H_

#include <algorithm>
#include <fstream>
#include <random>
#include <stdexcept>
#include <thread>
#include <valarray>
#include <vector>
#include "Common.h"
#include "MTH.h"

template <typename T = double> requires std::floating_point<T>
struct ConvData
{
    constexpr static unsigned int s_RngSeed {88};

    ConvData() = delete;
    explicit ConvData(size_t num_rs) : NumRs {num_rs} {RawSignals.resize(NumRs);}

    void generate_signal_x(bool add_noise=false, unsigned int rng_seed=s_RngSeed)
    {
        // make sure signal generation parameter array sizes are valid
        if (Amplitudes.size() != NumRs || Frequencies.size() != NumRs ||
            PhaseAngles.size() != NumRs)
        {
            throw std::runtime_error("generate_signal_x - size error");
        }

        // initialize RNG for additive noise
        std::mt19937_64 rng {};
        std::uniform_real_distribution<T> rng_dist { T {-0.30}, T {0.30} };

        if (add_noise)
        {
            if (rng_seed == 0)
            {
                std::random_device rd {};
                rng.seed(rd());
            }
            else
                rng.seed(rng_seed);
        }

        // generate SignalX
        for (size_t i = 0; i < NumRs; ++i)
        {
            RawSignals[i] = MTH::generate_sine_wave<T, std::valarray<T>>
            (Amplitudes[i], Frequencies[i], PhaseAngles[i],
             StartTime, EndTime, StepTime);

            if (add_noise)
            {
                for (size_t j = 0; j < RawSignals[i].size(); ++j)
                {
                    T noise = rng_dist(rng);
                    RawSignals[i][j] += RawSignals[i][j] * noise;
                }
            }

            if (i == 0)
                SignalX = RawSignals[i];
            else
                SignalX += RawSignals[i];
        }

        SignalY.resize(SignalX.size());
    }

    static void convolve(
        ConvData<T>& cd, const std::valarray<T>& kernel, size_t num_threads = 1)
    {
        size_t ss = cd.SignalX.size();
        size_t ks = kernel.size();
        size_t ks2 = ks / 2;

        if (ks < 3 || (ks & 1) == 0 || ss < ks)
            throw std::runtime_error("convolve_par - invalid kernel size");

        if (num_threads == 0)
            throw std::runtime_error("convolve_par - invalid num_threads");

        if (num_threads == 1)
        {
            // perform convolution on current thread
            convolve_thread(cd, kernel, ks2, ss - ks2);
            return;
        }

        // calc npts_per_thread, npts_adj (residual points added to first thread)
        size_t npts = ss - 2 * ks2;
        size_t npts_per_thread = npts / num_threads;
        size_t npts_adj = npts - npts_per_thread * num_threads;

        // launch convolution threads
        size_t ib = ks2;
        size_t ie = ib + npts_per_thread + npts_adj;
        std::vector<std::jthread> thread_pool(num_threads);

        for (size_t i = 0; i < num_threads; ++i)
        {
            thread_pool[i] = std::jthread(convolve_thread, std::ref(cd),
                std::cref(kernel), ib, ie);

            ib = ie;
            ie += npts_per_thread;
        }
    }

    static void convolve_thread(
        ConvData<T>& cd, const std::valarray<T>& kernel, size_t ib, size_t ie)
    {
        try
        {
            size_t ks = kernel.size();
            size_t ks2 = ks / 2;

            // create reverse copy of kernel
            std::valarray<T> kernel_rev(ks);
            std::ranges::reverse_copy(kernel, std::begin(kernel_rev));

            // perform convolution using SignalX [ib, ie)
            for (size_t i = ib; i < ie; ++i)
            {
                T y_val {};

                for (size_t k = 0; k < ks; ++k)
                    y_val += cd.SignalX[i - ks2 + k] * kernel_rev[k];
                cd.SignalY[i] = y_val;
            }
        }

        catch (const std::exception& ex)
        {
            std::println("Exception occured in convolve_thread");
            std::println("{:s}", ex.what());
        }
    }

    void save_data(const char* fn) const
    {
        // save data to specfided filw
        std::ofstream ofs {fn, std::ios_base::out | std::ios_base::trunc};

        if (!ofs.good())
            throw std::runtime_error("save_data - file open error");

        T t {StartTime};
        size_t ss {SignalX.size()};

        for (size_t i = 0; i < ss; ++i)
        {
            std::print(ofs, "{:.6f}, ", t);
            t += StepTime;

            for (size_t j = 0; j < NumRs; ++j)
                std::print(ofs, "{:.6f}, ", RawSignals[j][i]);

            std::println(ofs, "{:.6f}, {:.6f}", SignalX[i], SignalY[i]);
        }
    
        ofs.close();
        std::println("results saved to file {:s}", fn);
    }

    // signal arrays
    std::valarray<T> SignalX {};                // input signal array
    std::valarray<T> SignalY {};                // output signal array

    // raw signal data (used to initialize SignalX)
    size_t NumRs {};                            // number of raw signals
    T StartTime {};                             // raw signal start time
    T EndTime {};                               // raw signal end time
    T StepTime {};                              // raw signal time step size

    std::valarray<T> Amplitudes {};             // raw signal ampltudes
    std::valarray<T> Frequencies {};            // raw signal frequecies
    std::valarray<T> PhaseAngles {};            // raw signal phase angles
    std::vector<std::valarray<T>> RawSignals {}; // raw signals used to build SignalX
};

#endif
