//-----------------------------------------------------------------------------
// HtmlColor.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <cmath>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include "HtmlColor.h"
#include "MTH.h"

// vector s_HtmlColors contains 141 HtmlColors
const std::vector<HtmlColor> HtmlColor::s_HtmlColors
{
    HtmlColor{"AliceBlue",              0xf0f8ff},
    HtmlColor{"AntiqueWhite",           0xfaebd7},
    HtmlColor{"Aqua",                   0x00ffff},
    // colors AquaMarine - White excluded from listing

    HtmlColor{"AquaMarine",             0x7fffd4},
    HtmlColor{"Azure",                  0xf0ffff},
    HtmlColor{"Beige",                  0xf5f5dc},
    HtmlColor{"Bisque",                 0xffe4c4},
    HtmlColor{"Black",                  0x000000},
    HtmlColor{"BlanchedAlmond",         0xffebcd},
    HtmlColor{"Blue",                   0x0000ff},
    HtmlColor{"BlueViolet",             0x8a2be2},
    HtmlColor{"Brown",                  0xa52a2a},
    HtmlColor{"Burlywood",              0xdeb887},
    HtmlColor{"CadetBlue",              0x5f9ea0},
    HtmlColor{"Chartreuse",             0x7fff00},
    HtmlColor{"Chocolate",              0xd2691e},
    HtmlColor{"Coral",                  0xff7f50},
    HtmlColor{"CornFlowerBlue",         0x6495ed},
    HtmlColor{"Cornsilk",               0xfff8dc},
    HtmlColor{"Crimson",                0xdc143c},
    HtmlColor{"Cyan",                   0x00ffff},
    HtmlColor{"DarkBlue",               0x00008b},
    HtmlColor{"DarkCyan",               0x008b8b},
    HtmlColor{"DarkGoldenrod",          0xb8860b},
    HtmlColor{"DarkGray",               0xa9a9a9},
    HtmlColor{"DarkGreen",              0x006400},
    HtmlColor{"DarkKhaki",              0xbdb76b},
    HtmlColor{"DarkMagenta",            0x8b008b},
    HtmlColor{"DarkOliveGreen",         0x556b2f},
    HtmlColor{"DarkOrange",             0xff8c00},
    HtmlColor{"DarkOrchid",             0x9932cc},
    HtmlColor{"DarkRed",                0x8b0000},
    HtmlColor{"DarkSalmon",             0xe9967a},
    HtmlColor{"DarkSeaGreen",           0x8fbc8f},
    HtmlColor{"DarkSlateBlue",          0x483d8b},
    HtmlColor{"DarkSlateGray",          0x2f4f4f},
    HtmlColor{"DarkTurquoise",          0x00ced1},
    HtmlColor{"DarkViolet",             0x9400d3},
    HtmlColor{"DeepPink",               0xff1493},
    HtmlColor{"DeepSkyBlue",            0x00bfff},
    HtmlColor{"DimGray",                0x696969},
    HtmlColor{"DodgerBlue",             0x1e90ff},
    HtmlColor{"Firebrick",              0xb22222},
    HtmlColor{"FloralWhite",            0xfffaf0},
    HtmlColor{"ForestGreen",            0x228b22},
    HtmlColor{"Fuchsia",                0xff00ff},
    HtmlColor{"Gainsboro",              0xdcdcdc},
    HtmlColor{"GhostWhite",             0xf8f8ff},
    HtmlColor{"Gold",                   0xffd700},
    HtmlColor{"Goldenrod",              0xdaa520},
    HtmlColor{"Gray",                   0x808080},
    HtmlColor{"Green",                  0x008000},
    HtmlColor{"GreenYellow",            0xadff2f},
    HtmlColor{"Honeydew",               0xf0fff0},
    HtmlColor{"HotPink",                0xff69b4},
    HtmlColor{"IndianRed",              0xcd5c5c},
    HtmlColor{"Indigo",                 0x4b0082},
    HtmlColor{"Ivory",                  0xfffff0},
    HtmlColor{"Khaki",                  0xf0e68c},
    HtmlColor{"Lavender",               0xe6e6fa},
    HtmlColor{"LavenderBlush",          0xfff0f5},
    HtmlColor{"LawnGreen",              0x7cfc00},
    HtmlColor{"LemonChiffon",           0xfffacd},
    HtmlColor{"LightBlue",              0xadd8e6},
    HtmlColor{"LightCoral",             0xf08080},
    HtmlColor{"LightCyan",              0xe0ffff},
    HtmlColor{"LightGoldenrodYellow",   0xfafad2},
    HtmlColor{"LightGray",              0xd3d3d3},
    HtmlColor{"LightGreen",             0x90ee90},
    HtmlColor{"LightPink",              0xffb6c1},
    HtmlColor{"LightSalmon",            0xffa07a},
    HtmlColor{"LightSeaGreen",          0x20b2aa},
    HtmlColor{"LightSkyBlue",           0x87cefa},
    HtmlColor{"LightSlateGray",         0x778899},
    HtmlColor{"LightSteelBlue",         0xb0c4de},
    HtmlColor{"LightYellow",            0xffffe0},
    HtmlColor{"Lime",                   0x00ff00},
    HtmlColor{"LimeGreen",              0x32cd32},
    HtmlColor{"Linen",                  0xfaf0e6},
    HtmlColor{"Magenta",                0xff00ff},
    HtmlColor{"Maroon",                 0x800000},
    HtmlColor{"MediumAquamarine",       0x66cdaa},
    HtmlColor{"MediumBlue",             0x0000cd},
    HtmlColor{"MediumOrchid",           0xba55d3},
    HtmlColor{"MediumPurple",           0x9370db},
    HtmlColor{"MediumSeaGreen",         0x3cb371},
    HtmlColor{"MediumSlateBlue",        0x7b68ee},
    HtmlColor{"MediumSpringGreen",      0x00fa9a},
    HtmlColor{"MediumTurquoise",        0x48d1cc},
    HtmlColor{"MediumVioletRed",        0xc71585},
    HtmlColor{"MidnightBlue",           0x191970},
    HtmlColor{"MintCream",              0xf5fffa},
    HtmlColor{"MistyRose",              0xffe4e1},
    HtmlColor{"Moccasin",               0xffe4b5},
    HtmlColor{"NavajoWhite",            0xffdead},
    HtmlColor{"Navy",                   0x000080},
    HtmlColor{"OldLace",                0xfdf5e6},
    HtmlColor{"Olive",                  0x808000},
    HtmlColor{"OliveDrab",              0x6b8e23},
    HtmlColor{"Orange",                 0xffa500},
    HtmlColor{"OrangeRed",              0xff4500},
    HtmlColor{"Orchid",                 0xda70d6},
    HtmlColor{"PaleGoldenrod",          0xeee8aa},
    HtmlColor{"PaleGreen",              0x98fb98},
    HtmlColor{"PaleTurquoise",          0xafeeee},
    HtmlColor{"PaleVioletRed",          0xdb7093},
    HtmlColor{"PapayaWhip",             0xffefd5},
    HtmlColor{"PeachPuff",              0xffdab9},
    HtmlColor{"Peru",                   0xcd853f},
    HtmlColor{"Pink",                   0xffc0cb},
    HtmlColor{"Plum",                   0xdda0dd},
    HtmlColor{"PowderBlue",             0xb0e0e6},
    HtmlColor{"Purple",                 0x800080},
    HtmlColor{"RebeccaPurple",          0x663399},
    HtmlColor{"Red",                    0xff0000},
    HtmlColor{"RosyBrown",              0xbc8f8f},
    HtmlColor{"RoyalBlue",              0x4169e1},
    HtmlColor{"SaddleBrown",            0x8b4513},
    HtmlColor{"Salmon",                 0xfa8072},
    HtmlColor{"SandyBrown",             0xf4a460},
    HtmlColor{"SeaGreen",               0x2e8b57},
    HtmlColor{"Seashell",               0xfff5ee},
    HtmlColor{"Sienna",                 0xa0522d},
    HtmlColor{"Silver",                 0xc0c0c0},
    HtmlColor{"SkyBlue",                0x87ceeb},
    HtmlColor{"SlateBlue",              0x6a5acd},
    HtmlColor{"SlateGray",              0x708090},
    HtmlColor{"Snow",                   0xfffafa},
    HtmlColor{"SpringGreen",            0x00ff7f},
    HtmlColor{"SteelBlue",              0x4682b4},
    HtmlColor{"Tan",                    0xd2b48c},
    HtmlColor{"Teal",                   0x008080},
    HtmlColor{"Thistle",                0xd8bfd8},
    HtmlColor{"Tomato",                 0xff6347},
    HtmlColor{"Turquoise",              0x40e0d0},
    HtmlColor{"Violet",                 0xee82ee},
    HtmlColor{"Wheat",                  0xf5deb3},
    HtmlColor{"White",                  0xffffff},

    HtmlColor{"WhiteSmoke",             0xf5f5f5},
    HtmlColor{"Yellow",                 0xffff00},
    HtmlColor{"YellowGreen",            0x9acd32},
};

