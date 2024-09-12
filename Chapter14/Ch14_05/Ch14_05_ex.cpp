//-----------------------------------------------------------------------------
// Ch14_05_ex.cpp
//-----------------------------------------------------------------------------

#include <ranges>
#include <vector>
#include "Ch14_05.h"
#include "MT.h"
#include "RN.h"

auto get_test_vector(unsigned int seed)
{
    return RN::get_vector<int>(30, -200, 200, seed);
}

void Ch14_05_ex1()
{
    const char* fmt = "{:8d}";
    constexpr size_t epl_max {10};

    // create view that squares positive numbers
    auto view_ft = std::views::filter([](int x) { return x >= 0; })
                 | std::views::transform([](int x) { return x * x; });

    // create test vectors of random numbers
    std::vector<int> vec1 = get_test_vector(71);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    std::vector<int> vec2 = get_test_vector(73);
    MT::print_ctr("\nvec2:\n", vec2, fmt, epl_max);

    // using view_ft - operator |
    auto view1a = vec1 | view_ft;
    MT::print_ctr("\nview1a:\n", view1a, fmt, epl_max);

    // using view_ft - function call syntax
    auto view2a = view_ft(vec2);
    MT::print_ctr("\nview2a:\n", view2a, fmt, epl_max);
}

void Ch14_05_ex2()
{
    const char* fmt = "{:8d}";
    constexpr size_t epl_max {10};

    // create test vectors of random numbers
    std::vector<int> vec1 = get_test_vector(71);
    MT::print_ctr("\nvec1 (before calculation of squares):\n", vec1, fmt, epl_max);

    // create view of positive numbers
    auto view1 = vec1 | std::views::filter([](int x) { return x >= 0; });

    // square positive numbers
    for (auto& val : view1)
        val *= val;

    MT::print_ctr("\nvec1 (after calculation of squares):\n", vec1, fmt, epl_max);
}

#define STATIC_VECTOR

auto get_test_view(unsigned int seed, const char* fmt, size_t epl_max)
{
    // create test vector
#ifdef STATIC_VECTOR
    static std::vector<int> vec1 {};        // ok
#else
    std::vector<int> vec1 {};               // trouble
#endif

    // create view of positive numbers
    vec1 = RN::get_vector<int>(30, -200, 200, seed);
    auto view1 = vec1 | std::views::filter([](int x) { return x >= 0; });
    MT::print_ctr("view1:\n", view1, fmt, epl_max);

    // return view to caller (trouble if vec1 not static)
    return view1;
}

void Ch14_05_ex3()
{
    const char* fmt = "{:8d}";
    constexpr size_t epl_max {10};

    auto test_view = get_test_view(77, fmt, epl_max);

    std::print("\ntest_view: ");

#ifdef STATIC_VECTOR
    MT::print_ctr("\n", test_view, fmt, epl_max);
#else
    std::println("invalid view - preprocessor symbol STATIC_VECTOR not defined");
#endif
}

void Ch14_05_ex()
{
    std::println("\n----- Ch14_05_ex1() -----");
    Ch14_05_ex1();

    std::println("\n----- Ch14_05_ex2() -----");
    Ch14_05_ex2();

    std::println("\n----- Ch14_05_ex3() -----");
    Ch14_05_ex3();
}
