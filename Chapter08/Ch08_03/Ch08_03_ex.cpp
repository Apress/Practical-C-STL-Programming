//-----------------------------------------------------------------------------
// Ch08_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <utility>
#include "Ch08_03.h"
#include "MT.h"

void Ch08_03_ex1()
{
    constexpr size_t epl_max {2};
    const char* fmt1 = "[{:3s}, ";
    const char* fmt2 = "{:^35s}] ";

    // initialize unordered maps
    uno_map_t map1 = get_airports(1);
    MT::print_unordered_map("\nmap1 (initial values):\n",
        map1, fmt1, fmt2, epl_max);

    uno_map_t map2 = get_airports(2);
    MT::print_unordered_map("\nmap2 (initial values):\n",
        map2, fmt1, fmt2, epl_max);

    // merge maps
    map2.merge(map1);
    MT::print_unordered_map("\nmap1 (after merge):\n",
        map1, fmt1, fmt2, epl_max);
    MT::print_unordered_map("\nmap2 (after merge):\n",
        map2, fmt1, fmt2, epl_max);

    // insert new elements
    map2.insert(std::make_pair("COD", "Yellowstone Regional"));
    map2["MHT"] = "Manchester-Boston Regional";

    MT::print_unordered_map("\nmap2 (after insertions):\n",
        map2, fmt1, fmt2, epl_max);

    // find keys in map
    std::array<std::string, 4> keys {"LAX", "PIT", "COD", "CHS"};

    std::println("\nfind keys in map2");
    for (auto key : keys)
    {
        std::print("key: {:s} - ", key);

        if (auto iter = map2.find(key); iter != map2.end())
            std::println("{:s}", iter->second);
        else
            std::println("not found");
    }

    // erase elements from map
    auto pred = [](const auto& elem)
        { auto const& [key, value] = elem; return key[0] == 'D'; };

    auto num_erasures = std::erase_if(map2, pred);

    std::println("\nnum_erasures = {:d}", num_erasures);
    MT::print_unordered_map("\nmap2 (after erasures):\n",
        map2, fmt1, fmt2, epl_max);
}

void Ch08_03_ex2()
{
   // simple hash function
    auto hash_func = [](const std::string& s) -> size_t
    {
        auto c = static_cast<unsigned char>(s[0]);
        return std::isalpha(c) ? std::toupper(c) - 'A' + 1 : c % 32;
    };

    // initialize map1
    constexpr size_t num_buckets {32};
    uno_map_hf_t map1(num_buckets, hash_func);
    get_airports(map1, 1);
    print_buckets("\nmap1 (initial values)", map1);

    // initialize map2
    uno_map_hf_t map2(num_buckets, hash_func);
    get_airports(map2, 2);
    print_buckets("\nmap2 (initial values)", map2);

    // merge maps
    map2.merge(map1);
    print_buckets("\nmap2 (after merge)", map2);

    // using relational operators (only operator== is defined)
    auto map3 {map2};
    std::println("\nmap2 == map3: {:s}", map2 == map3);
    std::println("map2 != map3: {:s}", map2 != map3);
}

void Ch08_03_ex3()
{
    constexpr size_t epl_max {2};
    const char* fmt1 = "[{:3s}, ";
    const char* fmt2 = "{:^35s}] ";

    // initialize unordered maps
    uno_map_t map1 = get_airports(1);
    uno_map_t map2 = get_airports(2);

    // using insert_range, copies elements from map2 to map1
#ifdef __cpp_lib_containers_ranges
    map1.insert_range(map2);
#else
    map1.insert(map2.begin(), map2.end());
#endif
    MT::print_unordered_map("\nmap1 (after insert_range):\n",
        map1, fmt1, fmt2, epl_max);

    // modify value component of each map1 key-value pair
    const std::string str1 = "International";
    const std::string str2 = "Intl.";

    for (auto iter = map1.begin(); iter != map1.end(); ++iter)
    {
        // iter->first points to key (airport code)
        // iter->second points to value (airport name)
        auto pos = iter->second.find(str1);

        if (pos != std::string::npos)
        {
            // replace str1 with str2 using replace_with_ranges (C++23)
            auto iter_b = iter->second.begin() + pos;
            auto iter_e = iter_b + str1.size();

#ifdef __cpp_lib_containers_ranges
            iter->second.replace_with_range(iter_b, iter_e, str2);
#else
            iter->second.replace(iter_b, iter_e, str2.begin(), str2.end());
#endif
        }
    }

    MT::print_unordered_map("\nmap1 (after replace_with_ranges):\n",
        map1, fmt1, fmt2, epl_max);
}

void Ch08_03_ex()
{
    std::println("\n----- Ch08_03_ex1() -----");
    Ch08_03_ex1();

    std::println("\n----- Ch08_03_ex2() -----");
    Ch08_03_ex2();

    std::println("\n----- Ch08_03_ex3() -----");
    Ch08_03_ex3();
}
