//-----------------------------------------------------------------------------
// Ch08_04_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <string_view>
#include <unordered_map>
#include "Ch08_04.h"
#include "MF.h"

void Ch08_04_ex1()
{
    // create unordered_multimap
    uno_mmap_t airports = get_airports();
    print_buckets("\nairports (initial values):", airports);

    // search airports for matching country codes
    std::array<std::string_view, 5> key_codes {"CH", "FR", "NL", "NO", "US"};

    for (const auto& key_code : key_codes)
    {
        auto range = airports.equal_range(key_code);
        std::print("\nkey_code: {:s} - match ", key_code);

        if (range.first == range.second)
            std::println("not found");
        else
        {
            std::println("found");

            // change city name to upper case
            for (auto iter = range.first; iter != range.second; ++iter)
            {
                Airport& airport = iter->second;
                airport.City = MF::to_upper(airport.City);

                std::println("  updating city name: {:s}", airport.City);

            }
        }
    }

    print_buckets("\nairports (after city name updates):", airports);
}

void Ch08_04_ex()
{
    std::println("\n----- Ch08_04_ex1() -----");
    Ch08_04_ex1();
}
