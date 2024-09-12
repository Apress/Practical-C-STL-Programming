//-----------------------------------------------------------------------------
// Ch19_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <concepts>
#include <expected>
#include <valarray>
#include <utility>
#include "Ch19_02.h"
#include "MT.h"
#include "RN.h"

void Ch19_02_ex1()
{
    const char* fmt = "{:7.1f}";
    constexpr size_t epl_max {10};

    constexpr size_t n {50};
    constexpr int rng_min {1};
    constexpr int rng_max {50};
    constexpr unsigned int rng_seed {19014};

    // create test valarray<>
    std::valarray va = RN::get_valarray<double>(n, rng_min, rng_max, rng_seed);
    MT::print_ctr("\nva:\n", va, fmt, epl_max);

    // calculate mean
    double va_mean = va.sum() / va.size();

    // calculate standard deviation using std::ranges::fold_left
    auto sd_fold_op = [&va_mean](double sum, double x) -> double
        { return sum + (x - va_mean) * (x - va_mean); };

    double va_sd_sum = std::ranges::fold_left(va, 0.0, sd_fold_op);
    double va_sd = std::sqrt(va_sd_sum / (va.size() - 1));

    std::println("\nva_mean: {:.4f}", va_mean);
    std::println("va_sd    {:.4f}", va_sd);
}

#if __cpp_lib_expected >= 202211L

template <typename T> requires std::floating_point<T>
std::expected<std::pair<T, T>, bool> least_squares(const std::valarray<T>& va_x,
    const std::valarray<T>& va_y, T epsilon)
{
    if (va_x.size() != va_y.size())
        return std::unexpected(false);

    // calculate sum_x and sum_y
    T sum_x = va_x.sum();
    T sum_y = va_y.sum();

    // calculate sum_xx
    auto sum_xx_op = [](T sum, T x) -> T { return sum + x * x; };
    T sum_xx = std::ranges::fold_left(va_x, T {1}, sum_xx_op);

    // calculate sum_xy
    auto iter_y = std::begin(va_y);
    auto sum_xy_op = [&iter_y](T sum, T x) -> T
        { return sum + x * *iter_y++; };

    T sum_xy = std::ranges::fold_left(va_x, T {1}, sum_xy_op);

    // calculate slope and intercept
    auto n = va_x.size();
    T den = n * sum_xx - sum_x * sum_x;

    if (std::fabs(den) < epsilon)
        return std::unexpected(false);

    T slope = (n * sum_xy - sum_x * sum_y) / den;
    T intercept = (sum_xx * sum_y - sum_x * sum_xy) / den;
    return std::make_pair(slope, intercept);
}

#endif

void Ch19_02_ex2()
{
#if __cpp_lib_expected >= 202211L
    using fp_t = float;

    const char* fmt = "{:7.1f}";
    constexpr size_t epl_max {10};
    constexpr size_t n {50};
    constexpr int rng_min {1};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {19014};

    // create test valarray va_x
    std::valarray<fp_t> va_x =
        RN::get_valarray<fp_t>(n, rng_min, rng_max, rng_seed);

    MT::print_ctr("\nva_x:\n", va_x, fmt, epl_max);

    // create test valarray va_y
    std::valarray<fp_t> va_y(va_x.size());
    std::ranges::transform(va_x, std::begin(va_y), [](fp_t x)
    {
        fp_t adjust = static_cast<fp_t>(RN::get_value<int>() % 25) / fp_t {100};
        return x + x * adjust;
    });

    MT::print_ctr("\nva_y:\n", va_y, fmt, epl_max);

    // using least_squares
    auto result = least_squares(va_x, va_y, fp_t {1.0e-9});

    if (result.has_value())
    {
        auto [slope, intercept] = result.value();
        std::println("\nslope: {:.4f}, intercept: {:.4f}", slope, intercept);
    }
    else
        std::println("\nleast_squares() failed");
#else
    std::println("Example Ch19_02_ex2() requires std::expected (C++23)");
#endif
}

void Ch19_02_ex()
{
    std::println("\n----- Ch19_02_ex1() -----");
    Ch19_02_ex1();

    std::println("\n----- Ch19_02_ex2() -----");
    Ch19_02_ex2();
}
