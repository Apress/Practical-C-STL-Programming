//-----------------------------------------------------------------------------
// Ch15_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <ranges>
#include <vector>
#include "Ch15_01.h"
#include "AminoAcid.h"

void Ch15_01_ex1()
{
    size_t add_nl {};
    constexpr size_t add_nl_max {5};

    // create vector of AminoAcid tuples
    // AaTuple = using std::tuple<std::string, std::string, char, double>;
    //                            Code3,       Name         Code1 MolMass
    std::vector<AaTuple> aa_vec = AminoAcid::get_vector_tuple();

    // using std::views::keys (first tuple element)
    auto view_keys = std::views::keys(aa_vec);

    for (const std::string& aa_code3 : view_keys)
    {
        char c = (++add_nl % add_nl_max == 0) ? '\n' : ' ';
        std::print("{:3s}{:c}", aa_code3, c);
    }
    std::println("");

    // using std::views::values (second tuple element)
    add_nl = 0;
    auto view_values = std::views::values(aa_vec);

    for (const std::string& aa_name : view_values)
    {
        char c = (++add_nl % add_nl_max == 0) ? '\n' : ' ';
        std::print("{:15s}{:c}", aa_name, c);
    }
    std::println("");
}

template <typename T, size_t I>
void print_elements(const char* msg, std::vector<AaTuple>& aa_vec, const char* fmt)
{
    size_t add_nl {};
    constexpr size_t add_nl_max {5};

    std::println("{:s}", msg);

    for (const T& elem : std::views::elements<I>(aa_vec))
    {
        // format tuple element I of elem
        std::string s {};
        std::vformat_to(std::back_inserter(s), fmt, std::make_format_args(elem)); 

        // add nl if needed, then print
        char c = (++add_nl % add_nl_max == 0) ? '\n' : ' ';
        s.push_back(c);
        std::print("{}", s);
    }
    std::println("");
}

void Ch15_01_ex2()
{
    // create vector of AminoAcid tuples
    std::vector<AaTuple> aa_vec = AminoAcid::get_vector_tuple();

    // print tuple elements in aa_vec
    print_elements<std::string, 0>("element 0 (amino acid code3)", aa_vec, "{:3s}");

    print_elements<std::string, 1>("element 1 (amino acid name)", aa_vec, "{:15s}");

    print_elements<char, 2>("element 2 (amino acid code1)", aa_vec, "{:3c}");

    print_elements<double, 3>("element 3 (amino acid mol mass)", aa_vec, "{:8.3f}");
}

void Ch15_01_ex()
{
    std::println("\n----- Ch15_01_ex1() -----");
    Ch15_01_ex1();

    std::println("\n----- Ch15_01_ex2() -----");
    Ch15_01_ex2();
}
