//-----------------------------------------------------------------------------
// Ch10_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch10_02.h"
#include "MT.h"
#include "Nut.h"
#include "RN.h"

void Ch10_02_ex1()
{
    const char* fmt = "{:7.1f} ";
    constexpr size_t epl_max {10};

    // initialize vector of doubles
    std::vector<double> vec1 = RN::get_vector<double>(20);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::min_element and std::max_element
    auto iter_min1 = std::min_element(vec1.begin(), vec1.end());
    auto iter_max1 = std::max_element(vec1.begin(), vec1.end());
    std::println("\n*iter_min1: {:.1f}", *iter_min1);
    std::println("*iter_max1: {:.1f}", *iter_max1);

    // using std::ranges::min_element and std::ranges::max_element
    auto iter_min2 = std::ranges::min_element(vec1);
    auto iter_max2 = std::ranges::max_element(vec1);
    std::println("\n*iter_min2: {:.1f}", *iter_min2);
    std::println("*iter_max2: {:.1f}", *iter_max2);

    // using std::minmax_element, returns std::pair<iter, iter>
    auto [iter_min3, iter_max3] = std::minmax_element(vec1.begin(), vec1.end());
    std::println("\n*iter_min3: {:.1f}", *iter_min3);
    std::println("*iter_max3: {:.1f}", *iter_max3);

    // using std::ranges::minmax_element
    // std::ranges::minmax_element returns std::ranges::min_max_result
    auto [iter_min4, iter_max4] = std::ranges::minmax_element(vec1);
    std::println("\n*iter_min4: {:.1f}", *iter_min4);
    std::println("*iter_max4: {:.1f}", *iter_max4);
}

void Ch10_02_ex2()
{
    const char* fmt = "{}";
    constexpr size_t epl_max {1};

    // create vector of nuts
    std::vector<Nut> nuts = Nut::get_vector();
    MT::print_ctr(Nut::title_str().c_str(), nuts, fmt, epl_max);

    // using std::ranges::minmax_element (operator<)
    // std::ranges::minmax_element returns std::ranges::min_max_result
    auto result1 = std::ranges::minmax_element(nuts);

    std::println("\nminmax_element using operator<");
    std::println("result1.min: {:s}", result1.min->Name());
    std::println("result1.max: {:s}", result1.max->Name());

    // using std::ranges::minmax_element (fat compare)
    auto cmp_fat = [](const Nut& nut1, const Nut& nut2)
        { return nut1.Fat() < nut2.Fat(); };
    
    auto [result2_min, result2_max] = std::ranges::minmax_element(nuts, cmp_fat);

    std::println("\nminmax_element using cmp_fat");
    std::println("result2_min: {:s} = {:.4f}",
        result2_min->Name(), result2_min->Fat());
    std::println("result2_max: {:s} = {:.4f}",
        result2_max->Name(), result2_max->Fat());

    // using std::ranges::minmax_element (protein compare)
    auto cmp_protein = [](const Nut& nut1, const Nut& nut2)
        { return nut1.Protein() < nut2.Protein(); };

    auto [result3_min, result3_max] = std::ranges::minmax_element(nuts,cmp_protein);

    std::println("\nminmax_element using cmp_protein");
    std::println("result3_min: {:s} = {:.4f}",
        result3_min->Name(), result3_min->Protein());
    std::println("result3_max: {:s} = {:.4f}",
        result3_max->Name(), result3_max->Protein());
}

void Ch10_02_ex3()
{
    const char* fmt = "{:7.1f} ";
    constexpr size_t epl_max {10};

    // initialize vector of doubles
    std::vector<double> vec1 = RN::get_vector<double>(20);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::ranges::min and std::ranges::max
    auto min1 = std::ranges::min(vec1);
    auto max1 = std::ranges::max(vec1);
    std::println("\nmin1: {:.1f}", min1);
    std::println("max1: {:.1f}", max1);

    // using std::ranges::minmax
    auto result2 = std::ranges::minmax(vec1);
    std::println("\nresult.min: {:.1f}", result2.min);
    std::println("result.max: {:.1f}", result2.max);
}

void Ch10_02_ex()
{
    std::println("\n----- Ch10_02_ex1() -----");
    Ch10_02_ex1();

    std::println("\n----- Ch10_02_ex2() -----");
    Ch10_02_ex2();

    std::println("\n----- Ch10_02_ex3() -----");
    Ch10_02_ex3();
}
