//-----------------------------------------------------------------------------
// Ch13_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <string>
#include <vector>
#include "Ch13_05.h"
#include "HtmlColor.h"
#include "MT.h"

void Ch13_05_ex1()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // create test vector of HtmlColors
    std::vector<size_t> indices1 {20, 40, 60, 80, 100};
    std::vector<HtmlColor> colors1 = HtmlColor::get_vector(indices1);

    int i {};

    while (1)
    {
        std::string s = "\niteration " + std::to_string(++i) + ":\n";
        MT::print_ctr(s.c_str(), colors1, fmt, epl_max);

        // using std::ranges::next_permutation
        // returns template<class I>
        // struct next_permutation_result { I in; bool found; };
        // in = colors1.end()
        auto np_result = std::ranges::next_permutation(colors1);

        if (!np_result.found)
            break;
    }
}

void Ch13_05_ex2()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // create test vectors of HtmlColors
    std::vector<size_t> indices1 {100, 101, 102, 103, 104, 105, 106, 107};
    std::vector<HtmlColor> colors1 = HtmlColor::get_vector(indices1);
    MT::print_ctr("\ncolors1:\n", colors1, fmt, epl_max);

    std::vector<size_t> indices2 {101, 107, 103, 104, 102, 106, 100, 105};
    std::vector<HtmlColor> colors2 = HtmlColor::get_vector(indices2);
    MT::print_ctr("\ncolors2:\n", colors2, fmt, epl_max);

    std::vector<size_t> indices3 {101, 107, 103, 104, 102, 106, 108, 105};
    std::vector<HtmlColor> colors3 = HtmlColor::get_vector(indices3);
    MT::print_ctr("\ncolors3:\n", colors3, fmt, epl_max);

    // using std::ranges::is_permutation
    bool b12 = std::ranges::is_permutation(colors1, colors2);
    bool b13 = std::ranges::is_permutation(colors1, colors3);
    std::println("\nis_permutation (colors1, colors2): {:s}", b12);
    std::println("is_permutation (colors1, colors3): {:s}", b13);
}

void Ch13_05_ex()
{
    std::println("\n----- Ch13_05_ex1() -----");
    Ch13_05_ex1();

    std::println("\n----- Ch13_05_ex2() -----");
    Ch13_05_ex2();
}
