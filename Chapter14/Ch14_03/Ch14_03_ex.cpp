//-----------------------------------------------------------------------------
// Ch14_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>
#include "Ch14_03.h"
#include "Mineral.h"
#include "MT.h"

struct Fruit
{
    std::string Name {};        // fruit name
    unsigned int Energy {};     // kJ per 100 gram serving
};
    
void Ch14_03_ex1()
{
    // test data
    std::vector<Fruit> fruits
    {
        {"Banana", 371},          {"Orange", 197},
        {"Apple", 281},           {"Kiwi (green)", 255},
        {"Tangerine", 223},       {"Blueberry", 240},
        {"Strawberry", 136},      {"Tomato (red)", 74},
        {"Cherry (sweet)", 263},  {"Cherry (sour)", 209},
    };

    // print lambda
    auto print_fruits = [&fruits](const char* msg)
    {
        std::println("{:s}", msg);

        for (const Fruit& f : fruits)
            std::println("{:20s}  kJ: {:3d}  kcal: {:3d}", f.Name,
            f.Energy, static_cast<unsigned int>(f.Energy * 0.239f + 0.5f));
    };

    // using std::ranges::sort, by Name
    std::ranges::sort(fruits, std::ranges::greater(), &Fruit::Name);
    print_fruits("\nvector fruits (descending order by Name)");

    // using std::ranges::sort, by Energy
    std::ranges::sort(fruits, std::ranges::less(), &Fruit::Energy);
    print_fruits("\nvector fruits (ascending order by Energy)");
}

void Ch14_03_ex2()
{
    const char* fmt = "{} ";
    constexpr size_t epl_max {3};

    // create test vector of minerals
    std::vector<Mineral> minerals = Mineral::get_vector_all_shuffle(100);

    // sort using Mineral::operator< (Hardness and Name)
    std::ranges::sort(minerals);
    MT::print_ctr("\nminerals (sorted using Mineral::operator<):\n",
        minerals, fmt, epl_max);

    // sort using std::ranges::greater and Hardness
    std::ranges::sort(minerals, std::ranges::greater(), &Mineral::Hardness);
    MT::print_ctr("\nminerals (sorted using std::ranges::greater and Hardness):\n",
        minerals, fmt, epl_max);

    // sort using std::ranges::less and Name
    std::ranges::sort(minerals, std::ranges::less(), &Mineral::Name);
    MT::print_ctr("\nminerals (sorted using std::ranges::less and Name):\n",
        minerals, fmt, epl_max);
}

struct Value
{
    double X {};
    double Y {};
};

void Ch14_03_ex3()
{
    // test vector
    std::vector<Value> values
    {
        {3.0, 4.0},  {6.0, 3.0},  {12.0, 5.0},  {11.0, 10.0},
        {7.0, 8.0},  {2.0, 9.0},  {4.0, 14.0},  {6.0, 13.0}
    };

    // projection lambdas (arbitrary calculations)
    auto pf1 = [](const Value& v) { return v.X + std::log(std::fabs(v.Y)) ; };
    auto pf2 = [](const Value& v) { return v.Y + std::log10(std::fabs(v.X)); };

    // print lambda
    auto print_values = [&] (const char* msg)
    {
        std::println("{:s}", msg);
        std::print("         X          Y");
        std::print(" |       pf1        pf2");
        std::println("\n{:s}", std::string(48, '='));

        for (const Value& v : values)
        {
            auto t1 = pf1(v);
            auto t2 = pf2(v);
            std::println("[{:9.4f}, {:9.4f} | {:9.4f}, {:9.4f}]", v.X, v.Y, t1, t2);
        }
    };

    // sort using std::ranges::greater() and pf1
    std::ranges::sort(values, std::ranges::greater(), pf1);
    print_values("\nvalues (sorted using std::ranges::greater and pf1):");

    // sort using std::ranges::less() and pf2
    std::ranges::sort(values, std::ranges::less(), pf2);
    print_values("\nvalues (sorted using std::ranges::less and pf2):");
}

void Ch14_03_ex()
{
    std::println("\n----- Ch14_03_ex1() -----");
    Ch14_03_ex1();

    std::println("\n----- Ch14_03_ex2() -----");
    Ch14_03_ex2();

    std::println("\n----- Ch14_03_ex3() -----");
    Ch14_03_ex3();
}
