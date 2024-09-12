//-----------------------------------------------------------------------------
// Ch12_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch12_02.h"
#include "Airport.h"
#include "MT.h"

void print_airports(const char* msg, const std::vector<Airport>& airports)
{
    size_t nl {};
    std::println("{:s}", msg);

    for (const auto& ap : airports)
    {
        std::print("[{:2s} {:3s} {:32s}] ", ap.CountryCode(), ap.IataCode(),
            ap.Name());
        if (++nl % 2 == 0)
            std::println("");
    }
}

std::vector<Airport> Ch12_02_ex1()
{
    // using std::ranges::sort (uses Airport::operator< which uses IATA code)
    std::vector<Airport> airports = Airport::get_vector_airports_shuffle(8191);
    std::ranges::sort(airports);
    print_airports("\nairports (ascending sort by IATA code):", airports);

    // list of airports to search for (Airport::operator== compares IATA codes)
    std::vector<Airport> more_airports
    {
        Airport {"US", "LAX", "Los Angeles International",
            Airport::GeoCoord{33, 56, 33, 'N', 118, 24, 29, 'W'}},
        Airport {"US", "BOS", "Logan International",                    // new
            Airport::GeoCoord{42, 21, 47, 'N',  71, 0, 23, 'W'}},
        Airport {"US", "ORD", "O'Hare International",
            Airport::GeoCoord{41, 58, 43, 'N',  87, 54, 17, 'W'}},
        Airport {"US", "ANC", "Ted Stevens Anchorage Intl.",            // new
            Airport::GeoCoord{61, 10, 27, 'N', 149, 59, 54, 'W'}},
        // repeat airports to confirm successful insertions
        Airport {"US", "BOS", "Logan Internatioal",
            Airport::GeoCoord{42, 21, 47, 'N',  71, 0, 23, 'W'}},
        Airport {"US", "ANC", "Ted Stevens Anchorage Intl.",
            Airport::GeoCoord{61, 10, 27, 'N', 149, 59, 54, 'W'}},
    };

    for (auto const& new_airport : more_airports)
    {
        // using std::ranges::binary_search
        std::println("\nsearching for airport: {:s}", new_airport.IataCode());
        bool sea_result = std::ranges::binary_search(airports, new_airport);

        if (sea_result)
            std::println("airport found: {}", new_airport);
        else
        {
            // using std::ranges::upper_bound
            auto iter_insert = std::ranges::upper_bound(airports, new_airport);
            airports.insert(iter_insert, new_airport);
            std::println("airport not found - added to container");
        }
    }

    print_airports("\nairports (after new airport insertions):", airports);
    return airports;
}

void Ch12_02_ex2(std::vector<Airport>& airports)
{
    // sort airports in descending order by country code
    auto cmp_op = [](const Airport& ap1, const Airport& ap2)
        { return ap1.CountryCode() > ap2.CountryCode(); };

    std::ranges::sort(airports, cmp_op);
    print_airports("\nairports (descending sort by country code):", airports);

    // vector below contains invalid country codes for test purposes
    std::vector<std::string> country_codes {"AA", "AU", "DE", "NN", "US", "ZZ"};

    for (auto country_code : country_codes)
    {
        Airport ap_temp { country_code, "", "", Airport::GeoCoord{} };

        // using std::ranges::equal_range (must use same sort_op)
        auto iter_sr = std::ranges::equal_range(airports, ap_temp, cmp_op);

        std::println("\nresults for country code '{:s}' ",
                  country_code);

        if (iter_sr.begin() == iter_sr.end())
            std::println("no airports found");
        else
        {
            auto f = [](const auto& ap) { std::println("{}", ap); };
            std::ranges::for_each(iter_sr, f);
        }
    }
}

void Ch12_02_ex()
{
    std::println("\n----- Ch12_02_ex1() -----");
    auto airports = Ch12_02_ex1();

    std::println("\n----- Ch12_02_ex2() -----");
    Ch12_02_ex2(airports);
}
