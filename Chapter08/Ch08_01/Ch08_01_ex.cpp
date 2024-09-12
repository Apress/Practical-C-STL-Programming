//-----------------------------------------------------------------------------
// Ch08_01_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <functional>
#include <string>
#include <unordered_set>
#include "Ch08_01.h"
#include "MF.h"
#include "MT.h"
#include "HtmlColor.h"

uno_set_str_t Ch08_01_ex1()
{
    // create an unordered set of strings
    uno_set_str_t set1 { "Gulf of Alaska", "Caribbean Sea", "Black Sea",
        "Red Sea", "Gulf of Thailand", "Bering Sea" };

    print_buckets("\nset1 (initial values): ", set1);

    // add more elements using insert and emplace
    set1.insert("Baltic Sea");
    set1.insert("Mediterranean Sea");
    set1.insert("Gulf of Mexico");
    set1.emplace("Ross Sea");
    set1.emplace("Yellow Sea");
    set1.emplace("Greenland Sea");

    // add more elements using insert_range (C++23) or ranges::copy (C++20)
    std::array<std::string, 6> arr1
        {"Labrador Sea", "Amundsen Gulf", "North Sea",
         "Adriatic Sea", "Scotia Sea", "Gulf of Biscay"};

#if __cpp_lib_containers_ranges >= 202202L
    set1.insert_range(arr1);
#else
    std::ranges::copy(arr1, std::inserter(set1, set1.begin()));
#endif

    print_buckets("\nset1 (after insert_range): ", set1);
    return set1;
}

void Ch08_01_ex2(uno_set_str_t set1)
{
    // create new set
    uno_set_str_t set2 {"Yellow Sea", "Red Sea", "Arabian Sea", "Baffin Bay",
        "North Sea", "Beaufort Sea", "Caspian Sea", "Gulf of Biscay"};

    // set1 is the same as final output from Ch08_01_ex1()
    // print_buckets("\nset1 (initial values): ", set1);

    print_buckets("\nset2 (initial values): ", set2);

    // merge sets
    set2.merge(set1);
    print_buckets("\nset1 (after merge): ", set1);
    print_buckets("\nset2 (after merge): ", set2);

    // using contains
    std::println("\nset2.contains(\"North Sea\"): {:s}", set2.contains("North Sea"));
    std::println("set2.contains(\"Java Sea\"): {:s}", set2.contains("Java Sea"));
    std::println("");

    // using extract ("Green Sea" not member of set2)
    std::array<std::string, 3> extract_seas
        {"Black Sea", "Green Sea", "Red Sea"};

    for (const std::string& extract_sea : extract_seas)
    {
        std::print("extract_sea: {:s} - ", extract_sea);

        auto node_handle = set2.extract(extract_sea);

        if (!node_handle.empty())
        {
            std::println("found");
            node_handle.value() = MF::to_upper(node_handle.value());
            set2.insert(std::move(node_handle));
        }
        else
            std::println("not found");
    }

    print_buckets("\nset2 (after extracts): ", set2);
}

void Ch08_01_ex3()
{
    uno_set_str_t set1 {"Superior", "Michigan", "Huron", "Ontario", "Erie",
        "Tahoe", "Iliamna", "Crater", "Becharof", "Clark", "Sakakawea",
        "Pyramid", "Pontchartrain", "Champlain", "Mead", "Flathead",
        "Seneca", "Yellowstone", "Cayuga", "Bear"};

    print_buckets("\nset1 (initial values): ", set1);

    // remove strings that begin with an 'S'
    for (auto iter = set1.begin(); iter != set1.end(); )
    {
        if ((*iter)[0] == 'S')
            iter = set1.erase(iter);
        else
            ++iter;
    }
    print_buckets("\nset1 (after removals): ", set1);
}

void Ch08_01_ex4()
{
    // instantiate uno_set_hc_t object - custom hash function
    uno_set_hc_t colors(HtmlColor::hash_func_bucket_count, HtmlColor::hash_func);

    // change max_load_factor to prevent a rehash
    colors.max_load_factor(100.0f);

    // add HTML colors
    size_t num_colors = HtmlColor::num_colors();

    for (size_t i = 0; i < num_colors; ++i)
        colors.emplace(HtmlColor::get(i));

    print_buckets("--- Bucket values for 'colors' ---", colors);
}

void Ch08_01_ex()
{
    std::println("\n----- Ch08_01_ex1() -----");
    auto set = Ch08_01_ex1();

    std::println("\n----- Ch08_01_ex2() -----");
    Ch08_01_ex2(set);

    std::println("\n----- Ch08_01_ex3() -----");
    Ch08_01_ex3();

    std::println("\n----- Ch08_01_ex4() -----");
    Ch08_01_ex4();
}
