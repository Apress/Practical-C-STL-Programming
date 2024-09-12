//-----------------------------------------------------------------------------
// Ch05_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <string>
#include <utility>
#include <vector>
#include "Ch05_01.h"

void Ch05_01_ex1()
{
    using namespace std::string_literals;

    // pair<int, double>
    std::pair<int, double> pair1 {100, 200.0};
    std::println("pair1.first: {:d}  pair1.second: {:.1f}",
        pair1.first, pair1.second);

    // pair<std::string, long long>
    std::pair<std::string, long long> pair2 {"Hello, World!", 42LL};
    std::println("pair2.first: {:s}  pair2.second: {:d}",
        pair2.first, pair2.second);

    // using std::make_pair()
    auto pair3 = std::make_pair("cm / inch", 2.54f);
    std::println("pair3.first: {:s}  pair3.second: {:.2f}",
        pair3.first, pair3.second);

    // pair<> - type deduction
    std::pair pair4 {"L / U.S. gallon"s, 3.785411784};
    std::println("pair4.first: {:s}  pair4.second: {:.9f}",
        pair4.first, pair4.second);
}

void Ch05_01_ex2()
{
    // create std::pairs
    std::pair<int, double> pair1 {100, 200.0};
    std::pair<int, double> pair2 {300, 400.0};
    std::pair<int, double> pair3 {pair1};
    std::pair<int, double> pair4 {};
    std::pair<int, double> pair5 {};

    // using first and second
    pair4.first = pair1.first;
    pair4.second = 350.0;

    // using std::get<>
    std::get<0>(pair5) = pair1.first;   // pair5.first = pair1.first
    std::get<1>(pair5) = -150.0;        // pair5.second = -150.0

    // display values
    std::println("pair1.first: {:d}   pair1.second: {:.1f}",
        pair1.first, pair1.second);
    std::println("pair2.first: {:d}   pair2.second: {:.1f}",
        pair2.first, pair2.second);
    std::println("pair3.first: {:d}   pair3.second: {:.1f}",
        pair3.first, pair3.second);
    std::println("pair4.first: {:d}   pair4.second: {:.1f}",
        pair4.first, pair4.second);
    std::println("pair5.first: {:d}   pair5.second: {:.1f}",
        pair5.first, pair5.second);

    // relational operators
    std::println("\npair1 == pair2: {:s}", pair1 == pair2);
    std::println("pair1 == pair3: {:s}", pair1 == pair3);
    std::println("pair1 >  pair4: {:s}", pair1 >  pair4);
    std::println("pair1 <  pair4: {:s}", pair1 <  pair4);
}

void Ch05_01_ex3()
{
    // create vector of pair_t elements
    using pair_t = std::pair<std::string, double>;

    std::vector<pair_t> vec1 { {"Beryllium", 9.0122}, {"Helium", 4.0026},
        {"Neon", 20.180}, {"Nitrogen", 14.007}, {"Oxygen", 15.999} };

    // using emplace_back to add more elements
    vec1.emplace_back(std::make_pair("Lithium", 6.94));
    vec1.emplace_back(std::make_pair("Fluorine", 18.998));
    vec1.emplace_back(std::make_pair("Boron", 10.81));
    vec1.emplace_back(std::make_pair("Hydrogen", 1.0080));
    vec1.emplace_back(std::make_pair("Carbon", 12.011));

    // print lambda for std::vector<pair_t>
    auto print_vec = [](const char* msg, const std::vector<pair_t>& vec)
    {
        std::print("{:s}", msg);

        for (const auto& v : vec)
            std::println("{:<12s} {:12.4f}", v.first, v.second);
    };

    print_vec("\nvec1 (initial values):\n", vec1);

    // using std::ranges::sort (operator<)
    std::ranges::sort(vec1);
    print_vec("\nvec1 (after first sort):\n", vec1);

    // using std::ranges::sort (custom predicate)
    auto cmp_op = [](const pair_t& pair1, const pair_t& pair2)
        { return pair1.second < pair2.second; };

    std::ranges::sort(vec1, cmp_op);
    print_vec("\nvec1 (after second sort):\n", vec1);
}

void Ch05_01_ex()
{
    std::println("\n----- Ch05_01_ex1() -----");
    Ch05_01_ex1();

    std::println("\n----- Ch05_01_ex2() -----");
    Ch05_01_ex2();

    std::println("\n----- Ch05_01_ex3() -----");
    Ch05_01_ex3();
}
