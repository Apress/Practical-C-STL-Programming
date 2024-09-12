//-----------------------------------------------------------------------------
// Ch15_02_ex.cpp
//-----------------------------------------------------------------------------

#include <format>
#include <map>
#include <numbers>
#include <ranges>
#include <vector>
#include "Ch15_02.h"
#include "AminoAcid.h"
#include "MT.h"
#include "MF.h"
#include "RN.h"

void Ch15_02_ex1()
{
#if defined(__cpp_lib_ranges_enumerate) && defined(__cpp_lib_ranges_to_container)
    const char* fmt = "{}";
    constexpr size_t epl_max {2};

    // initialize vector of amino acids
    std::vector<AminoAcid> aa_vec = AminoAcid::get_vector_all();
    MT::print_ctr("\naa_vec:\n", aa_vec, fmt, epl_max);

    // using std::views::enumerate
    auto aa_enum = aa_vec | std::views::enumerate;
    std::println("\naa_enum (size = {:d}):", aa_enum.size());

    if (!aa_enum.empty())
    {
        for (const auto& [key, value] : aa_enum)
            std::println("key: {:2d}: value: {}", key, value);
    }

    // using std::ranges::to<std::map>
    auto aa_map = aa_enum | std::ranges::to<std::map>();
    std::println("\naa_map (size = {:d}):", aa_map.size());

    if (!aa_map.empty())
    {
        for (const auto& [key, value] : aa_map)
            std::println("key: {:2d}: value: {}", key, value);
    }
#else
    std::println("Ch15_02_ex1() requires C++23");
#endif
}

void Ch15_02_ex2()
{
#ifdef __cpp_lib_ranges_zip
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {10};

    // initialize vector of amino acids
    std::vector<std::string> aa_vec = AminoAcid::get_vector_all_code3();
    MT::print_ctr("\naa_vec:\n", aa_vec, fmt, epl_max);

    // using std::views::adjacent
    auto adj_view1 = aa_vec | std::views::adjacent<3>;
    std::println("\nadj_view1 (size = {:d}):", adj_view1.size());

    if (adj_view1)
    {
        for (const auto [aa0, aa1, aa2] : adj_view1)
            std::println("[{:3s} {:3s} {:3s}]", aa0, aa1, aa2);
    }

    // using std::views::adjacent_transform
    auto adj_xform = [](const std::string& s1, const std::string& s2,
                        const std::string& s3, const std::string& s4)
        { return s1 + "|" + s2 + "|" + s3 + "|" + s4; };

    auto adj_view2 = aa_vec | std::views::adjacent_transform<4>(adj_xform);
    std::println("\nadj_view2 (size = {:d}):", adj_view2.size());

    if (adj_view2)
    {
        for (auto a : adj_view2)
            std::println("[{:s}]", a);
    }
#else
    std::println("Ch15_02_ex2() - std::views::adjacent_transform() requires C++23");
#endif
}

void Ch15_02_ex3()
{
#ifdef __cpp_lib_ranges_zip
    const char* fmt_code1 = "{:5c}";
    const char* fmt_code3 = "{:5s}";
    const char* fmt_mm = "{:9.3f}";
    constexpr size_t epl_max {7};

    // create text vectors of amino acid attributes
    std::vector<char> aa_vec_code1 {AminoAcid::get_vector_all_code1()};
    MT::print_ctr("\naa_vec_code1:\n", aa_vec_code1, fmt_code1, epl_max);

    std::vector<std::string> aa_vec_code3 {AminoAcid::get_vector_all_code3()};
    MT::print_ctr("\naa_vec_code3:\n", aa_vec_code3, fmt_code3, epl_max);

    std::vector<double> aa_vec_mm {AminoAcid::get_vector_all_mol_mass()};
    MT::print_ctr("\naa_vec_mm:\n", aa_vec_mm, fmt_mm, epl_max);

    // create zip view of amino acid attributes
    auto aa_zip_view = std::views::zip(aa_vec_code1, aa_vec_code3, aa_vec_mm);
    std::println("\naa_zip_view:");

    // print tuples of aa_zip_view
    for (auto aa : aa_zip_view)
    {
        std::string s {};
        static const char* sep = "  ";

        std::vformat_to(std::back_inserter(s), fmt_code1,
            std::make_format_args(std::get<0>(aa)));
        s += sep;

        std::vformat_to(std::back_inserter(s), fmt_code3,
            std::make_format_args(std::get<1>(aa)));
        s += sep;

        std::vformat_to(std::back_inserter(s), fmt_mm,
            std::make_format_args(std::get<2>(aa)));

        std::println("{:s}", s);
    }
#else
    std::println("Ch15_02_ex3() - std::views::zip() requires C++23");
#endif
}

void Ch15_02_ex4()
{
#ifdef __cpp_lib_ranges_zip
    const char* fmt = "{:10.2f} ";
    constexpr size_t epl_max {6};

    constexpr size_t n {12};
    constexpr int rng_min {1};
    constexpr int rng_max {20};
    constexpr unsigned int rng_seed {511};

    // create vector of cylinder radii and heights
    std::vector radii = RN::get_vector<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nradii:\n", radii, fmt, epl_max);

    std::vector heights = RN::get_vector<double>(n, rng_min, rng_max, rng_seed / 3);
    MT::print_ctr("\nheights:\n", heights, fmt, epl_max);

    // lambda to calculate cylinder volume
    auto cyl_vol = [](double r, double h) { return std::numbers::pi * r * r * h; };

    // calculate volumes - vector sizes equal
    auto volumes1 = std::views::zip_transform(cyl_vol, radii, heights);
    MT::print_ctr("\nvolumes1:\n", volumes1, fmt, epl_max);

    // modify test vector heights
    heights.pop_back();
    MT::print_ctr("\nheights (after pop_back):\n", heights, fmt, epl_max);
    
    // calculate volumes - vector sizes not equal
    auto volumes2 = std::views::zip_transform(cyl_vol, radii, heights);
    MT::print_ctr("\nvolumes2:\n", volumes2, fmt, epl_max);
#else
    std::println("Ch15_02_ex4() - std::views::zip_transform() requires C++23");
#endif
}

void Ch15_02_ex()
{
    std::println("\n----- Ch15_02_ex1() -----");
    Ch15_02_ex1();

    std::println("\n----- Ch15_02_ex2() -----");
    Ch15_02_ex2();

    std::println("\n----- Ch15_02_ex3() -----");
    Ch15_02_ex3();

    std::println("\n----- Ch15_02_ex4() -----");
    Ch15_02_ex4();
}
