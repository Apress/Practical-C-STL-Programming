//-----------------------------------------------------------------------------
// Airport.cpp
//----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <format>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "Airport.h"
#include "MTH.h"

namespace
{
    const std::vector<Airport> c_Airports
    {
        // data below not suitable for navigation purposes
        Airport {"AU", "SYD", "Sydney Kingsford Smith",
            Airport::GeoCoord{33, 56, 46, 'S',  151, 10, 38, 'E'}},
        Airport {"AU", "MEL", "Melbourne",
            Airport::GeoCoord{37, 40, 24, 'S',  144, 50, 36, 'E'}},
        Airport {"BR", "BSB", "Brasilia International",
            Airport::GeoCoord{15, 52, 16, 'S',   47, 55, 7, 'W'}},

        // airports YYC - JFK excluded from listing

        Airport {"CA", "YYC", "Calgary International",
            Airport::GeoCoord{51, 7, 21, 'N',   114,  0, 48, 'W'}},
        Airport {"CA", "YEG", "Edmonton International",
            Airport::GeoCoord{43, 40, 36, 'N',   79, 37, 50, 'W'}},
        Airport {"CA", "YVR", "Vancouver International",
            Airport::GeoCoord{49, 11, 41, 'N',   123, 11, 2, 'W'}},
        Airport {"CA", "YYZ", "Toronto Pearson International",
            Airport::GeoCoord{53, 18, 36, 'N',   113, 34, 46, 'W'}},
        Airport {"CH", "ZRH", "Zurich",
            Airport::GeoCoord{47, 25, 53, 'N',   8, 32, 57, 'E'}},
        Airport {"CL", "SCL", "Santiago International",
            Airport::GeoCoord{33, 23, 34, 'S',   70, 47, 28, 'W'}},
        Airport {"CN", "PEK", "Beijing Capital International",
            Airport::GeoCoord{40,  4, 21, 'N',   116, 35, 51, 'E'}},
        Airport {"CN", "PVG", "Shanghai Pudong International",
            Airport::GeoCoord{31,  8, 36, 'N',   121, 48, 19, 'E'}},
        Airport {"DE", "BER", "Berlin Brandenburg",
            Airport::GeoCoord{52, 22,  0, 'N',  13, 30, 12, 'E'}},
        Airport {"DE", "FRA", "Frankfurt",
            Airport::GeoCoord{50,  2,  0, 'N',   8, 34, 14, 'E'}},
        Airport {"DE", "MUN", "Munich Franz Josef Stauss",
            Airport::GeoCoord{48, 21,  14, 'N', 11, 47, 10, 'E'}},
        Airport {"FR", "CDG", "Paris Charles de Gaulle",
            Airport::GeoCoord{49,  0, 35, 'N',   2, 32, 52, 'E'}},
        Airport {"FR", "TLS", "Toulouse-Blagnac",
            Airport::GeoCoord{43, 38,  6, 'N',   1, 22,  4, 'E'}},
        Airport {"GB", "GLA", "Glasgow",
            Airport::GeoCoord{55, 52, 19, 'N',   4, 25, 59, 'W'}},
        Airport {"GB", "LHR", "Heathrow International",
            Airport::GeoCoord{51, 28, 39, 'N',   0, 27, 41, 'W'}},
        Airport {"IN", "DEL", "Indira Gandhi International",
            Airport::GeoCoord{28, 34, 7, 'N',   77, 6, 44, 'E'}},
        Airport {"JP", "KIX", "Kansai International",
            Airport::GeoCoord{34, 25, 50, 'N',   135, 13, 49, 'E'}},
        Airport {"JP", "NRT", "Narita International",
            Airport::GeoCoord{35, 45, 55, 'N',   140, 23, 8, 'E'}},
        Airport {"NO", "OSL", "Oslo Gardermoen",
            Airport::GeoCoord{60, 12, 10, 'N',  11, 5, 2, 'E'}},
        Airport {"NZ", "AKL", "Auckland",
            Airport::GeoCoord{37,  0, 29, 'S', 174, 47, 30, 'E'}},
        Airport {"NZ", "WLG", "Wellington International",
            Airport::GeoCoord{41, 19, 38, 'S', 174, 48, 19, 'E'}},
        Airport {"SE", "ARN", "Stockholm Arlanda",
            Airport::GeoCoord{59, 30, 7, 'N',  17, 55, 7, 'E'}},
        Airport {"US", "IAH", "George Bush International",
            Airport::GeoCoord{29, 59,  4, 'N',  95, 20, 29, 'W'}},
        Airport {"US", "JFK", "John F Kennedy International",
            Airport::GeoCoord{40, 38, 23, 'N', 73, 64, 44, 'W'}},

        Airport {"US", "LAX", "Los Angeles International",
            Airport::GeoCoord{33, 56, 33, 'N', 118, 24, 29, 'W'}},
        Airport {"US", "MCO", "Orlando International",
            Airport::GeoCoord{28, 25, 46, 'N', 81, 18, 32, 'W'}},
        Airport {"US", "ORD", "O'Hare International",
            Airport::GeoCoord{41, 58, 43, 'N',  87, 54, 17, 'W'}},
    };
};

