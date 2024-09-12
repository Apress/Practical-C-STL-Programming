//-----------------------------------------------------------------------------
// Point2D.h
//-----------------------------------------------------------------------------

#ifndef POINT2D_H_
#define POINT2D_H_
#include <cmath>
#include <concepts>
#include <format>
#include <ostream>
#include <string>

// Point2D coordinate constraint
template <typename T> concept
PointCoord2D = std::integral<T> || std::floating_point<T>;

template <PointCoord2D T> class Point2D
{
    friend struct std::formatter<Point2D<T>>;

public:
    Point2D() = default;
    Point2D(T x, T y) : m_X {x}, m_Y {y} {};

    // accessors
    T X() const { return m_X; }
    T Y() const { return m_Y; }
    T& X() { return m_X; }
    T& Y() { return m_Y; }

    // operators
    friend bool operator==(const Point2D<T>& p1, const Point2D<T>& p2)
        { return p1.m_X == p2.m_X && p1.m_Y == p2.m_Y; }

    friend bool operator!=(const Point2D<T>& p1, const Point2D<T>& p2)
        { return !(p1 == p2); }

    friend Point2D operator+(const Point2D& p1, const Point2D& p2)
        { return Point2D(p1.m_X + p2.m_X, p1.m_Y + p2.m_Y); }

    friend std::ostream& operator<< (std::ostream& os, const Point2D& p)
    {
        os << p.to_str();
        return os;
    }

    // member functions
    double distance() const
        { return std::hypot(m_X, m_Y); }    // distance from (0, 0)

private:
    std::string to_str() const
    {
        std::string s;
        std::format_to(std::back_inserter(s), "({}, {})", m_X, m_Y);
        return s;
    }

    T m_X {};
    T m_Y {};
};

// class Point2D formatter
template <typename T> struct std::formatter<Point2D<T>> :
    std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const Point2D<T>& point, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", point.to_str()); }
};

#endif
