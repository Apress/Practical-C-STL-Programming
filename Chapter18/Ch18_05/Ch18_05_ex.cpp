//-----------------------------------------------------------------------------
// Ch18_05_ex.cpp
//-----------------------------------------------------------------------------

#include <vector>
#include "Ch18_05.h"
#include "MT.h"
#include "RN.h"

void Ch18_05_ex1()
{
    const char* fmt1 = "{:7.1f}";
    const char* fmt2 = "{:7d}";
    constexpr size_t epl_max1 {10};
    constexpr size_t epl_max2 {10};

    constexpr size_t n {50};
    constexpr int rng_min {1};
    constexpr int rng_max {500};
    constexpr unsigned int rng_seed {99};

    // using RN::get_vector (constant seed)
    std::vector vec1 = RN::get_vector<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nvec1:\n", vec1, fmt1, epl_max1);

    std::vector vec2 = RN::get_vector<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nvec2:\n", vec2, fmt1, epl_max1);
    std::println("\nvec1 == vec2: {:s} (expect true)", vec1 == vec2);

    // using RN::get_vector (hardware seed)
    std::vector vec3 = RN::get_vector<int>(n, rng_min, rng_max, 0);
    MT::print_ctr("\nvec3:\n", vec3, fmt2, epl_max2);

    std::vector vec4 = RN::get_vector<int>(n, rng_min, rng_max, 0);
    MT::print_ctr("\nvec4:\n", vec4, fmt2, epl_max2);
    std::println("\nvec3 == vec3: {:s} (expect false)", vec3 == vec4);
}

void Ch18_05_ex()
{
    std::println("\n----- Ch18_05_ex1() -----");
    Ch18_05_ex1();
}
