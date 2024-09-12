//-----------------------------------------------------------------------------
// Ch07_01_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <functional>
#include <numbers>
#include <set>
#include <string>
#include "Ch07_01.h"
#include "MT.h"

void Ch07_01_ex1()
{
    const char* fmt1 = "{:d}  ";
    constexpr size_t epl_max {5};

    // create set1 - ints
    std::set<int> set1 {20, 40, 100, 50, 90, 70, 10, 30};

    MT::print_ctr("\nset1 (initial values):\n", set1, fmt1, epl_max);
    std::println("set1.size(): {:d}", set1.size());

    // add more elements to set1 using insert()
    std::array<int, 3> vals1 {80, 50, 60};

    for (auto val1 : vals1)
    {
        auto p = set1.insert(val1);
        std::println("set1.insert({:d}) - status: {:s}", *p.first, p.second);
    }

    MT::print_ctr("\nset1 (after insertions):\n", set1, fmt1, epl_max);
    std::println("set1.size(): {:d}", set1.size());

    // create set2 - strings
    const char* fmt2 = "{:s}  ";
    std::set<std::string> set2 {"New York", "Los Angeles", "Chicago",
        "Houston", "Phoenix", "Philadelphia", "San Antonio", "San Diego"};

    MT::print_ctr("\nset2 (initial values):\n", set2, fmt2, epl_max);
    std::println("set2.size(): {:d}\n", set2.size());

    // add more elements to set2 using emplace()
    std::array<std::string, 3> vals2 {"Dallas", "Phoenix", "Austin"};

    for (const auto& val2 : vals2)
    {
        auto p = set2.emplace(val2);
        std::println("set2.emplace(\"{:s}\") - status: {:s}", *p.first, p.second);
    }

    MT::print_ctr("\nset2 (after emplacements):\n", set2, fmt2, epl_max);
    std::println("set2.size(): {:d}", set2.size());
}

void Ch07_01_ex2()
{
    const char* fmt = "{:s}  ";
    constexpr size_t epl_max {5};

    // create set1 - using std::greater for sorting
    std::set<std::string, std::greater<std::string>> set1 { "California",
        "Texas", "Florida", "New York", "Pennsylvania", "Illinois", "Ohio"};

    MT::print_ctr("\nset1 (initial values):\n", set1, fmt, epl_max);

    // add more elements to set1 using insert
    std::array<std::string, 4> vals1
        {"Georgia", "Florida", "North Carolina", "Michigan"};

    set1.insert(vals1.begin(), vals1.end());
    MT::print_ctr("\nset1 (after insert):\n", set1, fmt, epl_max);

    // add more elements to set1 using insert_range (C++23)
#ifdef __cpp_lib_containers_ranges
    std::array<std::string, 3> vals2
        {"South Carolina", "Vermont", "Indiana"};

    set1.insert_range(vals2);
    MT::print_ctr("\nset1 (after insert_range):\n", set1, fmt, epl_max);
#else
    std::println("\nstd::set::insert_range() requires C++23");
#endif

    // using iterators to access elements of set1
    std::println("\nset1 (using iterators)");

    for (auto iter = set1.begin(); iter != set1.end(); ++iter)
    {
//      *iter += " test";               // error - modifications not allowed
        std::println("{:s}", *iter);
    }
}

