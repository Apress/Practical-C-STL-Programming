//-----------------------------------------------------------------------------
// Ch21_04_ex.cpp
//-----------------------------------------------------------------------------

#include <future>
#include <numbers>
#include <thread>
#include <utility>
#include "Ch21_04.h"
#include "MTH.h"
#include "THR.h"

void Ch21_04_ex1()
{
    // define result type
    using result_t = std::pair<double, double>;

    // lambda to calculate sphere surface area & volume
    auto calc_sphere_area_vol = [](double r)
    {
        double area = 4 * std::numbers::pi * r * r;
        double volume = area * r / 3;
        return result_t {area, volume};
    };

    // calculate sphere surface areas and volumes
    std::vector<double> radii { 1.0, 2.0, 3.0, 4.0, 5.0 };

    for (double radius : radii)
    {
        // using std::promise
        std::promise<result_t> promise1 {};
        promise1.set_value(calc_sphere_area_vol(radius));

        // using std::future
        std::future<result_t> future1 { promise1.get_future() };
        result_t result1 = future1.get();

        // print result
        std::println("radius: {:6.2f}  surface area: {:6.2f}  volume: {:6.2f}",
            radius, result1.first, result1.second);
    }
}

void Ch21_04_ex2()
{
    // define result type
    using result_t = std::pair<double, double>;

    // lambda to calculate sphere surface area & volume
    auto calc_sphere_area_vol = [](double r, std::promise<result_t>& prom)
    {
        double area = 4 * std::numbers::pi * r * r;
        double volume = area * r / 3;

        prom.set_value(result_t {area, volume});
    };

    // calculate sphere surface areas and volumes
    std::vector<double> radii { 1.0, 2.0, 3.0, 4.0, 5.0 };

    for (double radius : radii)
    {
        // create std::promise and std::future objects
        std::promise<result_t> promise1 {};
        std::future<result_t> future1 { promise1.get_future() };

        // launch thread to perform calculation
        std::jthread thread1(calc_sphere_area_vol, radius, std::ref(promise1));

        // get future result, current thread blocked until result is ready
        result_t result1 = future1.get();

        // print result
        std::println("radius: {:6.2f}  surface area: {:6.2f}  volume: {:6.2f}",
            radius, result1.first, result1.second);

        // thread1 joined here
    }
}

void Ch21_04_ex3()
{
    // define types
    using ll_t = long long;
    struct result_t { std::string ThreadId {}; ll_t Sum {}; };

    // sum_primes lambda
    auto sum_primes = [](ll_t n, const char* policy)
    {
        std::print("ENTER sum_primes() - policy: {:s}\n", policy);

        ll_t sum {0};

        for (ll_t i = 2; i <= n; ++i)
            { if (MTH::is_prime(i)) sum += i; }

        std::print("EXIT  sum_primes() - policy: {:s}\n", policy);
        return result_t { THR::get_this_thread_id(), sum };
    };

    // print current thread_id
    constexpr ll_t n {10'000'000};
    std::println("Ch21_04_ex2() - n: {:d}, thread_id: {:s}\n", n,
        THR::get_this_thread_id());

    // launch async threads using different launch policies
    const char* ps0 = "default";
    const char* ps1 = "async";
    const char* ps2 = "deferred";
    const char* ps3 = "async | deferred";

    auto async_result0 = std::async(sum_primes, n, ps0);
    auto async_result1 = std::async(std::launch::async, sum_primes, n, ps1);
    auto async_result2 = std::async(std::launch::deferred, sum_primes, n, ps2);
    auto async_result3 = std::async(std::launch::async | std::launch::deferred,
        sum_primes, n, ps3);

    // print results
    auto print_result = [](std::future<result_t>& result, const char* policy)
    {
        // print result, get() blocks until result is ready
        result_t r = result.get();

        std::println("result - Sum: {:12d}  ThreadId: {:6s}  policy: {:s}",
            r.Sum, r.ThreadId, policy);
    };

    print_result(async_result0, ps0);
    print_result(async_result1, ps1);
    print_result(async_result2, ps2);
    print_result(async_result3, ps3);
}

void Ch21_04_ex()
{
    std::println("\n----- Ch21_04_ex1() -----");
    Ch21_04_ex1();

    std::println("\n----- Ch21_04_ex2() -----");
    Ch21_04_ex2();

    std::println("\n----- Ch21_04_ex3() -----");
    Ch21_04_ex3();
}
