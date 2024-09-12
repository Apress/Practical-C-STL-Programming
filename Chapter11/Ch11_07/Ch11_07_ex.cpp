//-----------------------------------------------------------------------------
// Ch11_07_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <functional>
#include <vector>
#include "Ch11_07.h"
#include "HtmlColor.h"
#include "MT.h"

std::vector<std::vector<HtmlColor>> get_sequences(size_t offset)
{
    std::vector<std::vector<HtmlColor>> sequences {};

    for (size_t i = 0; ; ++i)
    {
        // create test sequence of three HtmlColor colors
        size_t indx0 = i * offset;
        size_t indx1 = i * offset + 1;
        size_t indx2 = i * offset + 2;

        if (i == 2)
            ++indx2;    // index for non-matching sequence

        if (indx2 >= HtmlColor::num_colors())
            break;

        std::vector<HtmlColor> sequence {};
        sequence.push_back(HtmlColor::get(indx0));
        sequence.push_back(HtmlColor::get(indx1));
        sequence.push_back(HtmlColor::get(indx2));

        sequences.push_back(sequence);
    }

    return sequences;
}

void Ch11_07_ex1()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // initialize vector of HtmColors
    std::vector<HtmlColor> colors = HtmlColor::get_vector();
    MT::print_ctr("\ncolors:\n", colors, fmt, epl_max);

    // generate HtmlColor color sequences
    std::vector<std::vector<HtmlColor>> sequences = get_sequences(30);

    for (const auto& sequence : sequences)
    {
        MT::print_ctr("\ntest sequence:\n", sequence, fmt, epl_max);

        // using std::ranges::search to find 'sequence' in 'colors'
        // std::ranges::search() returns iterator subrange [iter_b, iter_e)
        auto [iter_b, iter_e] = std::ranges::search(colors, sequence);

        if (iter_b != iter_e)
        {
            // sequence found, calculate position
            auto pos = std::distance(colors.begin(), iter_b);
            std::println("found sequence at position {:d}", pos);
        }
        else
            std::println("sequence not found");
    }
}

void Ch11_07_ex2()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {2};

    // initialize vector of HtmColors
    std::vector<HtmlColor> colors = HtmlColor::get_vector();
    MT::print_ctr("\ncolors:\n", colors, fmt, epl_max);

    // generate HtmlColor sequences
    std::vector<std::vector<HtmlColor>> sequences = get_sequences(31);

    for (const auto& sequence : sequences)
    {
        MT::print_ctr("\ntest sequence:\n", sequence, fmt, epl_max);

        // create sequence searcher
        std::boyer_moore_searcher searcher(sequence.begin(), sequence.end(),
            HtmlColor::hash_func_searcher);

        // using std::search to find 'sequence' in vector 'colors'
        auto iter = std::search(colors.begin(), colors.end(), searcher);

        if (iter != colors.end())
        {
            auto pos = std::distance(colors.begin(), iter);
            std::println("found sequence at position {:d}", pos);
        }
        else
            std::println("sequence not found");
    }
}

void Ch11_07_ex3()
{
    const char* fmt = "{:s} ";
    constexpr size_t epl_max {8};

    // initialize vector of HtmColor names
    std::vector<std::string> colors {};
    size_t num_colors {HtmlColor::num_colors()};

    for (size_t i = 0; i < num_colors; i += 25)
    {
        auto color {HtmlColor::get(i)};
        colors.emplace_back(color.Name());
    }

    for (size_t i = 0; i < 6; ++i)
    {
        // generate test vectors colors1a and colors2a
        constexpr size_t mmi {42};
        std::vector<std::string> colors1 {colors};
        std::vector<std::string> colors2 {colors};

        if (i == 1)
            colors1.insert(colors1.begin() + 2, HtmlColor::get(mmi).Name());
        else if (i == 2)
            colors2.insert(colors2.end() - 2, HtmlColor::get(mmi).Name());
        else if (i == 3)
            colors1.erase(colors1.begin() + 3);
        else if (i == 4)
            colors1.push_back(HtmlColor::get(mmi).Name());
        else if (i == 5)
            colors2.push_back(HtmlColor::get(mmi).Name());

        // display test vectors
        std::println("\nTest #{:d}", i);
        MT::print_ctr("colors1a: ", colors1, fmt, epl_max);
        MT::print_ctr("colors2a: ", colors2, fmt, epl_max);

        // using std::ranges::mismatch
        auto [iter1, iter2] = std::ranges::mismatch(colors1, colors2);

        if (iter1 == colors1.end() && iter2 == colors2.end())
            std::println("no mistmatch found");
        else
        {
            std::println("mismatch found");

            if (iter1 != colors1.end())
                std::println("*iter1 (colors1): {}", *iter1);

            if (iter2  != colors2.end())
                std::println("*iter2 (colors2): {}", *iter2);
        }
    }
}

void Ch11_07_ex()
{
    std::println("\n----- Ch11_07_ex1() -----");
    Ch11_07_ex1();

    std::println("\n----- Ch11_07_ex2() -----");
    Ch11_07_ex2();

    std::println("\n----- Ch11_07_ex3() -----");
    Ch11_07_ex3();
}

