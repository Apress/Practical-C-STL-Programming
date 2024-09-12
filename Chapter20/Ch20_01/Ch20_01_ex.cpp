//-----------------------------------------------------------------------------
// Ch20_01_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <execution>
#include <iostream>
#include "Ch20_01.h"
#include "BmTimer.h"
#include "MT.h"
#include "RN.h"

namespace ex = std::execution;

void Ch20_01_ex1()
{
    const char* fmt = "{:9.1f} ";
    constexpr size_t epl_max {8};
    constexpr int rng_min {-200};
    constexpr int rng_max {200};
    constexpr size_t vec_size {50};

    // create test vectors
    std::vector<double> vec0 = RN::get_vector<double>(vec_size, rng_min, rng_max);
    MT::print_ctr("\nvec0 (initial values):\n", vec0, fmt, epl_max);
    std::vector<double> vec1(vec0.size());
    std::vector<double> vec2(vec0.size());
    std::vector<double> vec3(vec0.size());
    std::vector<double> vec4(vec0.size());

    // transformation lambda
    auto tr_op = [](auto x) { return 3 * x * x + 2 * x + 1; };

    // using transform - sequenced
    std::transform(ex::seq, vec0.begin(), vec0.end(), vec1.begin(), tr_op);

    // using transform - unsequenced
    std::transform(ex::unseq, vec0.begin(), vec0.end(), vec2.begin(), tr_op);

    // using transform - parallel sequenced
    std::transform(ex::par, vec0.begin(), vec0.end(), vec3.begin(), tr_op);

    // using transform - parallel unsequenced
    std::transform(ex::par_unseq, vec0.begin(), vec0.end(), vec4.begin(), tr_op);

    // verify results
    std::print("\nresult vector compare check: ");
    if (vec1 == vec2 && vec1 == vec3 && vec1 == vec4)
        std::println("OK");
    else
        std::println("Failed!");
}

void Ch20_01_ex2()
{
    // create test vector
    constexpr size_t n {1'000'000};
    std::vector<int> vec0(n);
    std::iota(vec0.begin(), vec0.end(), 0);
    std::vector<int> vec1 {};

    // function object for for_each
    auto fe_op = [&vec1](int x)
            { vec1.push_back(3 * x * x + 2 * x + 1); };

    // OK
    std::for_each(ex::seq, vec0.begin(), vec0.end(), fe_op);
    std::println("after std::for_each(ex::seq)\n");

    // trouble - data race condition - calls std::terminate()
//    std::for_each(ex::par, vec0.begin(), vec0.end(), fe_op);
//    std::println("after std::for_each(ex::par)\n");
}

void Ch20_01_ex3()
{
    constexpr int rng_min {1};
    constexpr int rng_max {2000};
    constexpr size_t vec_size = {10'000'000};

    // create test vectors
    auto vec0 = RN::get_vector<float>(vec_size, rng_min, rng_max);
    auto vec1(vec0);
    auto vec2(vec0);
    auto vec3(vec0);
    auto vec4(vec0);

    // create BmTimer using steady clock
    constexpr size_t num_iter {25};
    constexpr size_t num_alg {5};
    BmTimerSteadyClk bm_timer(num_iter, num_alg);

    // transform lambda
    auto transform_policy = [&bm_timer]<typename T>(std::vector<T>& vec,
        size_t alg_id, bool use_default, auto policy)
    {
        auto tr_op = [](T x) { return x + std::cbrt(x); };

        if (use_default)
        {
            for (size_t i = 0; i < num_iter; ++i)
            {
                bm_timer.start(i, alg_id);
                std::transform(vec.begin(), vec.end(), vec.begin(), tr_op);
                bm_timer.stop(i, alg_id);

               if (i % 4 == 0)
                    std::cout << '.' << std::flush;
            }
        }
        else
        {
            for (size_t i = 0; i < num_iter; ++i)
            {
                bm_timer.start(i, alg_id);
                std::transform(policy, vec.begin(), vec.end(), vec.begin(), tr_op);
                bm_timer.stop(i, alg_id);

               if (i % 4 == 0)
                    std::cout << '.' << std::flush;
            }
        }
    };

    // benchmark std::transform() using execution policies
    std::print("example Ch20_01_ex3 is running, please wait ");

    transform_policy(vec0, 0, true,  ex::seq);
    transform_policy(vec1, 1, false, ex::seq);
    transform_policy(vec2, 2, false, ex::unseq);
    transform_policy(vec3, 3, false, ex::par);
    transform_policy(vec4, 4, false, ex::par_unseq);

    // save results to CSV file
    std::println("");
    std::string fn = "Ch20_01_ex3_results.csv";
    bm_timer.save_to_csv(fn, "{:.2f}", BmTimerSteadyClk::EtUnit::MilliSec);
    std::println("Benchmark times save to file {:s}", fn);
}

void Ch20_01_ex4()
{
    constexpr int rng_min {-1'000'000};
    constexpr int rng_max { 1'000'000};
    constexpr size_t vec_size = {5'000'000};

    // create test vector
    auto vec0 = RN::get_vector<int>(vec_size, rng_min, rng_max);

    // create BmTimer using steady clock
    constexpr size_t num_iter {40};
    constexpr size_t num_alg {5};
    BmTimerSteadyClk bm_timer(num_iter, num_alg);

    std::print("example Ch20_01_ex4 is running, please wait ");

    // sort lambda
    auto sort_policy = [&bm_timer]<typename T>(const std::vector<T>& vec0,
        size_t alg_id, bool use_default, auto policy)
    {
        if (use_default)
        {
            for (size_t i = 0; i < num_iter; ++i)
            {
                auto vec1(vec0);

                bm_timer.start(i, alg_id);
                std::sort(vec1.begin(), vec1.end());
                bm_timer.stop(i, alg_id);

               if (i % 4 == 0)
                    std::cout << '.' << std::flush;
            }
        }
        else
        {
            for (size_t i = 0; i < num_iter; ++i)
            {
                auto vec1(vec0);

                bm_timer.start(i, alg_id);
                std::sort(policy, vec1.begin(), vec1.end());
                bm_timer.stop(i, alg_id);

               if (i % 4 == 0)
                    std::cout << '.' << std::flush;
            }
        }
    };

    sort_policy(vec0, 0, true, ex::seq);
    sort_policy(vec0, 1, false, ex::seq);
    sort_policy(vec0, 2, false, ex::unseq);
    sort_policy(vec0, 3, false, ex::par);
    sort_policy(vec0, 4, false, ex::par_unseq);

    // save results to CSV file
    std::println("");
    std::string fn {"Ch20_01_ex4_results.csv"};
    bm_timer.save_to_csv(fn, "{:.2f}", BmTimerSteadyClk::EtUnit::MilliSec);
    std::println("Benchmark times save to file {:s}", fn);
}

void Ch20_01_ex()
{
    std::println("\n----- Ch20_01_ex1() -----");
    Ch20_01_ex1();

    std::println("\n----- Ch20_01_ex2() -----");
    Ch20_01_ex2();

    std::println("\n----- Ch20_01_ex3() -----");
    Ch20_01_ex3();

    std::println("\n----- Ch20_01_ex4() -----");
    Ch20_01_ex4();
}
