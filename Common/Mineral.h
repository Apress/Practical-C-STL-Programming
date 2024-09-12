//-----------------------------------------------------------------------------
// Mineral.h
//-----------------------------------------------------------------------------

#ifndef MINERAL_H_
#define MINERAL_H_
#include <compare>
#include <format>
#include <string>
#include <vector>

class Mineral
{
    friend struct std::formatter<Mineral>;
    static constexpr unsigned int c_RngSeedDef {119};

public:
    Mineral() = default;
    Mineral(const char* name, double hardness) : m_Name {name},
        m_Hardness {hardness} {};
    Mineral(const std::string& name, double hardness) : m_Name {name},
        m_Hardness {hardness} {};

    // accessors
    std::string Name() const { return m_Name; }
    double Hardness() const { return m_Hardness; }

    // operators
    friend auto operator<=>(const Mineral& mineral1, const Mineral& mineral2)
    {
        auto cmp = mineral1.m_Hardness <=> mineral2.m_Hardness;
        return (cmp == 0) ? mineral1.m_Name <=> mineral2.m_Name : cmp;
    }

    friend bool operator==(const Mineral& mineral1, const Mineral& mineral2)
    {
        return mineral1.m_Hardness == mineral2.m_Hardness &&
               mineral1.m_Name == mineral2.m_Name;
    }

    // miscellaneous data generation functions
    static std::vector<Mineral> get_vector_all();
    static std::vector<Mineral> get_vector_all_shuffle(
        unsigned int rng_seed = c_RngSeedDef, unsigned int num_shuffles = 4);
    static std::vector<Mineral> get_vector_random(std::size_t vec_size,
        unsigned int rng_seed = c_RngSeedDef);
    static std::vector<Mineral> get_vector_sample(std::size_t vec_size,
        unsigned int rng_seed = c_RngSeedDef + 7);

private:
    std::string to_str() const;

    std::string m_Name {};      // mineral name
    double m_Hardness {};       // approximate hardness (Mohs scale)
};

// class Mineral formatter
template <> struct std::formatter<Mineral> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& pc)
        { return pc.begin(); }

    auto format(const Mineral& mineral, std::format_context& fc) const
        { return std::format_to(fc.out(), "{}", mineral.to_str()); }
};

#endif
