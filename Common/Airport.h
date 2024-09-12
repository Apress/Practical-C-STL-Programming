//-----------------------------------------------------------------------------
// Airport.h
//-----------------------------------------------------------------------------

#ifndef AIRPORT_H_
#define AIRPORT_H_
#include <format>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Airport
{
    friend struct std::formatter<Airport>;

public:
    class GeoCoord
    {
    public:
        enum class Units {Ignore, mi, km};

        GeoCoord() = default;

        GeoCoord(int lat_deg, int lat_min, int lat_sec, char lat_quad,
                 int lon_deg, int lon_min, int lon_sec, char lon_quad) :
            LatDeg {lat_deg}, LatMin {lat_min}, LatSec {lat_sec}, LatQuad {lat_quad},
            LonDeg {lon_deg}, LonMin {lon_min}, LonSec {lon_sec}, LonQuad {lon_quad} {}

        // validation functions for latitude and longitude
        static bool is_valid_lat(char quad) {return quad == 'N' || quad == 'S';}
        static bool is_valid_lon(char quad) {return quad == 'E' || quad == 'W';}
        static bool is_valid_lat(double lat) {return lat >= -90.0 && lat <= 90.0;}
        static bool is_valid_lon(double lon) {return lon >= -180.0 && lon <= 180.0;}

        // misc functions (see Airport.cpp)
        static double calc_distance(const GeoCoord& gc1, const GeoCoord& gc2,
            Units units);
        std::pair<double, double> to_decimal() const;

        // latitude and longitude attributes
        int LatDeg {}, LatMin {}, LatSec {};
        char LatQuad {};

        int LonDeg {}, LonMin {}, LonSec {};
        char LonQuad {};
    };

    Airport() = default;
    Airport(const std::string& country_code, const std::string& iata_code,
        const std::string& name, const GeoCoord& location) :
        m_CountryCode {country_code}, m_IataCode {iata_code}, m_Name {name},
        m_Location {location} {};

    // accessors
    std::string CountryCode() const { return m_CountryCode; }
    void CountryCode(const std::string& country_code)
        { m_CountryCode = country_code; }

    std::string IataCode() const { return m_IataCode; }
    void IataCode(const std::string& iata_code)
        { m_IataCode = iata_code; }

    std::string Name() const { return m_Name; }
    void Name(const std::string& name) { m_Name = name; }

    GeoCoord Location() const { return m_Location; }
    void Location(const GeoCoord& location) { m_Location = location; }

    // operators
    friend auto operator<=>(const Airport& ap1, const Airport& ap2)
        { return ap1.m_IataCode <=> ap2.m_IataCode; }

    friend bool operator==(const Airport& ap1, const Airport& ap2)
        { return ap1.m_IataCode == ap2.m_IataCode; }

    // misc functions
    static double calc_distance(const Airport& ap1, const Airport& ap2,
        GeoCoord::Units units)
       { return GeoCoord::calc_distance(ap1.m_Location, ap2.m_Location, units); }

    // static data generation functions
    static std::optional<Airport> get(const std::string& iata_code);
    static std::string get_iata_codes_string();

    static std::vector<Airport> get_vector_airports();
    static std::vector<Airport> get_vector_airports_shuffle
        (unsigned int rng_seed = 42);
    static std::vector<std::string> get_vector_iata_codes();
    static std::vector<std::string> get_vector_iata_codes_shuffle
        (unsigned int rng_seed = 57);

    static std::vector<std::string> get_vector_random_iata_codes(size_t num_codes,
        unsigned int rng_seed = 73);

private:
    std::string to_str() const;

    std::string m_CountryCode {};       // country code (ISO 3166-1 alpha-2)
    std::string m_IataCode {};          // airport code (IATA, 3 letters)
    std::string m_Name {};              // airport name
    GeoCoord m_Location {};             // airport location (lat and lon)
};

// class Airport formatter
template <> struct std::formatter<Airport> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const Airport& ap, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", ap.to_str()); }
};

#endif