// LUT functions
HtmlColor HtmlColor::get(size_t index)
{
    if (index >= s_HtmlColors.size())
        throw std::runtime_error("HtmlColor::get() - invalid index");

    return s_HtmlColors[index];
}

std::string HtmlColor::get_name(size_t index)
{
    if (index >= s_HtmlColors.size())
        throw std::runtime_error("HtmlColor::get_name() - invalid index");

    return s_HtmlColors[index].m_Name;
}

std::vector<HtmlColor> HtmlColor::get_vector()
{
    std::vector<HtmlColor> colors {};
    std::copy(s_HtmlColors.begin(), s_HtmlColors.end(), std::back_inserter(colors));

    return colors;
}

std::vector<HtmlColor> HtmlColor::get_vector(const std::vector<size_t>& indices)
{
    std::vector<HtmlColor> colors {};

    for (auto index : indices)
        colors.push_back(get(index));

    return colors;
}

std::vector<HtmlColor> HtmlColor::get_vector(size_t vec_size,
    bool unique_vals, unsigned int rng_seed)
{
    if (unique_vals && vec_size > s_HtmlColors.size())
        throw std::runtime_error("HtmlColor::get_vector_random() - bad args");

    std::mt19937 rng {rng_seed};
    std::uniform_int_distribution<size_t> dist {0, s_HtmlColors.size() - 1};

    std::vector<HtmlColor> colors {};

    while (colors.size() < vec_size)
    {
        const HtmlColor& color = s_HtmlColors[dist(rng)];

        if (unique_vals)
        {
            auto iter = std::find(std::begin(colors), std::end(colors), color);

            if (iter != std::end(colors))
                continue;
        }

        colors.push_back(color);
    }

    return colors;
}

