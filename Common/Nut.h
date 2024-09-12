//-----------------------------------------------------------------------------
// Nut.h
//-----------------------------------------------------------------------------

#ifndef NUT_H_
#define NUT_H_
#include <format>
#include <ostream>
#include <string>
#include <vector>

class Nut
{
    friend struct std::formatter<Nut>;

public:
    // order of elements in enum Type must match elements in s_Nuts (see Nut.cpp)
    enum class Type : unsigned int
        {Almond, Cashew, Chestnut, Hazelnut, Pecan, Pistachio, Walnut};

    // constructors
    Nut() = default;

    Nut(const std::string& name, unsigned int energy_kj, float carbohydrates,
        float fat, float protein) : m_Name {name}, m_EnergyKj {energy_kj},
        m_Carbohydrates {carbohydrates}, m_Fat {fat}, m_Protein {protein}
    {
        m_EnergyKcal = static_cast<unsigned int>(m_EnergyKj * 0.239f + 0.5f);
    }

    // accessors
    std::string Name() const { return m_Name; }
    unsigned int EnergyKj() const { return m_EnergyKj; }
    unsigned int EnergyKcal() const { return m_EnergyKcal; }
    float Carbohydrates() const { return m_Carbohydrates; }
    float Fat() const { return m_Fat; }
    float Protein() const { return m_Protein; }

    // operators
    friend auto operator<=>(const Nut& nut1, const Nut& nut2)
        { return nut1.m_Name <=> nut2.m_Name; }

    friend bool operator==(const Nut& nut1, const Nut& nut2)
        { return nut1.m_Name == nut2.m_Name; }

    friend std::ostream& operator<<(std::ostream& os, const Nut& nut)
        { os << nut.to_str(); return os; }

    // miscellaneous (see Nut.cpp)
    static Nut get_nut(Nut::Type type);
    static std::string get_type_string(Nut::Type type);
    static std::vector<Nut> get_vector();
    static std::string title_str();

private:
    // private member functions (see Nut.cpp)
    std::string to_str() const;

    // private attributes
    std::string m_Name {};              // nut name
    unsigned int m_EnergyKj {};         // energy (kilojoules) per 100g
    unsigned int m_EnergyKcal {};       // energy (kilocalories) per 100g
    float m_Carbohydrates {};           // carbohydrates (g) per 100g
    float m_Fat {};                     // fat (g) per 100g
    float m_Protein {};                 // protein (g) per 100g
};

// class Nut formatter
template <> struct std::formatter<Nut> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const Nut& nut, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", nut.to_str()); }
};

#endif
