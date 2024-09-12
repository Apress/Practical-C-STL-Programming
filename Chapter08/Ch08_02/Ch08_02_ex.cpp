//-----------------------------------------------------------------------------
// Ch08_02_ex.cpp
//-----------------------------------------------------------------------------

#include <string>
#include <unordered_set>
#include "Ch08_02.h"
#include "HtmlColor.h"
#include "MF.h"

void Ch08_02_ex1()
{
    uno_mset_t colors(HtmlColor::hash_func_bucket_count, HtmlColor::hash_func);

    // add elements to colors using emplace
    for (size_t i = 0; i < HtmlColor::num_colors(); i += 10)
        colors.emplace(HtmlColor::get(i));

    // add elements to colors using insert
    for (size_t i = 0; i < HtmlColor::num_colors(); i += 20)
        colors.insert(HtmlColor::get(i));

    // using merge to add duplicates
    uno_mset_t more_colors(HtmlColor::hash_func_bucket_count, HtmlColor::hash_func);

    HtmlColor test_color1 {HtmlColor::get(HtmlColor::num_colors() / 2)};
    HtmlColor test_color2 {HtmlColor::get(HtmlColor::num_colors() / 5)};
    std::println("\ntest_color1: {}", test_color1);
    std::println("test_color2: {}", test_color2);

    more_colors.insert(test_color1);
    more_colors.insert(test_color1);
    more_colors.insert(test_color1);
    more_colors.insert(test_color2);
    more_colors.insert(test_color2);

    colors.merge(more_colors);
    print_buckets("\ncolors (initial values):", colors);

    // using extract and insert
    HtmlColor test_color3 {"FalseColor", 0x123456};
    std::vector<HtmlColor> test_colors {test_color1, test_color2, test_color3};

    for (auto test_color : test_colors)
    {
        auto iter = colors.find(test_color);

        for (; iter != colors.end(); iter = colors.find(test_color))
        {
            // extract node
            auto node_handle = colors.extract(test_color);

            // convert name to upper case
            HtmlColor html_color_ex = node_handle.value();
            std::string name {html_color_ex.Name()};
            MF::to_upper(name);

            // reinsert updated color
            node_handle.value() = HtmlColor {name, html_color_ex.ValRgb()};
            colors.insert(std::move(node_handle));
        }
    }

    print_buckets("\ncolors (after extract/insert operations):", colors);
}

void Ch08_02_ex()
{
    std::println("\n----- Ch08_02_ex1() -----");
    Ch08_02_ex1();
}