std::vector<std::string>
HtmlColor::get_vector_names_only(const std::vector<size_t>& indices)
{
    std::vector<std::string> color_names {};

    for (auto index : indices)
        color_names.push_back(get(index).Name());

    return color_names;
}

// Private member functions
HtmlColor::HSI HtmlColor::get_hsi() const
{
    // See Gonzalez and Woods, "Digital Image Processing (4th edition)",
    // p. 541 - 546 for more information about the RGB to HSI algorithm
    // used below.
 
    HSI hsi;
    constexpr float eps {0.00001f};         // prevents division by zero
    float r = m_ValRgb.R / 255.0f;
    float g = m_ValRgb.G / 255.0f;
    float b = m_ValRgb.B / 255.0f;

    // Note: theta_deg = 90.0 when r, g, b are equal
    float theta_num = 0.5f * ((r - g) + (r - b));
    float theta_den = std::sqrt((r - g) * (r - g) + (r - b) * (g - b));
    float theta_rad = std::acos(theta_num / (theta_den + eps));
    float theta_deg = MTH::rad_to_deg(theta_rad);
    hsi.H = (b > g) ? 360.0f - theta_deg : theta_deg;

    // Note: saturation is 0 when r, g, b are equal
    float min_rgb = std::min(r, std::min(g, b));
    hsi.S = 1.0f - (3.0f / (r + g + b + eps)) * min_rgb;

    hsi.I = (r + g + b) / 3.0f;
    return hsi;
}

std::string HtmlColor::to_str(bool use_hex) const
{
    std::string s {};
    std::format_to(std::back_inserter(s), "[{:20s} ", m_Name);

    if (use_hex)
    {
        uint32_t c = m_ValRgb.get_uint();
        std::format_to(std::back_inserter(s), "0x{:06X}]", c);
    }
    else
    {
        unsigned int r = m_ValRgb.R;
        unsigned int g = m_ValRgb.G;
        unsigned int b = m_ValRgb.B;
        std::format_to(std::back_inserter(s), "({:3d},{:3d},{:3d})", r, g, b);
    }

    return s;
}
