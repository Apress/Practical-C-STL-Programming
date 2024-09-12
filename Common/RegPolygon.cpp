//-----------------------------------------------------------------------------
// RegPolygon.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <iomanip>
#include <numbers>
#include <ostream>
#include <random>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "RegPolygon.h"
#include "MTH.h"

std::vector<RegPolygon> RegPolygon::get_random_polygons(size_t num_polygons,
        unsigned int rng_seed1, unsigned int rng_seed2)
{
    std::mt19937 rng_num_sides {rng_seed1};
    std::uniform_int_distribution<int> dist_num_sides {3, 30};

    std::mt19937 rng_radius {rng_seed2};
    std::uniform_real_distribution<double> dist_radius {0.5, 25.0};

    std::vector<RegPolygon> polygons {};

    for (size_t i = 0; i < num_polygons; ++i)
    {
        int num_sides = dist_num_sides(rng_num_sides);
        double radius1 = dist_radius(rng_radius);

        polygons.emplace_back(num_sides, radius1);
    }

    return polygons;
}

std::string RegPolygon::title_str()
{
    static std::string s {};

    if (s.empty())
    {
        s += "Sides     ";
        s += "Radius1     ";
        s += "SideLen    ";
        s += "Radius2     ";
        s += "Perim     ";
        s += "VerAng       ";
        s += "Area\n";
        s += std::string(74, '=');
    }

    return s;
}

void RegPolygon::calc_values(int num_sides, double radius1)
{
    using namespace std::numbers;

    // validate arguments
    static std::string s1 { "RegPolygon::CalcValues(): invalid value - " };

    if (num_sides < 3)
        throw std::runtime_error(s1 + "'num_sides'");

    if (radius1 <= 0.0)
        throw std::runtime_error(s1 + "'radius1'");

    // calculate polygon parameters
    m_NumSides = num_sides;
    m_Radius1 = radius1;

    m_SideLength = 2.0 * m_Radius1 * std::tan(MTH::deg_to_rad(180.0 / m_NumSides));
    m_Perimeter = m_NumSides * m_SideLength;
    m_VertexAngle = (m_NumSides - 2) / static_cast<double>(m_NumSides) * 180.0;

    m_Radius2 = 0.5 * m_SideLength
                    * MTH::csc(MTH::deg_to_rad(180.0 / m_NumSides));

    m_Area = m_NumSides * m_Radius1 * m_Radius1
                        * std::tan(MTH::deg_to_rad(180.0 / m_NumSides));
}

std::string RegPolygon::to_str() const
{
    std::string s {};
    std::format_to(std::back_inserter(s), "[{:4d}, ", m_NumSides);
    std::format_to(std::back_inserter(s), "{:9.3f} | ", m_Radius1);
    std::format_to(std::back_inserter(s), "{:9.3f}, ", m_SideLength);
    std::format_to(std::back_inserter(s), "{:9.3f}, ", m_Radius2);
    std::format_to(std::back_inserter(s), "{:9.3f}, ", m_Perimeter);
    std::format_to(std::back_inserter(s), "{:9.3f}, ", m_VertexAngle);
    std::format_to(std::back_inserter(s), "{:9.3f}]", m_Area);

    return s;
}
