//-----------------------------------------------------------------------------
// Ch11_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch11_04.h"
#include "Airport.h"
#include "MT.h"

void Ch11_04_ex1()
{
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {10};

    std::vector<std::string> iata_codes {Airport::get_vector_iata_codes()};
    MT::print_ctr("\niata_codes\n", iata_codes, fmt, epl_max);
    std::println("");

    std::vector<std::string> find_codes {"AKL", "DFW", "FRA", "ORD"};

    for (const std::string& find_code : find_codes)
    {
        // using std::ranges::find (uses operator==)
        std::print("IATA code: {:s} - ", find_code);
        auto iter = std::ranges::find(iata_codes, find_code);

        if (iter != iata_codes.end())
            std::println("found");
        else
            std::println("not found");
    }
}

void Ch11_04_ex2()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {1};

    // vector of airports
    std::vector<Airport> airports = Airport::get_vector_airports();
    MT::print_ctr("\nairports\n", airports, fmt, epl_max);

    // using std::find_if (uses specfied find predicate)
    auto find_op = [](const Airport& airport)
        { auto [lat, lon] = airport.Location().to_decimal(); return lat < 0; };

    std::println("\nairports found:");
    auto iter = airports.begin();

    while (1)
    {
        iter = std::ranges::find_if(iter, airports.end(), find_op);

        if (iter == airports.end())
            break;

        std::println("{}", *iter);
        iter++;
    }
}

void Ch11_04_ex3()
{
    std::vector<Airport> airports = Airport::get_vector_airports();

    // list of airports to find (Airport::operator== compares IATA codes)
    std::vector<Airport> find_airports
    {
        Airport {"", "CDG", "", Airport::GeoCoord {}},
        Airport {"", "ZRH", "", Airport::GeoCoord {}},
        Airport {"", "FRA", "", Airport::GeoCoord {}},
    };

    // using std::ranges::find_first_of
    std::println("\nairports found using find_first_of:");
    auto iter = airports.begin();

    while (1)
    {
        iter = std::ranges::find_first_of(iter, airports.end(),
            find_airports.begin(), find_airports.end());

        if (iter == airports.end())
            break;

        std::println("{}", *iter);
        iter++;
    }
}

//#define PRINT_SUBRANGE   // remove comment to enable

void Ch11_04_ex4()
{
#ifdef __cpp_lib_ranges_find_last
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {15};
    std::vector<std::string> iata_codes { Airport::get_vector_random_iata_codes(60) };
    MT::print_ctr("\niata_codes:\n", iata_codes, fmt, epl_max);

    // iata codes to find
    std::vector<std::string> find_vals
        {"ARN", "IAH", "MXX", "PVG", "WLG"};

    // using std::ranges::find_last
    for (const auto& find_val : find_vals)
    {
        std::print("\nfind_val: {:3s} | airport ", find_val);

        // std::ranges::find_last returns iterator subrange
        // object found         iter_sr = [iter of found obj, iata_codes.end())
        // object not found     iter_sr = [iata_codes.end(), iata_codes.end())
        auto iter_sr = std::ranges::find_last(iata_codes, find_val);

        if (iter_sr.begin() != iata_codes.end())
        {
#ifdef PRINT_SUBRANGE
            std::println("subrange iter_sr");
            for (auto iter = iter_sr.begin(); iter != iter_sr.end(); ++iter)
                std::print ("{:3s} ", *iter);
            std::println("");
#endif
            // calculate position
            auto find_pos = std::distance(iata_codes.begin(), iter_sr.begin());
            std::println("found (position = {:d})", find_pos);

            // print found airport
            std::optional<Airport> airport { Airport::get(find_val) };

            if (airport)
                std::println("{}", airport.value());
        }
        else
            std::println("not found");
    }
#else
    std::println("Ch11_04_ex4() requires __cpp_lib_ranges_find_last (C++23)");
#endif
}

void Ch11_04_ex()
{
    std::println("\n----- Ch11_04_ex1() -----");
    Ch11_04_ex1();

    std::println("\n----- Ch11_04_ex2() -----");
    Ch11_04_ex2();

    std::println("\n----- Ch11_04_ex3() -----");
    Ch11_04_ex3();

    std::println("\n----- Ch11_04_ex4() -----");
    Ch11_04_ex4();
}
