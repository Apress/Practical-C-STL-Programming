//-----------------------------------------------------------------------------
// AminoAcid.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <optional>
#include <random>
#include "AminoAcid.h"

using SC = AminoAcid::SC;

namespace
{
    // standard amino acids    
    const std::vector<AminoAcid> c_AminoAcids
    {
        AminoAcid {"Alanine",       'A', "Ala",  89.094, SC::NonPolar},
        AminoAcid {"Arginine",      'R', "Arg", 174.203, SC::Basic},
        AminoAcid {"Asparagine",    'N', "Asn", 132.119, SC::UnchargedPolar},
        AminoAcid {"AsparticAcid",  'D', "Asp", 133.104, SC::Acidic},
        AminoAcid {"Cysteine",      'C', "Cys", 121.154, SC::NonPolar},
        AminoAcid {"Glutamine",     'Q', "Gln", 146.146, SC::UnchargedPolar},
        AminoAcid {"GlutamicAcid",  'E', "Glu", 147.131, SC::Acidic},
        AminoAcid {"Glycine",       'G', "Gly",  75.067, SC::NonPolar},
        AminoAcid {"Histidine",     'H', "His", 155.156, SC::Basic},
        AminoAcid {"IsoLeucine",    'I', "Ile", 131.175, SC::NonPolar},
        AminoAcid {"Leucine",       'L', "Leu", 131.175, SC::NonPolar},
        AminoAcid {"Lysine",        'K', "Lys", 146.189, SC::Basic},
        AminoAcid {"Methionine",    'M', "Met", 149.208, SC::NonPolar},
        AminoAcid {"Phenylalanine", 'F', "Phe", 165.192, SC::NonPolar},
        AminoAcid {"Proline",       'P', "Pro", 115.132, SC::NonPolar},
        AminoAcid {"Serine",        'S', "Ser", 105.093, SC::UnchargedPolar},
        AminoAcid {"Threonine",     'T', "Thr", 119.119, SC::UnchargedPolar},
        AminoAcid {"Tryptophan",    'W', "Trp", 204.228, SC::NonPolar},
        AminoAcid {"Tyrosine",      'Y', "Tyr", 181.191, SC::UnchargedPolar},
        AminoAcid {"Valine",        'V', "Val", 117.148, SC::NonPolar},
    };
};

// helper functions
std::optional<AminoAcid> AminoAcid::find(char code1)
{
    auto pred = [code1](const AminoAcid& aa) { return aa.Code1() == code1; };
    auto iter = std::ranges::find_if(c_AminoAcids, pred);
    return (iter != c_AminoAcids.end()) ? std::optional(*iter) : std::nullopt;
}

std::optional<AminoAcid> AminoAcid::find(const std::string& code3)
{
    auto pred = [code3](const AminoAcid& aa) { return aa.Code3() == code3; };
    auto iter = std::ranges::find_if(c_AminoAcids, pred);
    return (iter != c_AminoAcids.end()) ? std::optional(*iter) : std::nullopt;
}

bool AminoAcid::is_valid(char code1)
{
    std::optional<AminoAcid> aa = AminoAcid::find(code1);
    return aa.has_value();
}

bool AminoAcid::is_valid(const std::string& code3)
{
    std::optional<AminoAcid> aa = AminoAcid::find(code3);
    return aa.has_value();
}

char AminoAcid::to_code1(const std::string& code3)
{
    std::optional<AminoAcid> aa = AminoAcid::find(code3);
    return aa.has_value() ? aa.value().Code1() : AminoAcid::BadCode1;
}

std::string AminoAcid::to_code3(char code1)
{
    std::optional<AminoAcid> aa = AminoAcid::find(code1);
    return aa.has_value() ? aa.value().Code3() : AminoAcid::BadCode3;
}

std::string AminoAcid::to_string(SC side_chain, bool short_text)
{
    switch (side_chain)
    {
        case SC::Acidic:
            return (short_text) ? "A " : "Acidic";
        case SC::Basic:
            return (short_text) ? "B " : "Basic";
        case SC::NonPolar:
            return (short_text) ? "NP" : "NonPolar";
        case SC::UnchargedPolar:
            return (short_text) ? "UP" : "UnchargedPolar";
        default:
            return (short_text) ? "??" : "?????";
    }
}

// vector generators
std::vector<AminoAcid> AminoAcid::get_vector_all()
{
    return c_AminoAcids;
}

std::vector<char> AminoAcid::get_vector_all_code1()
{
    std::vector<char> amino_acids {};

    for (const AminoAcid& aa : c_AminoAcids)
        amino_acids.push_back(aa.Code1());
    return amino_acids;
}

std::vector<std::string> AminoAcid::get_vector_all_code3()
{
    std::vector<std::string> amino_acids {};

    for (const AminoAcid& aa : c_AminoAcids)
        amino_acids.push_back(aa.Code3());
    return amino_acids;
}

std::vector<double> AminoAcid::get_vector_all_mol_mass()
{
    std::vector<double> amino_acids {};

    for (const AminoAcid& aa : c_AminoAcids)
        amino_acids.push_back(aa.MolMass());
    return amino_acids;
}

std::vector<std::string> AminoAcid::get_vector_all_name()
{
    std::vector<std::string> amino_acids {};

    for (const AminoAcid& aa : c_AminoAcids)
        amino_acids.push_back(aa.Name());
    return amino_acids;
}

std::vector<char> AminoAcid::get_vector_random_code1(size_t num_aa,
    unsigned int rng_seed)
{
    const int dist_max = static_cast<int>(c_AminoAcids.size() - 1);
    std::mt19937 rng {rng_seed};
    std::uniform_int_distribution<int> dist {0, dist_max};

    std::vector<char> amino_acids(num_aa);

    for (size_t i = 0; i < amino_acids.size(); ++i)
        amino_acids[i] = c_AminoAcids[dist(rng)].Code1();
    return amino_acids;
}

std::vector<std::string> AminoAcid::get_vector_random_code3(size_t num_aa,
        unsigned int rng_seed)
{
    std::vector<char> amino_acids1 = get_vector_random_code1(num_aa, rng_seed);
    std::vector<std::string> amino_acids3{};

    for (auto aa_code1 : amino_acids1)
        amino_acids3.push_back(to_code3(aa_code1));
    return amino_acids3;
}

std::vector<AaTuple> AminoAcid::get_vector_tuple()
{
    std::vector<AaTuple> aa_vec {};

    for (const AminoAcid& aa : c_AminoAcids)
    {
        aa_vec.emplace_back(std::make_tuple(aa.m_Code3, aa.m_Name, aa.m_Code1,
            aa.m_MolMass));
    }

    return aa_vec;
}

// private member functions
std::string AminoAcid::to_str() const
{
    std::string s {};
    std::format_to(std::back_inserter(s), "[{:<16s}", m_Name);
    std::format_to(std::back_inserter(s), "{:c}|", m_Code1);
    std::format_to(std::back_inserter(s), "{:3s}|", m_Code3);
    std::format_to(std::back_inserter(s), "{:7.3f}|", m_MolMass);
    std::format_to(std::back_inserter(s), "{:2s}]", to_string(m_SideChain));
    return s;
}
