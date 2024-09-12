//-----------------------------------------------------------------------------
// Ch13_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <format>
#include <random>
#include <vector>
#include "Ch13_02.h"
#include "AminoAcid.h"
#include "MT.h"

void Ch13_02_ex1()
{
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {20};

    // create vector of random amino acid codes
    std::vector<std::string> vec1 = AminoAcid::get_vector_all_code3();
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // random number generator for std::ranges::shuffle
    unsigned int rng_seed {42};
    std::mt19937 rng {rng_seed};

    // using std::ranges::shuffle
    std::ranges::shuffle(vec1, rng);
    MT::print_ctr("\nvec1 (after first shuffle):\n", vec1, fmt, epl_max);

    std::ranges::shuffle(vec1, rng);
    MT::print_ctr("\nvec1 (after second shuffle):\n", vec1, fmt, epl_max);
}

void Ch13_02_ex2()
{
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {20};

    // create vector of random amino acid codes
    std::vector<std::string> vec1 = AminoAcid::get_vector_all_code3();
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // random number generator for std::ranges::sample
    unsigned int rng_seed {111};
    std::mt19937 rng {rng_seed};

    // using std::ranges::sample (sampling without replacements)
    std::array<size_t, 3> sample_sizes {5, 10, 15};

    for (size_t i = 0; i < sample_sizes.size(); ++i)
    {
        std::vector<std::string> sample(sample_sizes[i]);
        std::ranges::sample(vec1, sample.begin(), sample_sizes[i], rng);

        std::string s = std::format("\nsample #{:d}:\n", i);
        MT::print_ctr(s.c_str(), sample, fmt, epl_max);
    }
}

void Ch13_02_ex()
{
    std::println("\n----- Ch13_02_ex1() -----");
    Ch13_02_ex1();

    std::println("\n----- Ch13_02_ex2() -----");
    Ch13_02_ex2();
}
