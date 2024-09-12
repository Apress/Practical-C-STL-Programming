//-----------------------------------------------------------------------------
// Ch03_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include "Ch03_03.h"
#include "MT.h"

void Ch03_03_ex1()
{
    const char* fmt = "{:6.1f}";
    constexpr size_t epl_max {10};
    constexpr double rem_val {-1.0};
    std::println("\nrem_val: {:.1f}", rem_val);

    // create test vectors
    std::vector<double> vec1 {10.0, 20.0, rem_val, 30.0, 40.0,
        rem_val, 50.0, rem_val, 60.0, 70.0};
    std::vector<double> vec2 {vec1};

    // using std::remove
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, 10);
    auto iter_rem = std::remove(vec1.begin(), vec1.end(), rem_val);
    MT::print_ctr("\nvec1 (after remove):\n", vec1, fmt, epl_max);
    std::println("vec1.size(): {:d}", vec1.size());

    // using std::vector::erase
    auto num_erased1 = vec1.end() - iter_rem;
    vec1.erase(iter_rem, vec1.end());
    MT::print_ctr("\nvec1 (after erase):\n", vec1, fmt, epl_max);
    std::println("num_erased1: {:d}", num_erased1);
    std::println("vec1.size(): {:d}", vec1.size());

    // using std::erase (C++20)
    MT::print_ctr("\nvec2 (initial values):\n", vec2, fmt, 10);
    auto num_erased2 = std::erase(vec2, rem_val);
    MT::print_ctr("\nvec2 (after std::erase):\n", vec2, fmt, epl_max);
    std::println("num_erased2: {:d}", num_erased2);
    std::println("vec2.size(): {:d}", vec2.size());
}

void Ch03_03_ex2()
{
    const char* fmt = "{:15s}";
    constexpr size_t epl_max {6};

    // initialize test containers
    std::array<std::string, 12> arr1
    {
        "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon",
        "Nitrogen", "Oxygen", "Fluorine", "Neon", "Sodium", "Magnesium",
    };
    MT::print_ctr("\narr1 (initial values):\n", arr1, fmt, epl_max);

    std::vector<std::string> vec1(arr1.begin(), arr1.end());
    MT::print_ctr("\nvec1 (initial values):\n", vec1, fmt, epl_max);

    // using std::replace and std::ranges::replace (C++20) with std::array
    std::replace(arr1.begin(), arr1.end(), "Neon", "NEON");
    std::ranges::replace(arr1, "Nitrogen", "NITROGEN");
    MT::print_ctr("\narr1 (after replace):\n", arr1, fmt, epl_max);

    // using std::replace and std::ranges::replace (C++20) with std::vector
    std::replace(vec1.begin(), vec1.end(), "Neon", "NEON");
    std::ranges::replace(vec1, "Nitrogen", "NITROGEN");
    MT::print_ctr("\nvec1 (after replace):\n", vec1, fmt, epl_max);

    // define unary predicate for later use
    auto replace_if_pred = [](std::string& s) { return s[0] == 'N'; };

    // using std::ranges::replace_if with std::array (C++20)
    std::ranges::replace_if(arr1, replace_if_pred, "########");
    MT::print_ctr("\narr1 (after replace_if):\n", arr1, fmt, epl_max);

    // using std::ranges::replace_if with std::vector (C++20)
    std::ranges::replace_if(vec1, replace_if_pred, "########");
    MT::print_ctr("\nvec1 (after replace_if):\n", vec1, fmt, epl_max);
}

void Ch03_03_ex()
{
    std::print("\n----- Ch03_03_ex1() -----\n");
    Ch03_03_ex1();

    std::print("\n----- Ch03_03_ex2() -----\n");
    Ch03_03_ex2();
}
