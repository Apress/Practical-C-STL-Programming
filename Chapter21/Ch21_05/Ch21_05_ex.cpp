//-----------------------------------------------------------------------------
// Ch21_05_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <chrono>
#include <cmath>
#include <future>
#include <numbers>
#include <stdexcept>
#include <vector>
#include "Ch21_05.h"
#include "RN.h"

template <typename T> requires std::floating_point<T>
std::vector<T> dct(const std::vector<T>& x)
{
    const size_t N = x.size();
    std::vector<T> X(N);

    // calculate DCT
    for (size_t k = 0; k < N; ++k)
    {
        T sum {};

        for (size_t n = 0; n < N; ++n)
        {
            T t1 = std::numbers::pi_v<T> * k / N;
            sum += x[n] * std::cos(t1 * (n + 0.5));
        }

        X[k] = T(1.0) / N * sum;
    }

    return X;
}

template <typename T> requires std::floating_point<T>
std::vector<T> dct_inv(const std::vector<T>& X)
{
    const size_t N = X.size();
    std::vector<T> x(N);

    // calculate inverse DCT
    for (size_t k = 0; k < N; ++k)
    {
        T sum {};

        for (size_t n = 1; n < N; ++n)
        {
            T t1 = std::numbers::pi_v<T> * n / N;
            sum += X[n] * std::cos(t1 * (k + 0.5));
        }

        x[k] = X[0] + T(2) * sum;
    }

    return x;
}

template <typename T> requires std::floating_point<T>
void compare_vectors(const std::vector<T>& vec1, const std::vector<T>& vec2,
    T epsilon = 1.0e-7)
{
    auto eq_pred = [epsilon](T a, T b) { return std::fabs(a - b) <= epsilon; };
    bool ok = std::ranges::equal(vec1, vec2, eq_pred);

    std::print("\ncompare_vectors(): ");
    std::println("{:s}", ok ? "ok" : "failed!");
}

// #define PRINT_DCT_VALUES

void Ch21_05_ex1()
{
    using fp_t = double;

    // create test vector
    constexpr int rng_min {0};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {879};
    constexpr size_t npts {20};

    std::vector<fp_t> x0 = RN::get_vector<fp_t>(npts, rng_min, rng_max, rng_seed);

    // perform DCT and inverse DCT, compare results
    auto X0 = dct<fp_t>(x0);
    auto x1 = dct_inv<fp_t>(X0);
    compare_vectors(x0, x1);

#ifdef PRINT_DCT_VALUES
    for (size_t i = 0; i < npts; ++i)
        std::println("{:3d}: {:12.6f}, {:12.6f}, {:12.6f}", i, x0[i], X0[i], x1[i]);
#endif
}

template <typename T> requires std::floating_point<T>
std::chrono::milliseconds wait_for_future(std::future<std::vector<T>>& future,
    std::chrono::milliseconds wait_time)
{
    std::chrono::milliseconds total_wait {};

    while (1)
    {
        auto status = future.wait_for(wait_time);

        if (status == std::future_status::ready)
            return total_wait;

        if (status != std::future_status::timeout)
            throw std::runtime_error("wait_for_future() - unexpected status");

        // other processing can be added here
        total_wait += wait_time;
        std::println("waiting for result ({})", total_wait);
    }
}

void Ch21_05_ex2()
{
    using fp_t = double;
    constexpr auto wait_time {std::chrono::milliseconds(500) };

    // create test vector
    constexpr int rng_min {0};
    constexpr int rng_max {1000};
    constexpr unsigned int rng_seed {879};
    constexpr size_t npts {25'000};
    std::vector<fp_t> x0 = RN::get_vector<fp_t>(npts, rng_min, rng_max, rng_seed);

    // perform DCT
    auto future_dct = std::async(std::launch::async, dct<fp_t>, x0);

    auto total_wait_time1 = wait_for_future(future_dct, wait_time);
    std::println("dct() complete - total_wait_time1 = {}", total_wait_time1);

    // perform inverse DCT
    auto X0 = future_dct.get();
    auto future_dct_inv = std::async(std::launch::async, dct_inv<fp_t>, X0);

    auto total_wait_time2 = wait_for_future(future_dct_inv, wait_time);
    std::println("dct_inv() complete - total_wait_ms = {}", total_wait_time2);

    // confirm results
    auto x1 = future_dct_inv.get();
    compare_vectors(x0, x1);
}

void Ch21_05_ex()
{
    std::println("\n----- Ch21_05_ex1() -----");
    Ch21_05_ex1();

    std::println("\n----- Ch21_05_ex2() -----");
    Ch21_05_ex2();
}
