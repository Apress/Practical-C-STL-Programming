//-----------------------------------------------------------------------------
// Ch11_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch11_05.h"
#include "MT.h"
#include "Mineral.h"

void Ch11_05_ex1()
{
#ifdef __cpp_lib_ranges_contains
    const char* fmt = "{} ";
    constexpr size_t epl_max {3};

    // create test vector
    std::vector<Mineral> minerals { Mineral::get_vector_all() };
    MT::print_ctr("\nminerals:\n", minerals, fmt, epl_max);
    std::println("");

    // using std::ranges::contains
    std::vector<Mineral> find_vals
        {{"Agrellite", 5.5}, {"Kaolinite", 2.5}, {"Zircon", 7.5}};

    for (const auto& find_val : find_vals)
    {
        std::print("find_val: {:12s} | ", find_val.Name());

        if (std::ranges::contains(minerals, find_val))
            std::println("found, hardness = {:.2f}", find_val.Hardness());
        else
            std::println("not found!");
    }
#else
    std::println("Ch11_05_ex1() requires __cpp_lib_ranges_contains (C++23)");
#endif
}

void Ch11_05_ex2()
{
#ifdef __cpp_lib_ranges_contains
    const char* fmt = "{} ";
    constexpr size_t epl_max {3};

    // create test vector
    std::vector<Mineral> minerals { Mineral::get_vector_all() };
    MT::print_ctr("\nminerals:\n", minerals, fmt, epl_max);

    // using std::ranges::contains_subrange - example #1
    std::vector<Mineral> subrange1
        {{"Conichalcite", 4.5}, {"Lindgrenite", 4.5}, Mineral {"Apatite", 5.0}};
    MT::print_ctr("\nsubrange1:\n", subrange1, fmt, epl_max);

    bool bsr1 = std::ranges::contains_subrange(minerals, subrange1);
    std::println("\nsubrange1 {:s} in vector minerals",
            bsr1 ? "found" : "not found");

    // using std::ranges::contains_subrange - example #2
    std::vector<Mineral> subrange2
        {{"Kaolinite", 2.5}, {"Lindgrenite", 4.5}, Mineral {"Apatite", 5.0}};
    MT::print_ctr("\nsubrange2:\n", subrange2, fmt, epl_max);

    bool bsr2 = std::ranges::contains_subrange(minerals, subrange2);
    std::println("\nsubrange2 {:s} in vector minerals",
            bsr2 ? "found" : "not found");
#else
    std::println("Ch11_05_ex2() requires __cpp_lib_ranges_contains (C++23)");
#endif
}

void Ch11_05_ex()
{
    std::println("\n----- Ch11_05_ex1() -----");
    Ch11_05_ex1();

    std::println("\n----- Ch11_05_ex2() -----");
    Ch11_05_ex2();
}
