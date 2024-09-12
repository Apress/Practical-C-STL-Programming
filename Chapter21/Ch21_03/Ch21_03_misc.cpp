//-----------------------------------------------------------------------------
// Ch21_03_misc.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include "Ch21_03.h"
#include "Airport.h"

std::vector<Airport> get_random_airports(size_t n, unsigned int rng_seed)
{
    std::vector<Airport> airports1 = Airport::get_vector_airports_shuffle(rng_seed);

    std::vector<Airport> airports2(n);
    std::ranges::copy_n(airports1.begin(), n, airports2.begin());
    return airports2;
}

std::vector<double> calc_distance_matrix(const std::vector<Airport>& airports,
    Airport::GeoCoord::Units units)
{
    size_t n = airports.size();

    if (n <= 1)
        throw std::runtime_error("calc_distance_matrix() - size error");

    std::vector<double> distance_matrix(n * n);

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            double& distance = distance_matrix[i * n + j];

            if (i == j)
                distance = 0.0;
            else if (i < j)
                distance = Airport::calc_distance(airports[i], airports[j], units);
            else
                distance = distance_matrix[j * n + i];
        }
    }

    return distance_matrix;
}

void print_distance_matrix(const std::string& title, const std::vector<Airport>& airports,
    const std::vector<double>& distance_matrix)
{
    const size_t n = airports.size();

    if (distance_matrix.size() != n * n)
        throw std::runtime_error("print_distance_matrix() - size error");

    std::println("\n{:s}", title);

    std::string s {};

    for (size_t i = 0; i < n + 1; ++i)
    {
        for (size_t j = 0; j < n + 1; ++j)
        {
            if (i == 0)
            {
                if (j == 0)
                    std::print("{:10s}", s);
                else
                    std::print("{:10s}", airports[j - 1].IataCode());  // col code
            }
            else
            {
                if (j == 0)
                    std::print("{:10s}", airports[i - 1].IataCode());  // row code
                else
                    std::print("{:<10.2f}", distance_matrix[(i - 1) * n + (j - 1)]);
            }
        }

        std::println("");
    }
}
