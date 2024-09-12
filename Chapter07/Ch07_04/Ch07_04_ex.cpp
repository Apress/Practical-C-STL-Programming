//-----------------------------------------------------------------------------
// Ch07_04_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include "Ch07_04.h"
#include "MT.h"

using mulmap_t = std::multimap<std::string_view, std::string>;

void Ch07_04_ex1()
{
    constexpr size_t epl_max {2};
    const char* fmt1 = "[{:<14s} | ";
    const char* fmt2 = "{:>14s}] ";

    // state abbreviations
    std::string_view ca {"California"};
    std::string_view fl {"Florida"};
    std::string_view il {"Illinois"};
    std::string_view ny {"New York"};
    std::string_view oh {"Ohio"};
    std::string_view tx {"Texas"};
    std::string_view wi {"Wisconsin"};

    mulmap_t mmap1
        {{ca, "Los Angeles"}, {ca, "San Francisco"}, {ca, "Fresno"},
         {il, "Chicago"}, {il, "Peoria"}, {il, "Rockford"},
         {oh, "Cleveland"}, {oh, "Columbus"}, {oh, "Cincinnati"},
         {tx, "Houston"}, {tx, "Dallas"}, {tx, "Austin"}, {tx, "El Paso"}};

    MT::print_multimap("\nmmap1 (initial values):\n", mmap1, fmt1, fmt2, epl_max);
    std::println("mmap1.size(): {:d}", mmap1.size());

    // add new key/value pairs to mmap1 using insert
    mmap1.insert(std::pair {fl, "Orlando"});
    mmap1.insert(std::pair {fl, "Miami"});
    mmap1.insert(std::pair {fl, "Jacksonville"});
    mmap1.insert(std::pair {fl, "Orlando"});
    MT::print_multimap("\nmmap1 (after insertions):\n", mmap1, fmt1, fmt2, epl_max);
    std::println("mmap1.size(): {:d}", mmap1.size());

    // add new key/value pairs to mmap1 using emplace
    mmap1.emplace(ny, "New York City");
    mmap1.emplace(ny, "Buffalo");
    mmap1.emplace(ny, "Albany");
    mmap1.emplace(ny, "Yonkers");
    mmap1.emplace(ny, "Syracuse");
    MT::print_multimap("\nmmap1 (after emplacements):\n", mmap1, fmt1, fmt2, epl_max);
    std::println("mmap1.size(): {:d}", mmap1.size());

    // using count
    auto count_il = mmap1.count(il);
    auto count_tx = mmap1.count(tx);
    std::println("\nnumber of {:s} cities in mmap1: {:d}", il, count_il);
    std::println("number of {:s} cities in mmap1: {:d}", tx, count_tx);

    // using contains (C++20)
    std::println("\nmmap1 contains key {:s}: {:s}", oh, mmap1.contains(oh));
    std::println("mmap1 contains key {:s}: {:s}", wi, mmap1.contains(wi));
}

void Ch07_04_ex2()
{
    constexpr size_t epl_max {3};
    const char* fmt1 = "[{:3s}, ";
    const char* fmt2 = "{:s}] ";

    // country abbreviations
    std::string_view ar {"Argentina"};
    std::string_view br {"Brazil"};
    std::string_view ca {"Canada"};
    std::string_view in {"India"};
    std::string_view mx {"Mexico"};

    // create and initialize multimap
    mulmap_t mmap1
        {{br, "Sao Paulo"}, {br, "Rio de Janeiro"}, {br, "Brasilia"},
         {ca, "Montreal"}, {ca, "Toronto"}, {ca, "Edmonton"},
         {ca, "Calgary"}, {ca, "Vancouver"},
         {in, "New Delhi"}, {in, "Chennai"},
         {mx, "Mexico City"}, {mx, "Tijuana"}, {mx, "Ecatepec"}};

    MT::print_multimap("\nmmap1 (initial values):\n", mmap1, fmt1, fmt2, epl_max);
    std::println("mmap1.size(): {:d}", mmap1.size());

    // using multimap::find
    std::println("\nsearching mmap1 using find()");
    std::array<std::string_view, 3> find_keys {ar, ca, in};

    for (const auto& find_key : find_keys)
    {
        std::print("\nfind_key: {:s}\n", find_key);

        auto iter = mmap1.find(find_key);

        if (iter == mmap1.end())
            std::println("not found");
        else
        {
            while (iter->first == find_key)
            {
                std::println("found: {:s}, {:s}", iter->first, iter->second);

                if (++iter == mmap1.end())
                    break;
            }
        }
    }

    // using multimap::equal_range
    std::println("\nsearching mmap1 using equal_range()");

    for (const auto& find_key : find_keys)
    {
        std::println("\nfind_key: {:s}", find_key);

        auto iter_er = mmap1.equal_range(find_key);

        if (iter_er.first->first != find_key)
            std::println("not found");
        else
        {
            for (auto iter = iter_er.first; iter != iter_er.second; ++iter)
                std::println("found: {:s}, {:s}", iter->first, iter->second);
        }
    }
}

void Ch07_04_ex()
{
    std::println("\n----- Ch07_04_ex1() -----");
    Ch07_04_ex1();

    std::println("\n----- Ch07_04_ex2() -----");
    Ch07_04_ex2();
}