void Ch07_01_ex3()
{
    const char* fmt = "{:5d}";
    constexpr size_t epl_max {10};

    // using relational operators
    std::set<int> set1 {100, 200, 300, 400, 500, 600};
    std::set<int> set2 {100, 200, 150, 400, 500, 600};
    std::set<int> set3 {100, 200, 300, 400, 500, 600};
    std::set<int> set4 {100, 200, 300, 450, 500, 600};

    MT::print_ctr("\nset1 (initial values):\n", set1, fmt, epl_max);
    MT::print_ctr("\nset2 (initial values):\n", set2, fmt, epl_max);
    MT::print_ctr("\nset3 (initial values):\n", set3, fmt, epl_max);
    MT::print_ctr("\nset4 (initial values):\n", set4, fmt, epl_max);

    std::println("\nset1 == set2: {:s}", set1 == set2);
    std::println("set1 != set2: {:s}", set1 != set2);
    std::println("set1 <  set2: {:s}", set1 <  set2);
    std::println("set1 <= set2: {:s}", set1 <= set2);
    std::println("set1 >  set2: {:s}", set1 >  set2);
    std::println("set1 >= set2: {:s}", set1 >= set2);

    std::println("\nset1 == set3: {:s}", set1 == set3);
    std::println("set1 <  set3: {:s}", set1 <  set3);
    std::println("set1 >  set3: {:s}", set1 >  set3);

    std::println("\nset1 == set4: {:s}", set1 == set4);
    std::println("set1 <  set4: {:s}", set1 <  set4);
    std::println("set1 >  set4: {:s}", set1 >  set4);

    // using relational operators (elements in container sorted using operator>)
    using set_t = std::set<int, std::greater<int>>;
    set_t set5 {100, 300, 400, 200, 500};
    set_t set6 {100, 300, 400, 200, 600};
    set_t set7 {100, 300, 400, 200, 500};
    MT::print_ctr("\nset5 (initial values):\n", set5, fmt, epl_max);
    MT::print_ctr("\nset6 (initial values):\n", set6, fmt, epl_max);
    MT::print_ctr("\nset7 (initial values):\n", set7, fmt, epl_max);

    std::println("\nset5 == set6: {:s}", set5 == set6);
    std::println("set5 <  set6: {:s}", set5 <  set6);
    std::println("set5 >  set6: {:s}", set5 >  set6);

    std::println("\nset5 == set7: {:s}", set5 == set7);
    std::println("set5 <  set7: {:s}", set5 <  set7);
    std::println("set5 >  set7: {:s}", set5 >  set7);
}

void Ch07_01_ex4()
{
    const char* fmt = "{}  ";
    constexpr size_t epl_max {5};

    // create set of strings
    std::set<std::string> set1 {"Wyoming", "Vermont", "Alaska", "North Dakota",
        "South Dakota", "Delaware", "Rhode Island", "Montana", "Maine"};

    MT::print_ctr("\nset1 (initial values):\n", set1, fmt, epl_max);
    std::println("");

    // search set1 using find, remove if found
    std::array<std::string, 4> find_vals
        {"New Hampshire", "Alaska", "Hawaii", "Maine"};

    for (const std::string& find_val : find_vals)
    {
        std::print("set1.find(\"{:s}\") - ", find_val);

        if (auto iter = set1.find(find_val); iter != set1.end())
        {
            set1.erase(iter);
            std::println("removed");
        }
        else
            std::println("not found");
    }

    MT::print_ctr("\nset1 (after erase operations):\n", set1, fmt, epl_max);
    std::println("");

    // search set1 for values using contains (C++20)
    std::array<std::string, 3> contains_vals
        {"Kansas", "South Dakota", "Nebraska"};

    for (const std::string& contain_val : contains_vals)
    {
        bool b = set1.contains(contain_val);
        std::println("set1.contains(\"{:s}\") - {:s}", contain_val, b);
    }
}

void Ch07_01_ex5()
{
    using namespace std::numbers;
    const char* fmt = "{:8.4f}";

    // create test sets
    std::set<double> set1 {pi, e, inv_pi, sqrt2};
    std::set<double> set2 {sqrt2, phi, pi, sqrt3, log2e};

    MT::print_ctr("\nset1 (initial values): ", set1, fmt);
    MT::print_ctr("set2 (initial values): ", set2, fmt);

    // merge sets
    set1.merge(set2);
    MT::print_ctr("\nset1 (after merge): ", set1, fmt);
    MT::print_ctr("set2 (after merge): ", set2, fmt);

    // clear set1
    set1.clear();
    MT::print_ctr("\nset1 (after clear): ", set1, fmt);
}

void Ch07_01_ex()
{
    std::println("\n----- Ch07_01_ex1() -----");
    Ch07_01_ex1();

    std::println("\n----- Ch07_01_ex2() -----");
    Ch07_01_ex2();

    std::println("\n----- Ch07_01_ex3() -----");
    Ch07_01_ex3();

    std::println("\n----- Ch07_01_ex4() -----");
    Ch07_01_ex4();

    std::println("\n----- Ch07_01_ex5() -----");
    Ch07_01_ex5();
}
