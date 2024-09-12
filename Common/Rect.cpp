//-----------------------------------------------------------------------------
// Rect.cpp
//-----------------------------------------------------------------------------

#include <format>
#include <ostream>
#include <string>
#include "Rect.h"
#include "Common.h"

Rect::~Rect()
{
//  std::println("Rect::~Rect()");    // for demo purposes only
}

std::ostream& operator<<(std::ostream& os, const Rect& rect)
{
    os << rect.to_str();
    return os;
}

std::string Rect::to_str() const
{
    std::string s{};
    std::format_to(std::back_inserter(s), "[({:d}, {:d}, {:d}, {:d}) ",
        m_X, m_Y, m_W, m_H);
    std::format_to(std::back_inserter(s), "{:d}]", area());
    return s;
}
