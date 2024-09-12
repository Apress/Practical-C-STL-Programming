//-----------------------------------------------------------------------------
// Ch15_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <ranges>
#include <vector>
#include "Ch15_04.h"
#include "MT.h"
#include "RN.h"

void Ch15_04_ex1()
{
#ifdef __cpp_lib_ranges_slide
    using ll_t = long long;
    const char* fmt = "{:d} ";
    constexpr size_t epl_max {10};

    // create test vector
    std::vector vec1 = RN::get_vector<ll_t>(6, 1, 50, 327);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // sliding window print lambda
    auto print_window = [](auto& window)
    {
        std::print("[");
        for (auto x : window)
            std::print(" {:3d}", x);
        std::print("] ");
    };

    // sliding window calculate lambda
    auto calc_window = [](auto& window)
    {
        auto sum = std::ranges::fold_left(window, 0, std::plus<ll_t>());
        auto prod = std::ranges::fold_left(window, 1, std::multiplies<ll_t>());
        std::println("sum: {:d} prod: {:d}", sum, prod);
    };

    for (size_t window_w = 1; window_w <= vec1.size(); ++window_w)
    {
        std::println("\nwindow width: {:d}", window_w);

        // using std::views::slide
        auto slide1 = vec1 | std::views::slide(window_w);

        for (const auto& window1 : slide1)
        {
            print_window(window1);
            calc_window(window1);
        }
    }
#else
    std::println("Ch15_01_ex1() - std::views::slide requires C++23)");
#endif
}

void Ch15_04_ex2()
{
#ifdef __cpp_lib_ranges_stride
    const char* fmt = "{:6d} ";
    constexpr size_t epl_max {10};

    // create test vector
    std::vector vec1 = RN::get_vector<int>(50, 1, 50, 327);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::views::stride
    constexpr size_t stride_len {5};

    auto stride1 = vec1 | std::views::stride(stride_len);
    MT::print_ctr("\nstride1:\n", stride1, fmt, epl_max);

    // using std::views::stride and std::views::transform
    auto stride2 = vec1
                 | std::views::stride(stride_len)
                 | std::views::transform([](int x) { return x * x; });

    MT::print_ctr("\nstride2:\n", stride2, fmt, epl_max);
#else
    std::println("Ch15_01_ex2() - std::views::stride requires C++23)");
#endif
}

auto print_chunk(auto& chunk)
{
    std::print("[");

    for (auto x : chunk)
        std::print("{:d} ", x);
    std::print("] ");
}

void Ch15_04_ex3()
{
#ifdef __cpp_lib_ranges_chunk_by
    const char* fmt = "{:4d} ";
    constexpr size_t epl_max {12};

    // create test vector
    std::vector vec1 = RN::get_vector<int>(12, 1, 50, 327);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    for (size_t chunk_w = 1; chunk_w <= vec1.size(); ++chunk_w)
    {
        std::println("\nchunk_w: {:d}", chunk_w);

        // using std::views::chunk
        auto chunk1 = vec1 | std::views::chunk(chunk_w);

        for (const auto& chunk : chunk1)
            print_chunk(chunk);
        std::println("");
    }
#else
    std::println("Ch15_01_ex3() - std::views::chunk requires C++23)");
#endif
}

void Ch15_04_ex4()
{
#ifdef __cpp_lib_ranges_chunk_by
    const char* fmt = "{:4d} ";
    constexpr size_t epl_max {15};

    // create sorted test vector
    std::vector vec1 = RN::get_vector<int>(40, 1, 20, 271);
    std::ranges::sort(vec1);
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // using std::views::chunk_by
    auto chunk_op = [](int x, int y) { return x == y; };
    auto chunk_vw = vec1 | std::views::chunk_by(chunk_op);

    size_t nl {};
    std::println("\nchunk_vw:");

    for (auto chunk : chunk_vw)
    {
        print_chunk(chunk);

        if (++nl % 4 == 0)
            std::println("");
    }
#else
    std::println("Ch15_01_ex4() - std::views::chunk_by requires C++23)");
#endif
}

void Ch15_04_ex()
{
    std::println("\n----- Ch15_04_ex1() -----");
    Ch15_04_ex1();

    std::println("\n----- Ch15_04_ex2() -----");
    Ch15_04_ex2();

    std::println("\n----- Ch15_04_ex3() -----");
    Ch15_04_ex3();

    std::println("\n----- Ch15_04_ex4() -----");
    Ch15_04_ex4();
}
