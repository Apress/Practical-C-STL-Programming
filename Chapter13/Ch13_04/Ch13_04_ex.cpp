//-----------------------------------------------------------------------------
// Ch13_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch13_04.h"
#include "HtmlColor.h"
#include "MT.h"

void Ch13_04_ex1()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // create test vectors of HtmlColors
    std::vector<size_t> indices1
        {0, 1, 1, 3, 4, 7, 7, 7, 8, 8, 9, 10, 11, 12, 12, 13, 14 };
    std::vector<HtmlColor> colors1 = HtmlColor::get_vector(indices1);
    std::ranges::sort(colors1);
    MT::print_ctr("\ncolors1:\n", colors1, fmt, epl_max);

    std::vector<size_t> indices2
        {1, 1, 1, 4, 5, 6, 8, 9, 10, 10, 11, 12, 13, 16, 16} ;
    std::vector<HtmlColor> colors2 = HtmlColor::get_vector(indices2);
    std::ranges::sort(colors2);
    MT::print_ctr("\ncolors2:\n", colors2, fmt, epl_max);

    // using std::ranges::set_intersection
    std::vector<HtmlColor> colors3 {};
    std::ranges::set_intersection(colors1, colors2, std::back_inserter(colors3));
    MT::print_ctr("\ncolors3 (intersection):\n", colors3, fmt, epl_max);

    // using std::ranges::set_union
    std::vector<HtmlColor> colors4 {};
    std::ranges::set_union(colors1, colors2, std::back_inserter(colors4));
    MT::print_ctr("\ncolors4 (union):\n", colors4, fmt, epl_max);

    // using std::ranges::set_difference
    std::vector<HtmlColor> colors5 {};
    std::ranges::set_difference(colors1, colors2, std::back_inserter(colors5));
    MT::print_ctr("\ncolors5 (difference):\n", colors5, fmt, epl_max);

    // using std::ranges::symmetric_difference
    std::vector<HtmlColor> colors6 {};
    std::ranges::set_symmetric_difference(colors1, colors2,
        std::back_inserter(colors6));
    MT::print_ctr("\ncolors6 (symmetric_difference):\n", colors6, fmt, epl_max);
}

void Ch13_04_ex()
{
    std::println("\n----- Ch13_04_ex1() -----");
    Ch13_04_ex1();
}
