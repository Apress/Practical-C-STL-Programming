//-----------------------------------------------------------------------------
// Ch11_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <list>
#include <numbers>
#include <numeric>
#include <vector>
#include "Ch11_02.h"
#include "AminoAcid.h"
#include "MF.h"
#include "MT.h"

void Ch11_02_ex1()
{
    using namespace std::numbers;
    const char* fmt {"{:9.2f} "};
    constexpr size_t epl_max {8};

    // create test vector of radii
    std::vector<double> radii(8);
    std::iota(radii.begin(), radii.end(), 1);
    MT::print_ctr("sphere radii:\n", radii, fmt, epl_max);

    // using std::transform
    std::vector<double> areas(radii.size());
    auto sphere_area = [](double r) { return 4.0 * pi * r * r; };
    std::transform(radii.begin(), radii.end(), areas.begin(), sphere_area);
    MT::print_ctr("\nsphere surface areas:\n", areas, fmt, epl_max);

    // using std::ranges::transform
    std::vector<double> volumes(radii.size());
    auto sphere_vol = [](double r) { return 4.0 * pi * r * r * r / 3.0; };
    std::ranges::transform(radii, volumes.begin(), sphere_vol);
    MT::print_ctr("\nsphere volumes:\n", volumes, fmt, epl_max);
}

void Ch11_02_ex2()
{
    const char* fmt1 {"'{:c}'   "};
    const char* fmt3 {"'{:3s}' "};
    constexpr size_t epl_max {12};

    // test sequence of amino acid codes (non-standard lower case)
    // (code 'x' is intentionally invalid)
    std::vector<char> aa1 {'a', 'g', 'l', 't', 'v', 'p', 'f', 'n', 'x', 'c', 'd'};
    MT::print_ctr("aa1 (initial values)\n", aa1, fmt1, epl_max);

    // using std::ranges::transform (inplace transformation)
    auto tr_op1 = [](char aa) { return MF::to_upper(aa); };
    std::ranges::transform(aa1, aa1.begin(), tr_op1);
    MT::print_ctr("\naa1 (after tansformation):\n", aa1, fmt1, epl_max);

    // using std::ranges::transform (non-inplace transformation)
    auto tr_op2 = [](char aa) { return AminoAcid::to_code3(aa); };
    std::deque<std::string> aa3 {};
    std::ranges::transform(aa1, std::back_inserter(aa3), tr_op2);
    MT::print_ctr("\naa3:\n", aa3, fmt3, epl_max);
}

void Ch11_02_ex3()
{
    const char* fmt {"{:12s}  "};
    constexpr size_t epl_max {5};

    // initialize test vectors
    std::vector<std::string> vec1 {"one", "two",  "three", "four",   "five"};
    std::vector<std::string> vec2 {"un",  "deux", "trois", "quatre", "cinq"};
    MT::print_ctr("vec1:  ", vec1, fmt, epl_max);
    MT::print_ctr("\nvec2:  ", vec2, fmt, epl_max);

    // using std::ranges::transform (binary operator)
    auto tr_op = [](const std::string& s1, const std::string& s2)
        { return s1 + '-' + s2; };

    std::list<std::string> list1 {};
    std::ranges::transform(vec1, vec2, std::back_inserter(list1), tr_op);
    MT::print_ctr("\nlist1: ", list1, fmt, epl_max);
}

void Ch11_02_ex()
{
    std::println("\n----- Ch11_02_ex1() -----\n");
    Ch11_02_ex1();

    std::println("\n----- Ch11_02_ex2() -----\n");
    Ch11_02_ex2();

    std::println("\n----- Ch11_02_ex3() -----\n");
    Ch11_02_ex3();
}
