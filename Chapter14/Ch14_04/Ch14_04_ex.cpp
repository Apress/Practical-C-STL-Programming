//-----------------------------------------------------------------------------
// Ch14_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>
#include "Ch14_04.h"
#include "HtmlColor.h"
#include "MT.h"
#include "MTH.h"

void Ch14_04_ex1()
{
    const char* fmt = "{:7d}";
    constexpr size_t epl_max {10};

    // create test vector
    std::vector<int> vec1(50);

#ifdef __cpp_lib_ranges_iota        // C++23
    std::ranges::iota(vec1, 1);
#else
    std::iota(vec1.begin(), vec1.end(), 1);
#endif
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // drop_while predicate
    auto dw_pred = [](int x) { return x <= 25; };
    
    // using std::views::filter and std::views::drop_while
    auto view1 = vec1
               | std::views::filter(MTH::is_prime<int>)
               | std::views::drop_while(dw_pred);

    MT::print_ctr("\nview1 (after filter and drop_while):\n", view1, fmt, epl_max);
}

void Ch14_04_ex2()
{
    const char* fmt = "{:7d}";
    constexpr size_t epl_max {10};

    // create view of integers [1, 51) (range factory)
    auto view0 = std::views::iota(1, 51);
    MT::print_ctr("\nview0 (result of std::views::iota):\n", view0, fmt, epl_max);

    // drop_while predicate
    auto dw_pred = [](int x) { return x <= 25; };

    // using std::views::filter and std::drop_while
    auto view1 = view0
               | std::views::filter(MTH::is_prime<int>)
               | std::views::drop_while(dw_pred);

    MT::print_ctr("\nview1 (after filter and drop_while):\n", view1, fmt, epl_max);
}

template <typename T>
void print_colors(const char* msg, T& colors)
{
    std::print("{:s}", msg);

    for (const HtmlColor& color : colors)
    {
        std::print("[{:4d} {:4d} {:4d}] ", color.R(), color.G(), color.B());
        std::println("[{:9.4f} {:9.4f} {:9.4f}] {:s}", color.H(), color.S(),
            color.I(), color.Name());
    }
}

// #define PRINT_ALL

void Ch14_04_ex3()
{
    // create test vector of HtmlColors
    std::vector<HtmlColor> colors = HtmlColor::get_vector();
#ifdef PRINT_ALL
    print_colors("\ncolors (initial values):\n", colors);
#endif

    // sort colors using hue
    std::ranges::sort(colors, std::ranges::less(), &HtmlColor::H);
#ifdef PRINT_ALL
    print_colors("\ncolors (after sort by hue):\n", colors);
#endif

    // using std::views::filter to select green colors
    auto is_green = [](const HtmlColor& c)
        { return 110.0 <= c.H() && c.H() <= 160.0; };

    auto colors_g1 = colors | std::views::filter(is_green);
    print_colors("\ncolors_g1:\n", colors_g1);

    // using std::views::reverse and std::views::take (largest green hues)
    auto colors_g2 = colors_g1 | std::views::reverse | std::views::take(4);
    print_colors("\ncolors_g2 (largest green hues):\n", colors_g2);

    // using std::views::take_while
    constexpr float hue_thresh {140.0};
    auto tw_pred = [](const HtmlColor& c) { return c.H() <= hue_thresh; };
    auto colors_g3 = colors_g1 | std::views::take_while(tw_pred);

    std::string msg {};
    std::format_to(std::back_inserter(msg), "\ncolors_g3 (hue < {:.2f}):\n",
        hue_thresh);
    print_colors(msg.c_str(), colors_g3);
}

void Ch14_04_ex()
{
    std::println("\n----- Ch14_04_ex1() -----");
    Ch14_04_ex1();

    std::println("\n----- Ch14_04_ex2() -----");
    Ch14_04_ex2();

    std::println("\n----- Ch14_04_ex3() -----");
    Ch14_04_ex3();
}
