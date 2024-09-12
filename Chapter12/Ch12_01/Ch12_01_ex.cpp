//-----------------------------------------------------------------------------
// Ch12_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch12_01.h"
#include "Airport.h"
#include "MT.h"
#include "RN.h"

void Ch12_01_ex1()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {1};

    // initialize vector of airports
    std::vector<Airport> airports = Airport::get_vector_airports_shuffle();
    MT::print_ctr("\nairports (before sort):\n", airports, fmt, epl_max);

    // using std::sort (uses Airport::operator< which uses IATA code)
    std::sort(airports.begin(), airports.end());
    MT::print_ctr("\nairports (ascending by IATA):\n", airports, fmt, epl_max);

    // using std::ranges::sort (custom compare, descending order using latitude)
    auto cmp_op = [](const Airport& ap1, const Airport& ap2)
    {
        auto [lat1, lon1] = ap1.Location().to_decimal();
        auto [lat2, lon2] = ap2.Location().to_decimal();
        return lat1 > lat2;
    };

    std::ranges::sort(airports, cmp_op);
    MT::print_ctr("\nairports (descending by latitude):\n", airports, fmt, epl_max);
}

void Ch12_01_ex2()
{
    auto print_airports = [](const char* msg, const std::vector<Airport>& airports)
    {
        size_t nl {};
        std::println("{:s}", msg);

        for (const auto& ap : airports)
        {
            std::print("[{:2s} {:3s} {:32s}] ",
                ap.CountryCode(), ap.IataCode(), ap.Name());

            if (++nl % 2 == 0)
                std::println("");
        }

        std::println("");
    };

    // initialize vectors of airports
    std::vector<Airport> airports = Airport::get_vector_airports_shuffle();
    print_airports("airports (before stable_sort):", airports);

    // compare op for sorting
    auto cmp_op = [](const Airport& ap1, const Airport& ap2)
        { return ap1.CountryCode() < ap2.CountryCode(); };

    // using std::ranges::stable_sort - preserves equivalent orderings
    std::ranges::stable_sort(airports, cmp_op);
    print_airports("airports (after stable_sort):", airports);
}

void Ch12_01_ex3()
{
    const char* fmt = "{:5d} ";
    constexpr size_t epl_max {12};

    // initialize vector of random integers
    auto vec1 = RN::get_vector<int>(60);
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // using std::ranges::nth_element to find median
    auto iter_nth = vec1.begin() + vec1.size() / 2;

    std::ranges::nth_element(vec1, iter_nth);
    MT::print_ctr("\nvec1 (after nth_element):\n", vec1, fmt, epl_max);
    std::println("\nmedian value of vec1: {:d}", *iter_nth);
}

void Ch12_01_ex4()
{
    const char* fmt = "{:5d}";
    constexpr size_t epl_max {16};

    auto print_vec = [](const std::vector<int>& v)
    {
        // using std::ranges::is_sorted
        std::println("is_sorted:       {:s}", std::ranges::is_sorted(v));

        // using std::ranges::is_sorted_until
        auto iter_until = std::ranges::is_sorted_until(v);
        std::print("is_sorted_until: ");

        if (iter_until != v.end())
            std::println("{:d}", *iter_until);
        else
            std::println("sorted");
    };

    // initialize vector of random integers
    auto vec1 = RN::get_vector<int>(16);
    MT::print_ctr("\nvec1 (initial order):\n", vec1, fmt, epl_max);
    print_vec(vec1);

    // using std::ranges::partial_sort - range, middle
    auto iter_ps = vec1.begin() + vec1.size() / 3;
    std::ranges::partial_sort(vec1, iter_ps);
    MT::print_ctr("\nvec1 (after first partial_sort):\n", vec1, fmt, epl_max);
    print_vec(vec1);

    // using std::ranges::partial_sort - first, middle, last
    std::ranges::partial_sort(iter_ps, vec1.end(), vec1.end());
    MT::print_ctr("\nvec1 (after second partial_sort):\n", vec1, fmt, epl_max);
    print_vec(vec1);
}

void Ch12_01_ex()
{
    std::println("\n----- Ch12_01_ex1() -----");
    Ch12_01_ex1();

    std::println("\n----- Ch12_01_ex2() -----");
    Ch12_01_ex2();

    std::println("\n----- Ch12_01_ex3() -----");
    Ch12_01_ex3();

    std::println("\n----- Ch12_01_ex4() -----");
    Ch12_01_ex4();
}
