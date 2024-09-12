//-----------------------------------------------------------------------------
// Ch10_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <deque>
#include <set>
#include <vector>
#include <utility>
#include "Ch10_01.h"
#include "AminoAcid.h"
#include "MT.h"

namespace
{
    const std::initializer_list<int> c_Numbers { 10, 20, 30, -10, 40, 50, 80, 10,
        50, -60, 10, 80, -90, 10, 80, 90, 60, 120, 90, 80, 60, 10, -20, -70 };
};

void Ch10_01_ex1()
{
    const char* fmt = "{:5d}";
    constexpr size_t epl_max {12};

    // using std::count with std::vector
    std::vector<int> vec1 {c_Numbers};
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    auto count10 = std::count(vec1.begin(), vec1.end(), 10);
    auto count75 = std::ranges::count(vec1, 75);
    std::println("\ncount10: {:d}", count10);
    std::println("count70: {:d}", count75);

    // using std::count with std::multiset
    // (elements ordered in ascending order)
    std::multiset<int> mset1 {c_Numbers};
    MT::print_ctr("\nmset1:\n", mset1, fmt, epl_max);

    auto count40 = std::count(mset1.begin(), mset1.end(), 40);
    auto count50 = std::ranges::count(mset1, 50);
    std::println("\ncount40: {:d}", count40);
    std::println("count80: {:d}", count50);
}

void Ch10_01_ex2()
{
    const char* fmt = "{:5d}";
    constexpr size_t epl_max {12};

    // predicates for std::count_if
    auto neg_pred = [](int x) { return x < 0; };
    auto div30_pred = [](int x) { return x % 30 == 0; };

    // using std::count_if
    std::deque<int> deq1 {c_Numbers};
    MT::print_ctr("\ndeq1:\n", deq1, fmt, epl_max);

    auto num_neg = std::count_if(deq1.begin(), deq1.end(), neg_pred);
    std::println("\nnum_neg: {:d}", num_neg);

    // using std::ranges::count_if
    auto num_div30 = std::ranges::count_if(deq1, div30_pred);
    std::println("num_div30: {:d}", num_div30);
}

void Ch10_01_ex3()
{
    // initialize vector of full amino acids
    std::vector<AminoAcid> vec1 {AminoAcid::get_vector_all()};
    MT::print_ctr("\nvec1:\n", vec1, "{}  ", 2);

    // using std::any_of, std::all_of, std::none_of
    const double mol_mass_vals[] {75.0, 150.0, 250.0};

    for (auto mol_mass : mol_mass_vals)
    {
        auto pred_mm = [mol_mass](const AminoAcid& aa)
            { return aa.MolMass() >= mol_mass; };

        // using std::any_of, std::all_of, std::none_of
        bool b_any_of = std::ranges::any_of(vec1, pred_mm);
        bool b_all_of = std::ranges::all_of(vec1, pred_mm);
        bool b_none_of = std::ranges::none_of(vec1, pred_mm);
 
        std::println("\nMolMass >= {:.2f})", mol_mass);
        std::println("b_any_of:  {:s}", b_any_of);
        std::println("b_all_of:  {:s}", b_all_of);
        std::println("b_none_of: {:s}", b_none_of);
    }
}

void Ch10_01_ex()
{
    std::println("\n----- Ch10_01_ex1() -----");
    Ch10_01_ex1();

    std::println("\n----- Ch10_01_ex2() -----");
    Ch10_01_ex2();

    std::println("\n----- Ch10_01_ex3() -----");
    Ch10_01_ex3();
}
