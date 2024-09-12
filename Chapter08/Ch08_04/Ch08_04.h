//-----------------------------------------------------------------------------
// Ch08_04.h
//-----------------------------------------------------------------------------

#ifndef CH08_04_H_
#define CH08_04_H_
#include <string>
#include <string_view>
#include <unordered_map>
#include "Common.h"

struct Airport
{
    std::string_view IataCode {};
    double Latitude {};
    double Longitude {};
    std::string City {};
};

// unordered_multimap<country code, Airport>
using uno_mmap_t = std::unordered_multimap<std::string_view, Airport>;

// Ch08_04_ex.cpp
extern void Ch08_04_ex();

// Ch08_04_misc.cpp
extern uno_mmap_t get_airports();
extern void print_buckets(const char* msg, const uno_mmap_t& airports);

#endif
