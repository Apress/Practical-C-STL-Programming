//-----------------------------------------------------------------------------
// Ch08_03.h
//-----------------------------------------------------------------------------

#ifndef CH08_03_H_
#define CH08_03_H_
#include <string>
#include <unordered_map>
#include "Common.h"

// type aliases for example Ch08_03
using uno_map_t = std::unordered_map<std::string, std::string>;
using uno_map_hf_t = std::unordered_map<std::string, std::string,
        size_t(*)(const std::string&)>;

// Ch08_03_ex.cpp
extern void Ch08_03_ex();

// Ch08_03_misc.cpp
uno_map_t get_airports(int id);
void get_airports(uno_map_hf_t& map, int id);
void print_buckets(const char* msg, const uno_map_hf_t& map);

#endif
