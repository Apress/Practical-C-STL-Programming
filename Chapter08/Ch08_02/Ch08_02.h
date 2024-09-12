//-----------------------------------------------------------------------------
// Ch08_02.h
//-----------------------------------------------------------------------------

#ifndef CH08_02_H_
#define CH08_02_H_
#include <unordered_set>
#include "Common.h"
#include "HtmlColor.h"

// type alias for example Ch08_02
using uno_mset_t = std::unordered_multiset<HtmlColor,
    size_t(*)(const HtmlColor&)>;

// Ch08_02_ex.cpp
extern void Ch08_02_ex();

// Ch08_02_misc.cpp
extern void print_buckets(const char* msg, const uno_mset_t& colors);
#endif
