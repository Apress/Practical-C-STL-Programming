//-----------------------------------------------------------------------------
// Ch21_03.h
//-----------------------------------------------------------------------------

#ifndef CH21_03_H_
#define CH21_03_H_
#include "Common.h"
#include <string>
#include <vector>
#include "Airport.h"

// Ch21_03_ex.cpp
extern void Ch21_03_ex();

// Ch201_03_misc.cpp
extern std::vector<Airport> get_random_airports(size_t n, unsigned int rng_seed);

extern std::vector<double> calc_distance_matrix(const std::vector<Airport>& airports,
  Airport::GeoCoord::Units units);

extern void print_distance_matrix(const std::string& title,
  const std::vector<Airport>& airports, const std::vector<double>& distance_matrix);

#endif
