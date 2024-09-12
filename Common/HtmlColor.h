//-----------------------------------------------------------------------------
// HtmlColor.h
//-----------------------------------------------------------------------------

#ifndef HTML_COLOR_H_
#define HTML_COLOR_H_
#include <cstdint>
#include <format>
#include <functional>
#include <ostream>
#include <string>
#include <vector>

class HtmlColor
{
    friend struct std::formatter<HtmlColor>;
    static const std::vector<HtmlColor> s_HtmlColors;   // all HTML colors

public:

    // simple structs for RGB and HSI values
    struct RGB
    {
        RGB() = default;
        RGB(uint8_t r, uint8_t g, uint8_t b) :
            R {r}, G {g}, B {b} {};
        RGB(uint32_t c)
            { B = c & 0xFF; G = (c >> 8) & 0xFF; R = (c >> 16) & 0xFF; }
        uint32_t get_uint() const
            { return static_cast<uint32_t>(B) | (G << 8) | (R << 16); }

        uint8_t R {};       // red
        uint8_t G {};       // green
        uint8_t B {};       // blue
    };

    struct HSI
    {
        HSI() = default;

        float H {};         // hue
        float S {};         // saturation
        float I {};         // intensity
    };

    // hash function bucket count
    static constexpr size_t hash_func_bucket_count {50};

    // hash function for unordered containers
    static size_t hash_func(const HtmlColor& color)
        { return color.m_ValRgb.get_uint() % hash_func_bucket_count; }

    // hash function for std::searcher (uses default for std::string)
    static size_t hash_func_searcher(const HtmlColor& html_color)
        { return std::hash<std::string>{} (html_color.m_Name); }

    HtmlColor() = default;
    HtmlColor(const HtmlColor& color) :
        m_Name {color.m_Name}, m_ValRgb {color.m_ValRgb} {};

    HtmlColor(const std::string& name, uint8_t r, uint8_t g, uint8_t b) :
        m_Name {name}, m_ValRgb {RGB(r, g, b)} {};

    HtmlColor(const std::string& name, uint32_t val) :
        m_Name {name}, m_ValRgb {RGB(val)} {};

    HtmlColor(const std::string& name, RGB val_rgb) :
        m_Name {name}, m_ValRgb {val_rgb} {};
   
    // accessors
    std::string Name() const { return m_Name; }

    RGB ValRgb() const { return m_ValRgb; };
    uint8_t R() const { return m_ValRgb.R; }
    uint8_t G() const { return m_ValRgb.G; }
    uint8_t B() const { return m_ValRgb.B; }

    uint32_t ValUint() const { return m_ValRgb.get_uint(); };

    HSI ValHSI() const { return get_hsi(); };
    float H() const { return get_hsi().H; }
    float S() const { return get_hsi().S; }
    float I() const { return get_hsi().I; }

    // operators
    HtmlColor& operator=(const HtmlColor& c1)
        {m_Name = c1.m_Name; m_ValRgb = c1.m_ValRgb; return *this; }

    friend auto operator<=>(const HtmlColor& c1, const HtmlColor& c2)
        { return c1.m_Name <=> c2.m_Name; };

    friend bool operator==(const HtmlColor& c1, const HtmlColor& c2)
        { return c1.m_Name == c2.m_Name; };

    friend std::ostream& operator<<(std::ostream& os, const HtmlColor& color)
        { os << color.to_str(); return os; }

    // miscellaneous HtmlColor functions (see HtmlColor.cpp)
    static HtmlColor get(size_t index);
    static std::string get_name(size_t index);

    static std::vector<HtmlColor> get_vector();
    static std::vector<HtmlColor> get_vector(const std::vector<size_t>& indices);

    static std::vector<HtmlColor> get_vector(size_t vec_size,
        bool unique_vals, unsigned int rng_seed);

    static std::vector<std::string>
        get_vector_names_only(const std::vector<size_t>& indices);

    static size_t num_colors() { return s_HtmlColors.size(); }

private:
    HSI get_hsi() const;
    std::string to_str(bool use_hex = true) const;

    std::string m_Name {"?"};   // color name
    RGB m_ValRgb {};            // color value
};

// HtmlColor formatter
template <> struct std::formatter<HtmlColor> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const HtmlColor& color, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", color.to_str()); }
};

#endif
