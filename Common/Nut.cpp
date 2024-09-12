//-----------------------------------------------------------------------------
// Nut.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <format>
#include <stdexcept>
#include <string>
#include <vector>
#include "Nut.h"

namespace
{
    const std::array<Nut, 7> s_Nuts
    {
        // order of objects below must match enum Nut::Type (see Nut.h)
        Nut {"Almond", 2423, 21.6f, 49.9f, 21.2f},
        Nut {"Cashew", 553, 30.19f, 43.85f, 18.22f},
        Nut {"Chestnut", 820, 28.0f, 1.3f, 1.6f},
        Nut {"Hazelnut", 2629, 16.7f, 60.75f, 15.95f},
        Nut {"Pecan", 2889, 13.86f, 71.97f, 9.17f},
        Nut {"Pistachio", 2351, 27.51f, 45.39f, 20.27f},
        Nut {"Walnut", 2738, 13.71f, 65.21f, 15.23f},
    };
}

Nut Nut::get_nut(Nut::Type type)
{
    auto t = static_cast<unsigned int>(type);

    if (t >= s_Nuts.size())
        throw std::runtime_error("Nut::get_nut() - invalid type");

    return s_Nuts[t];
}

std::string Nut::get_type_string(Nut::Type type)
{
    auto t = static_cast<unsigned int>(type);

    if (t >= s_Nuts.size())
        throw std::runtime_error("Nut::get_type_string() - invalid type");

    return s_Nuts[t].m_Name;
}

std::vector<Nut> Nut::get_vector()
{
    std::vector<Nut> nuts(s_Nuts.begin(), s_Nuts.end());
    return nuts;
}

std::string Nut::to_str() const
{
    std::string s {};
    std::format_to(std::back_inserter(s), "[{:<13s}", m_Name);
    std::format_to(std::back_inserter(s), "{:>11d}", m_EnergyKj);
    std::format_to(std::back_inserter(s), "{:>11d}", m_EnergyKcal);
    std::format_to(std::back_inserter(s), "{:>11.2f}", m_Carbohydrates);
    std::format_to(std::back_inserter(s), "{:>11.2f}", m_Fat);
    std::format_to(std::back_inserter(s), "{:>11.2f}]", m_Protein);

    return s;
}

std::string Nut::title_str()
{
    std::string s {};
    std::format_to(std::back_inserter(s), "\n{:<13s}", "Name");
    std::format_to(std::back_inserter(s), "{:>11s}", "EnKj");
    std::format_to(std::back_inserter(s), "{:>12s}", "EnKcal");
    std::format_to(std::back_inserter(s), "{:>11s}", "Carbs");
    std::format_to(std::back_inserter(s), "{:>11s}", "Fat");
    std::format_to(std::back_inserter(s), "{:>12s}\n", "Protein");

    s += std::string(72, '=');
    s += '\n';
    return s;
}
