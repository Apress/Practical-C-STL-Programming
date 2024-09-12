//-----------------------------------------------------------------------------
// RGB.h
//-----------------------------------------------------------------------------

#ifndef RGB_H_
#define RGB_H_
#include <compare>
#include <cstdint>
#include <format>
#include <ostream>
#include <string>

class RGB
{
    friend struct std::formatter<RGB>;

public:
    RGB() = default;
    RGB(uint8_t r, uint8_t g, uint8_t b) : m_R{r}, m_G{g}, m_B{b} {};

    RGB(uint32_t color)
    {
        m_B = color & 0xFF;
        m_G = (color >> 8) & 0xFF;
        m_R = (color >> 16) & 0xFF;
    }

    // accessors
    uint8_t R() const { return m_R; }
    uint8_t B() const { return m_B; }
    uint8_t G() const { return m_G; }
    uint8_t& R() { return m_R; };
    uint8_t& G() { return m_G; };
    uint8_t& B() { return m_B; };
    uint32_t ValUint() const { return (m_R << 16) | (m_G << 8) | m_B; }

    // operators
    friend auto operator<=>(const RGB& rgb1, const RGB& rgb2)
        { return rgb1.ValUint() <=> rgb2.ValUint(); }

    friend bool operator==(const RGB& rgb1, const RGB& rgb2)
        { return rgb1.ValUint() == rgb2.ValUint(); }

    friend std::ostream& operator<<(std::ostream& os, const RGB& rgb)
        {os << rgb.to_str(); return os;}

private:
    std::string to_str(bool use_hex = true) const;

    uint8_t m_R {};
    uint8_t m_G {};
    uint8_t m_B {};
    uint8_t m_A {};     // reserved for future use
};

// class RGB formatter
template <> struct std::formatter<RGB> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const RGB& rgb, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", rgb.to_str()); }
};

#endif
