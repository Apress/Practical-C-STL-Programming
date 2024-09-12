//-----------------------------------------------------------------------------
// AminoAcid.h
//-----------------------------------------------------------------------------

#ifndef AMINIO_ACID_H_
#define AMINIO_ACID_H_
#include <cstddef>
#include <format>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

// AA tuple <3-letter code, full name 1-letter code, molecular mass>
using AaTuple = std::tuple<std::string, std::string, char, double>;

class AminoAcid
{
    friend struct std::formatter<AminoAcid>;
    static constexpr unsigned int s_RngSeedDefault {1001};

public:
    // amino acid side chain types
    enum class SC : unsigned int
        { Unknown, Acidic, Basic, NonPolar, UnchargedPolar };

    static constexpr char BadCode1 {'?'};
    static constexpr const char* BadCode3 = "???";

    // constructors
    AminoAcid() = default;

    explicit AminoAcid(const char* name, char code1, const char* code3,
        double mol_mass, SC side_chain) : m_Name {name}, m_Code1 {code1}, m_Code3 {code3},
        m_MolMass {mol_mass}, m_SideChain {side_chain} {};

    // accessors
    const std::string& Name() const { return m_Name; }
    char Code1() const { return m_Code1; }
    std::string Code3() const { return m_Code3; }
    double MolMass() const { return m_MolMass; }
    SC SideChain() const { return m_SideChain; }

    // operators
    friend auto operator<=>(const AminoAcid& aa1, const AminoAcid& aa2)
        { return aa1.m_Name <=> aa2.m_Name; }
    friend bool operator==(const AminoAcid& aa1, const AminoAcid& aa2)
        { return aa1.m_Name == aa2.m_Name; }

    // helper functions (see AminoAcid.cpp)
    static std::optional<AminoAcid> find(char code1);
    static std::optional<AminoAcid> find(const std::string& code3);
    static bool is_valid(char code1);
    static bool is_valid(const std::string& code3);
    static char to_code1(const std::string& code3);
    static std::string to_code3(char code1);
    static std::string to_string(SC side_chain, bool short_text = true);

    // vector generators (see AminoAcid.cpp)
    static std::vector<AminoAcid> get_vector_all();
    static std::vector<char> get_vector_all_code1();
    static std::vector<std::string> get_vector_all_code3();
    static std::vector<double> get_vector_all_mol_mass();
    static std::vector<std::string> get_vector_all_name();
    static std::vector<char> get_vector_random_code1(size_t num_aa,
        unsigned int rng_seed = s_RngSeedDefault);
    static std::vector<std::string> get_vector_random_code3(size_t num_aa,
        unsigned int rng_seed = s_RngSeedDefault);
    static std::vector<AaTuple> get_vector_tuple();

private:
    std::string to_str() const;

    std::string m_Name {};              // full name
    char m_Code1 {};                    // 1-letter code
    std::string m_Code3 {};             // 3-letter code
    double m_MolMass {};                // molecular mass (g/mol)
    SC m_SideChain {SC::Unknown};       // side chain type
};

// class AminoAcid formatter
template <> struct std::formatter<AminoAcid> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const AminoAcid& aa, std::format_context& fc) const
        { return std::format_to(fc.out(), "{:s}", aa.to_str()); }
};

#endif
