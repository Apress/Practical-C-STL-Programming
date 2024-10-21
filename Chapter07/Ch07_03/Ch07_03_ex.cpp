//-----------------------------------------------------------------------------
// Ch07_03_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <format>
#include <functional>
#include <map>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include "Ch07_03.h"
#include "MT.h"
#include "RGB.h"

void Ch07_03_ex1()
{
    constexpr size_t epl_max {5};
    const char* fmt1 = "[{:3d}, ";
    const char* fmt2 = "{:<6s}] ";
 
    // simple map (int key, std::string data)
    std::map<int, std::string> map1
        {{0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"},
         {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};

    MT::print_map("\nmap1 (initial values):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // using operator[] to modify values (keys are const)
    map1[0] = "null";
    map1[1] = "eins";
    map1[2] = "zwei";
    map1[3] = "drei";
    MT::print_map("\nmap1 (after modifications):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // using operator[] to add new elements
    map1[10] = "zehn";
    map1[11] = "elf";
    MT::print_map("\nmap1 (after insertions):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // using at() - throws std::out_of_range if key is invalid
    std::println("\nmap1.at(2):  {}", map1.at(2));
    std::println("map1.at(11): {}", map1.at(11));
//  std::println("map1.at(47): {}", map1.at(47));       // throws exception

    // erase elements
    map1.erase(5);
    map1.erase(6);
    MT::print_map("\nmap1 (after erase operations):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // clear map
    map1.clear();
    MT::print_map("\nmap1 (after clear):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());
}

void Ch07_03_ex2()
{
    constexpr size_t epl_max {1};
    const char* fmt1 = "[{:3s}, ";
    const char* fmt2 = "{:^35s}] ";

    // initialize map
    std::map<std::string_view, std::string> map1
        {{"ORD", "O'Hare International (Chicago, IL USA)"},
         {"LHR", "Heathrow Airport (London, England UK)"},
         {"ZRH", "Flughafen Zurich (Zurich, Switzerland)"},
         {"AKL", "Auckland Airport (Auckland, New Zealand)"}};

    MT::print_map("\nmap1 (initial values):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // insert element using new key
    map1["SYD"] = "Sydney Airport (Sydney, Australia)";
    MT::print_map("\nmap1 (after SYD insert):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());

    // insert new element using emplace
    //
    // notes: emplace returns std::pair<iterator, bool>
    //        returned iterator points to std::pair<Key, T>

    auto [iter1, status1] = map1.emplace
        ( std::make_pair("NRT", "Narita International (Tokyo, Japan)") );

    if (status1)
    {
        std::println("\nmap1.emplace - new element added to map1");
        std::println("key = '{}' value: '{}'", iter1->first, iter1->second);
    }
    else
    {
        std::println("\nmap1.emplace - element key already exists in map1");
        std::println("key = '{}' value: '{}'", iter1->first, iter1->second);
    }

    // insert new element using try_emplace
    auto [iter2, status2] = map1.try_emplace
        ("DXB", "Dubai International Airport (Dubai, UAE)");

    if (status2)
    {
        std::println("\nmap1.try_emplace - new element added to map1");
        std::println("key = '{}' value: '{}'", iter2->first, iter2->second);
    }
    else
        std::println("\nmap1.try_emplace - element key already exists in map1");

    MT::print_map("\nmap1 (after emplacements):\n", map1, fmt1, fmt2, epl_max);
    std::println("map1.size(): {:d}", map1.size());
    std::println("");

    // search map using key values and find()
    std::array<std::string_view, 4> keys {"ZRH", "LAX", "MCO", "AKL"};

    for (const std::string_view& key : keys)
    {
        std::print("key: '{:3s}' - ", key);

        if (auto iter = map1.find(key); iter != map1.end())
            std::println("found [{:3s}, {:35s}]", iter->first, iter->second);
        else
            std::println("not found");
    }
}

using cmap_lt_t = std::map<std::string_view, RGB, std::less<std::string_view>>;
using cmap_gt_t = std::map<std::string_view, RGB, std::greater<std::string_view>>;

template <typename T>
void print_colors(const char* msg, const T& colors)
{
    std::print("{:s}", msg);

    for (const auto& color : colors)
        std::println("{:<10s} {}", color.first, color.second);
}

void Ch07_03_ex3()
{
    // create map of colors
    cmap_lt_t colors1
    {
        {"Red", 0xFF0000}, {"Green", 0x008000}, {"Blue", 0x0000FF},
        {"Yellow", 0xFFFF00}, {"Cyan", 0x00FFFF}, {"Magenta", 0xFF00FF}
    };

    print_colors("\nmap colors1 (initial values):\n", colors1);

    // std::map relational operators
    cmap_lt_t colors2 {colors1};
    print_colors("\nmap colors2 (initial values):\n", colors2);
    std::println("\ncolors2 == colors1: {:s}", colors2 == colors1);
    std::println("colors2 <  colors1: {:s}", colors2 <  colors1);
    std::println("colors2 >  colors1: {:s}", colors2 >  colors1);

    colors2.emplace("Lime", 0x00FF00);
    print_colors("\nmap colors2 (after emplace):\n", colors2);
    std::println("\ncolors2 == colors1: {:s}", colors2 == colors1);
    std::println("colors2 <  colors1: {:s}", colors2 <  colors1);
    std::println("colors2 >  colors1: {:s}", colors2 >  colors1);

    // add more colors using insert_range (C++23)
#ifdef __cpp_lib_containers_ranges
    auto more_colors = { std::pair<std::string_view, RGB>
        {"Black", RGB {0x00000}}, {"Gray", RGB {0x808080}},
        {"LightGray", RGB {0xD3D3D3}}, {"White", RGB {0xFFFFFF}} };

    colors2.insert_range(more_colors);
    print_colors("\nmap colors2 (initial insert_range):\n", colors2);
#else
    std::println("\nstd::map::insert_range() requires C++23");
#endif

    // create new map using std::greater for key sorts
    cmap_gt_t colors3(colors2.begin(), colors2.end());
    print_colors("\nmap colors3 (initial values):\n", colors3);

    // invalid expressions - different template types
//  cmap_gt_t colors3(colors2);     // compiler error
//  bool colors3 < colors1;         // compiler error
}

void Ch07_03_ex4()
{
    // create and print maps
    cmap_lt_t colors1
        {{"Red", 0xFF0000}, {"Maroon", 0x800000}, {"Green", 0x008000},
         {"Yellow", 0xFFFF00}};

    cmap_gt_t colors2
        {{"Aqua", 0x00FFFF}, {"Teal", 0x008080}, {"Yellow", 0xFFFF00},
         {"Red", 0xFF0000}, {"White", 0xFFFFFF}};

    print_colors("\nmap colors1 (initial values):\n", colors1);
    print_colors("\nmap colors2 (initial values):\n", colors2);

    // merge maps - ok since colors1 and colors2 use same <Key, T>
    colors1.merge(colors2);
    print_colors("\nmap colors1 (after merge):\n", colors1);
    print_colors("\nmap colors2 (after merge):\n", colors2);
}

void Ch07_03_ex()
{
    std::println("\n----- Ch07_03_ex1() -----");
    Ch07_03_ex1();

    std::println("\n----- Ch07_03_ex2() -----");
    Ch07_03_ex2();

    std::println("\n----- Ch07_03_ex3() -----");
    Ch07_03_ex3();

    std::println("\n----- Ch07_03_ex4() -----");
    Ch07_03_ex4();
}
