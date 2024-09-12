//-----------------------------------------------------------------------------
// Ch08_04_misc.cpp
//-----------------------------------------------------------------------------

#include "Ch08_04.h"

uno_mmap_t get_airports()
{
    // create unordered multimap using country code as key
    uno_mmap_t airports {};

    airports.emplace("AU", Airport {"MEL", -37.6733, 144.8433, "Melbourne"});
    airports.emplace("AU", Airport {"SYD", -33.9461, 151.1772, "Sydney"});
    airports.emplace("CA", Airport {"YYC", 51.1225, -114.0133, "Calgary"});
    airports.emplace("CA", Airport {"YVR", 49.1947, -123.1839, "Vancouver"});
    airports.emplace("CA", Airport {"YYZ", 53.3100, -113.5794, "Toronto"});
    airports.emplace("CN", Airport {"PEK", 40.0725, 116.5975, "Beijing"});
    airports.emplace("CN", Airport {"PVG", 31.1433, 121.8053, "Shanghai"});
    airports.emplace("CH", Airport {"ZRH", 47.4314, 8.5492, "Zurich"});
    airports.emplace("CL", Airport {"SCL", -33.3928, -70.7911, "Santiago"});
    airports.emplace("DE", Airport {"BER", 52.3667, 13.5033, "Berlin"});
    airports.emplace("DE", Airport {"FRA", 50.0333, 8.5706, "Frankfurt"});
    airports.emplace("DE", Airport {"MUN", 48.3539, 11.7861, "Munich"});
    airports.emplace("FR", Airport {"CDG", 49.0097, 2.5478, "Paris"});
    airports.emplace("FR", Airport {"TLS", 43.6350, 1.3678, "Toulouse"});
    airports.emplace("GB", Airport {"GLA", 55.8719, -4.4331, "Glasgow"});
    airports.emplace("GB", Airport {"LHR", 51.4775, -0.4614, "London"});
    airports.emplace("JP", Airport {"KIX", 34.4306, 135.2303, "Osaka"});
    airports.emplace("JP", Airport {"NRT", 35.7653, 140.3856, "Tokyo"});
    airports.emplace("NO", Airport {"BGO", 60.2936, 5.2181, "Bergen"});
    airports.emplace("NO", Airport {"OSL", 60.2028, 11.0839, "Oslo"});
    airports.emplace("SE", Airport {"ARN", 59.5019, 17.9186, "Stockholm"});
    airports.emplace("US", Airport {"JFK", 40.6397, -74.0789, "New York"});
    airports.emplace("US", Airport {"LAX", 33.9425, -118.4081, "Los Angeles"});
    airports.emplace("US", Airport {"ORD", 41.9786, -87.9047, "Chicago"});

    return airports;
}

void print_buckets(const char* msg, const uno_mmap_t& airports)
{
    // print stats
    std::println("{:s}", msg);
    std::print("size: {}  ", airports.size());
    std::print("bucket_count: {}  ", airports.bucket_count());
    std::println("load_factor: {}\n", airports.load_factor());

    // print buckets
    for (size_t i {0}; i < airports.bucket_count(); ++i)
    {
        if (airports.bucket_size(i) != 0)
        {
            std::println("bucket {:2d}:", i);

            for (auto iter = airports.begin(i); iter != airports.end(i); ++iter)
            {
                const Airport& ap = iter->second;

                std::println("  {:2s} | {:3s} [{:9.4f}, {:9.4f}] {:40s}",
                    iter->first, ap.IataCode, ap.Latitude, ap.Longitude, ap.City);
            }
        }
    }

    std::println("");
}
