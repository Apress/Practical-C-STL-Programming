//-----------------------------------------------------------------------------
// Ch18_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <fstream>
#include <random>
#include <vector>
#include "Ch18_03.h"

void Ch18_03_ex1()
{
    constexpr size_t n {60};
    constexpr int rng_min {1};
    constexpr int rng_max {100};
    constexpr unsigned int rng_seed {42};

    // create random number generator (std::minstd_rand) & distribution
    std::minstd_rand rng1(rng_seed);
    std::uniform_int_distribution<int> dist1(rng_min, rng_max);

    // generate random numbers (integers)
    std::println("\nrandom values using generator std::minstd_rand");
    size_t add_nl = 0;
    for (size_t i = 0; i < n; ++i)
    {
        int rng_val = dist1(rng1);
        std::print("{:4d} ", rng_val);

        if (++add_nl % 15 == 0)
            std::println("");
    }

    // create random number generator (std::mt19937) & distribution
    std::println("\nrandom values using generator std::mt19937");
    std::mt19937 rng2(rng_seed);
    std::uniform_real_distribution<float> dist2(rng_min, rng_max);

    // generate random numbers (integers)
    add_nl = 0;
    for (size_t i = 0; i < n; ++i)
    {
        float rng_val = dist2(rng2);
        std::print("{:7.2f} ", rng_val);

        if (++add_nl % 10 == 0)
            std::println("");
    }
}

void Ch18_03_ex2()
{
    constexpr size_t num_iter {2};

    for (size_t iter = 0; iter < num_iter; ++iter)
    {
        constexpr size_t n {32};
        constexpr double rng_mean {5.0};
        constexpr double rng_sd {2.0};
        constexpr unsigned int rng_seed {42};

        // create random number generator and distribution
        std::mt19937 rng(rng_seed);
        std::normal_distribution<double> dist(rng_mean, rng_sd);

        size_t add_nl {0};
        std::println("\niteration #{:d}", iter);

        for (size_t i = 0; i < n; ++i)
        {
            double rng_val = dist(rng);
            std::print("{:8.4f} ", rng_val);

            if (++add_nl % 8 == 0)
                std::println("");
        }
    }
}

template <typename T> bool save_histogram(const std::string& fn,
const std::vector<T>& vec1, int num_buckets = 100)
{
    std::ofstream ofs(fn, std::ios::out | std::ios::trunc);

    if (!ofs.good())
        throw std::runtime_error("save_histogram - file open error");

    auto histo_min = std::ranges::min(vec1);
    auto histo_max = std::ranges::max(vec1);
    auto bucket_size = (histo_max - histo_min) / num_buckets;

    // create histogram vector (extra bucket holds counts for histo_max)
    std::vector<int> histo(num_buckets + 1);

    // build and save histogram
    for (auto v : vec1)
    {
        int bucket_index = static_cast<int>((v - histo_min) / bucket_size);
        ++histo.at(bucket_index);
    }

    for (auto bucket_count : histo)
        std::println(ofs, "{:d}", bucket_count);

    ofs.close();
    return ofs.good();
}

void Ch18_03_ex3()
{
    constexpr size_t num_iter {4};
    constexpr size_t num_vals {25'000};
    constexpr double rng_mean {10.0};
    constexpr double rng_sd {2.0};
    const std::string fn_base = "Ch18_03_ex3-histogram";

    // instantiate non-deterministic random integer generator
    std::random_device rng_dev {};

    for (size_t i = 0; i < num_iter; ++i)
    {
        // create vectors for random numbers
        std::vector<double> vec1(num_vals);
        
        // create non-deterministic random number generator, distribution
        std::mt19937 rng(rng_dev());
        std::normal_distribution<double> dist(rng_mean, rng_sd);

        // fill vec1 with random values
        for (size_t j = 0; j < num_vals; ++j)
            vec1[j] = dist(rng);

        // save histogram
        std::string fn_histo = std::format("{:s}-{:02d}.csv", fn_base, i);
        save_histogram(fn_histo, vec1);
        std::println("Saved histogram to file {:s}", fn_histo);
    }
}

void Ch18_03_ex()
{
    std::println("\n----- Ch18_03_ex1() -----");
    Ch18_03_ex1();

    std::println("\n----- Ch18_03_ex2() -----");
    Ch18_03_ex2();

    std::println("\n----- Ch18_03_ex3() -----");
    Ch18_03_ex3();
}
