//-----------------------------------------------------------------------------
// Ch15_03_ex.cpp
//-----------------------------------------------------------------------------
#include <format>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include "Ch15_03.h"
#include "AminoAcid.h"
#include "MT.h"
#include "RN.h"

void Ch15_03_ex1()
{
    const char* fmt = "{:4d} ";
    constexpr size_t epl_max {15};

    constexpr size_t n {12};
    constexpr int rng_min {1};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {732};

    // create test vectors
    std::vector vec1 = RN::get_vector<int>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    std::vector vec2 = RN::get_vector<int>(n + 2, rng_min, rng_max, rng_seed / 3);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);

    std::vector vec3 = RN::get_vector<int>(n - 1, rng_min, rng_max, rng_seed / 4);
    MT::print_ctr("\nvec3:\n", vec3, fmt, epl_max);

    std::vector<std::vector<int>> vec_of_vecs {vec1, vec2, vec3};

    // create flatten view using std::views::join
    auto view_join = vec_of_vecs | std::views::join;
    MT::print_ctr("\nview_join:\n", view_join, fmt, epl_max);
}

void Ch15_03_ex2()
{
#ifdef __cpp_lib_ranges_join_with
    using namespace std::string_literals;

    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {20};

    // create test vector of amino acid code3 strings
    std::vector aa_vec1 = AminoAcid::get_vector_random_code3(15, 732);
    MT::print_ctr("\naa_vec1:\n", aa_vec1, fmt, epl_max);

   // using std::views::join_with
    auto aa_vec1_jw = aa_vec1 | std::views::join_with("|"s);

    // print chars using aa_vec1_jw
    std::print("\nresult #1: ");
    for (auto c : aa_vec1_jw)
        std::print("{:c}", c);
    std::println("");

    // create string using aa_vec1_jw
    std::string s(aa_vec1_jw.begin(), aa_vec1_jw.end());
    std::print("result #2: {:s}", s);

#else
    std::println("Ch15_03_ex2() std::views::join_with requires C++23");
#endif
}

void Ch15_03_ex3()
{
    // create vector of test strings and test delimiter
    std::vector<std::string> vec1
        { "one, two, three, four", "eins, zwei, drei, vier", "",
          "un, deux, trois, quatre" };

    std::string_view delim1 {", "};

    // using std::views::split
    for (const auto& str1 : vec1)
    {
        size_t i {};
        std::println("\ntest string:     \"{:s}\"", str1);

        for (auto sr1 : str1 | std::views::split(delim1))
        {
            // create string using sr1 (std::ranges::subrange)
            std::string s1(sr1.begin(), sr1.end());
            std::println("split string #{:d}: \"{:s}\"", i++, s1);
        }
    }
}

void Ch15_03_ex4()
{
#ifdef __cpp_lib_ranges_cartesian_product
    using pizza_tup = std::tuple<int, const std::string&, const std::string&,
        const std::string&>;

    // create test vectors
    std::vector<int> sizes {9, 12, 15, 18};
    std::vector<std::string> crusts {"Thin", "Thick", "DeepDish"};
    std::vector<std::string> toppings {"GreenPepper", "Mushroom", "Onion",
        "Pepperoni", "Sausage"};
    std::vector<std::string> salads {"Caesar", "Garden", "Spinach"};
 
    // print lambda expression
    auto print_pizza = [](const pizza_tup& pizza, size_t& nl)
    {
        const auto& [size, crust, topping, salad] = pizza;
        std::print("[{:2d} {:8s} {:11s} {:11s}] ", size, crust, topping,
            salad);

        if (++nl % 2 == 0)
            std::println("");
    };

    // using std::views::cartesian_product
    auto pizza_cp = std::views::cartesian_product(sizes, crusts, toppings, salads);

    size_t nl {0};
    for (const auto& pizza : pizza_cp)
        print_pizza(pizza, nl);
#else
    std::println("Ch15_03_ex4() - std::views::cartesian_product requires C++23)");
#endif
}

void Ch15_03_ex()
{
    std::println("\n----- Ch15_03_ex1() -----");
    Ch15_03_ex1();

    std::println("\n----- Ch15_03_ex2() -----");
    Ch15_03_ex2();

    std::println("\n----- Ch15_03_ex3() -----");
    Ch15_03_ex3();

    std::println("\n----- Ch15_03_ex4() -----");
    Ch15_03_ex4();
}
