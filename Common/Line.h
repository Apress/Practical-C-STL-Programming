//-----------------------------------------------------------------------------
// Line.h
//-----------------------------------------------------------------------------

#ifndef LINE_H_
#define LINE_H_
#include <cmath>
#include <compare>
#include <concepts>
#include <format>
#include <limits>
#include <ostream>
#include <string>

// Line coordinate constraint
template <typename T> concept
LineCoord = std::integral<T> || std::floating_point<T>;

// simple line class
template <LineCoord T> class Line
{
    friend struct std::formatter<Line<T>>;

public:
    Line() = default;
    Line(T x0, T y0, T x1, T y1) :
        m_X0{x0}, m_Y0{y0}, m_X1{x1}, m_Y1{y1} {}; 

    // accessors
    T X0() const { return m_X0; }
    T Y0() const { return m_Y0; }
    T X1() const { return m_X1; }
    T Y1() const { return m_Y1; }

    T& X0() { return m_X0; }
    T& Y0() { return m_Y0; }
    T& X1() { return m_X1; }
    T& Y1() { return m_Y1; }

    friend std::ostream& operator<<(std::ostream& os, const Line<T>& line)
    {
        os << line.to_str();
        return os;
    }

    double length() const
    {
        double dx = static_cast<double>(m_X1) - m_X0;
        double dy = static_cast<double>(m_Y1) - m_Y0;
        return std::hypot(dx, dy);
    }

    double slope(double epsilon = 1.0e-15) const
    {
        double dx = static_cast<double>(m_X1) - m_X0;
        double dy = static_cast<double>(m_Y1) - m_Y0;

        return std::fabs(dx) > epsilon ?
            dy / dx : std::numeric_limits<double>::quiet_NaN();
    }

private:
    std::string to_str() const
    {
        std::string s{};
        std::format_to(std::back_inserter(s), "[({}, {}, ", m_X0, m_Y0);
        std::format_to(std::back_inserter(s), "{}, {}) | ", m_X1, m_Y1);
        std::format_to(std::back_inserter(s), "({:.4f}, ", length());
        std::format_to(std::back_inserter(s), "{:.4f})]", slope());

        return s;
    }

    // attributes
    T m_X0 {};
    T m_Y0 {};
    T m_X1 {};
    T m_Y1 {};
};

// non-member relational operators
template <LineCoord T>
auto operator<=>(const Line<T>& line1, const Line<T>& line2)
{
    return line1.length() <=> line2.length();
}

template <LineCoord T>
bool operator==(const Line<T>& line1, const Line<T>& line2)
{
    return line1.length() == line2.length();
}

// class Line formatter
template <typename T> struct std::formatter<Line<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(Line<T> line, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", line.to_str()); }
};

#endif
