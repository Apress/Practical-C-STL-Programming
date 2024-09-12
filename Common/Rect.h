//-----------------------------------------------------------------------------
// Rect.h
//-----------------------------------------------------------------------------

#ifndef RECT_H_
#define RECT_H_
#include <format>
#include <ostream>
#include <string>

class Rect
{
    friend struct std::formatter<Rect>;

public:
    // constructors
    Rect() = default;

    Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
        m_X(x), m_Y(y), m_W(w), m_H(h) {}

    ~Rect();

    // accessors
    unsigned int X() const { return m_X; }
    unsigned int Y() const { return m_Y; }
    unsigned int W() const { return m_W; }
    unsigned int H() const { return m_H; }

    unsigned int& X() { return m_X; }
    unsigned int& Y() { return m_Y; }
    unsigned int& W() { return m_W; }
    unsigned int& H() { return m_H; }

    void set(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
        { m_X = x; m_Y = y; m_W = w; m_H = h; }

    // public member functions
    unsigned int area() const { return m_W * m_H; }

    // operators (see Rect.cpp)
    friend std::ostream& operator<<(std::ostream& os, const Rect& rect);

private:
    std::string to_str() const;

    // private attributes
    unsigned int m_X {};
    unsigned int m_Y {};
    unsigned int m_W {};
    unsigned int m_H {};
};

// relational operators
inline auto operator<=>(const Rect& rect1, const Rect& rect2)
    { return rect1.area() <=> rect2.area(); }

inline bool operator==(const Rect& rect1, const Rect& rect2)
    { return rect1.area() == rect2.area(); }

// class Rect formatter
template <> struct std::formatter<Rect> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const Rect& rect, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", rect.to_str()); }
};

#endif
