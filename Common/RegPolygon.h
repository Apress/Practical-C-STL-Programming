//-----------------------------------------------------------------------------
// RegPolygon.h
//-----------------------------------------------------------------------------

#ifndef REG_POLYGON_H_
#define REG_POLYGON_H_
#include <format>
#include <string>
#include <vector>

class RegPolygon
{
    friend struct std::formatter<RegPolygon>;

    static constexpr int NumSidesDef = 3;
    static constexpr double Radius1Def = 1.0;

public:
    RegPolygon() { calc_values(NumSidesDef, Radius1Def); }
    RegPolygon(int num_sides, double radius1) { calc_values(num_sides, radius1); }

    // accessors
    int NumSides() const { return m_NumSides; }
    double Radius1() const { return m_Radius1; };
    double SideLength() const { return m_SideLength; }
    double Radius2() const { return m_Radius2; };
    double Perimeter() const { return m_Perimeter; };
    double VertexAngle() const { return m_VertexAngle; };
    double Area() const { return m_Area; };

    void set(int num_sides, double radius1) { calc_values(num_sides, radius1); }

    // relational operators
    friend auto operator<=>(const RegPolygon& rp1, const RegPolygon& rp2)
        { return rp1.m_Area <=> rp2.m_Area; }

    friend bool operator==(const RegPolygon& rp1, const RegPolygon& rp2)
        { return rp1.m_Area == rp2.m_Area; }

    // public member functions
    static std::vector<RegPolygon> get_random_polygons(size_t num_polygons,
        unsigned int rng_seed1, unsigned int rng_seed2);

    static std::string title_str();

private:
    void calc_values(int num_sides, double radius1);
    std::string to_str() const;

    // RegPolygon attributes
    int m_NumSides {};
    double m_Radius1 {};        // inscribed radius
    double m_SideLength {};
    double m_Radius2 {};        // circumscribed radius
    double m_Perimeter {};
    double m_VertexAngle {};    // labeled theta in figure
    double m_Area {};
};

// class RegPolygon formatter
template <> struct std::formatter<RegPolygon> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const RegPolygon& rp, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", rp.to_str()); }
};

#endif