double Airport::GeoCoord::calc_distance(const Airport::GeoCoord& gc1,
    const Airport::GeoCoord& gc2, Airport::GeoCoord::Units units)
{
    constexpr double earth_radius_mi = 3959.0;
    constexpr double earth_radius_km = 6371.0;

    // convert DMS to decimal
    auto [lat1, lon1] = gc1.to_decimal();
    auto [lat2, lon2] = gc2.to_decimal();
    lat1 = MTH::deg_to_rad(lat1);
    lon1 = MTH::deg_to_rad(lon1);
    lat2 = MTH::deg_to_rad(lat2);
    lon2 = MTH::deg_to_rad(lon2);

    // calculate central angle
    double t1 = std::sin(lat1) * std::sin(lat2);
    double t2 = std::cos(lat1) * std::cos(lat2);
    double t3 = std::cos(lon1 - lon2);
    double angle = std::acos(t1 + t2 * t3);

    // calculate final distance
    if (units == Airport::GeoCoord::Units::mi)
        return angle * earth_radius_mi;
    else if (units == Airport::GeoCoord::Units::km)
        return angle * earth_radius_km;
    else
        return angle;
}

std::pair<double, double> Airport::GeoCoord::to_decimal() const
{
    // make sure lat/log quads are valid
    if (!Airport::GeoCoord::is_valid_lat(LatQuad))
        throw std::runtime_error("Airport::GeoCoord::to_dec() - bad lat quad");

    if (!Airport::GeoCoord::is_valid_lon(LonQuad))
        throw std::runtime_error("Airport::GeoCoord::to_dec() - bad lon quad");

    // convert DMS to decimal, both lat and lon
    auto dms_to_dec = [](int deg, int min, int sec)
        { return deg + (min * 60.0 + sec) / 3600.0; };

    double lat_dec = dms_to_dec(LatDeg, LatMin, LatSec);
    double lon_dec = dms_to_dec(LonDeg, LonMin, LonSec);

    if (LatQuad == 'S')
        lat_dec = -lat_dec;

    if (LonQuad == 'W')
        lon_dec = -lon_dec;

    return std::make_pair(lat_dec, lon_dec);
}

std::optional<Airport> Airport::get(const std::string& iata_code)
{
    // return Airport that matches iata_code
    auto pred = [iata_code](const Airport& a) { return a.IataCode() == iata_code; };
    auto iter = std::ranges::find_if(c_Airports, pred);
    return (iter != c_Airports.end()) ? std::optional(*iter) : std::nullopt;
}

std::string Airport::get_iata_codes_string()
{
    // build string of all IATA codes
    std::string iata_codes {};

    for (const Airport& airport : c_Airports)
    {
        iata_codes += airport.IataCode();
        iata_codes += ' ';
    }

    return iata_codes;
}

std::vector<Airport> Airport::get_vector_airports()
{
    return c_Airports;
}

std::vector<Airport> Airport::get_vector_airports_shuffle(unsigned int rng_seed)
{
    // get shuffled vector of Airports
    std::vector<Airport> airports {c_Airports};
    std::mt19937 rng {rng_seed};
    std::shuffle(airports.begin(), airports.end(), rng);
    std::shuffle(airports.begin(), airports.end(), rng);
    return airports;
}

std::vector<std::string> Airport::get_vector_iata_codes()
{
    // get vector of all IATA codes
    std::vector<std::string> iata_codes {};
    for (const Airport& airport : c_Airports)
        iata_codes.emplace_back(airport.IataCode());
    return iata_codes;
}

std::vector<std::string> Airport::get_vector_iata_codes_shuffle
    (unsigned int rng_seed)
{
    // get shuffled vector of IATA codes
    std::vector<std::string> iata_codes {get_vector_iata_codes()};
    std::mt19937 rng {rng_seed};
    std::shuffle(iata_codes.begin(), iata_codes.end(), rng);
    std::shuffle(iata_codes.begin(), iata_codes.end(), rng);
    return iata_codes;
}

std::vector<std::string> Airport::get_vector_random_iata_codes(size_t num_codes,
    unsigned int rng_seed)
{
    // generate vector of random IATA codes
    const int dist_max = static_cast<int>(c_Airports.size() - 1);
    std::mt19937 rng {rng_seed};
    std::uniform_int_distribution<int> dist {0, dist_max};

    std::vector<std::string> iata_codes(num_codes);

    for (size_t i = 0; i < iata_codes.size(); ++i)
        iata_codes[i] = c_Airports[dist(rng)].IataCode();
    return iata_codes;
}

std::string Airport::to_str() const
{
    std::string s {};
    auto [lat, lon] = m_Location.to_decimal();

    std::format_to(std::back_inserter(s),
        "[{:2s}, {:3s}, {:s} ({:.4f}, {:.4f})]",
        m_CountryCode, m_IataCode, m_Name, lat, lon);

    return s;
}
