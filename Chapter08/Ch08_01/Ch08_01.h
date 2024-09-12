//-----------------------------------------------------------------------------
// Ch08_01.h
//-----------------------------------------------------------------------------

#ifndef CH08_01_H_
#define CH08_01_H_
#include <string>
#include <unordered_set>
#include "Common.h"
#include "HtmlColor.h"

// type aliases for unordered_set of HtmlColor values
using uno_set_str_t = std::unordered_set<std::string>;
using uno_set_hc_t = std::unordered_set<HtmlColor, size_t(*)(const HtmlColor&)>;

// Ch08_01_misc.cpp
void print_buckets(const char* msg, const uno_set_str_t& strings);
void print_buckets(const char* msg, const uno_set_hc_t& colors);

// Ch08_01_ex.cpp
extern void Ch08_01_ex();

#endif

