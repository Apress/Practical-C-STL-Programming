//-----------------------------------------------------------------------------
// Ch08_03_misc.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <iterator>
#include <string>
#include <unordered_map>
#include "Ch08_03.h"

uno_map_t get_airports(int id)
{
    uno_map_t map;

    if (id == 1)
    {
        map.emplace("ABQ", "Albuquerque International");
        map.emplace("BWI", "Baltimore/Washington International");
        map.emplace("BOS", "Logan International");
        map.emplace("CLT", "Charlotte Douglas International");
        map.emplace("DEN", "Denver International");
        map.emplace("DFW", "Dallas Fort Worth International");
        map.emplace("DSM", "Des Moines International");
        map.emplace("DTS", "Detroit Metro Wayne County");
    }
    else
    {
        map.emplace("FAI", "Fairbanks International");
        map.emplace("ITO", "Hilo International");
        map.emplace("LAX", "Los Angeles International");
        map.emplace("LGA", "LaGuardia");
        map.emplace("MCO", "Orlando International");
        map.emplace("ORD", "O'Hare International");
        map.emplace("PHX", "Phoenix Sky Harbor International");
        map.emplace("SEA", "Seattle-Tacoma International");
    }

    return map;
}

void get_airports(uno_map_hf_t& map, int id)
{
    std::ranges::copy(get_airports(id), std::inserter(map, map.begin()));
}

void print_buckets(const char* msg, const uno_map_hf_t& map)
{
    // print stats
    std::println("{:s}", msg);
    std::print("size: {} ", map.size());
    std::print("bucket_count: {}  ", map.bucket_count());
    std::println("load_factor:  {}\n", map.load_factor());

    // print buckets (airport code only)
    unsigned int add_nl {};
    size_t bc = map.bucket_count();

    for (size_t i = 0; i < bc; ++i)
    {
        if (map.bucket_size(i) != 0)
        {
            std::string s {};
            std::format_to(std::back_inserter(s), "bucket {:2d}: ", i);

            for (auto iter = map.begin(i); iter != map.end(i); ++iter)
                std::format_to(std::back_inserter(s), "{:4s}", iter->first);

            if  ((++add_nl % 2) == 0)
                std::println("{:40s}", s);
            else
                std::print("{:40s}", s);
        }
    }

    if (add_nl % 2 != 0)
        std::println("");
}
