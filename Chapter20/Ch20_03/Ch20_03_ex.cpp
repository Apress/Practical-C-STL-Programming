//-----------------------------------------------------------------------------
// Ch20_03_ex.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <format>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
#include "Ch20_03.h"
#include "MTH.h"
#include "RN.h"
#include "THR.h"

std::vector<int> get_test_vector(unsigned int rng_seed = 1000)
{
    constexpr size_t n {50'000'000};
    constexpr int rng_min {1};
    constexpr int rng_max {100'000'000};

    std::vector<int> vec1 = RN::get_vector<int>(n, rng_min, rng_max, rng_seed);
    return vec1;
}

void count_primes_a(const char* name, const std::vector<int>& vec,
    size_t ib, size_t ie, size_t& num_primes)
{
    std::string id = THR::get_this_thread_id();
    std::println("\nENTER count_primes_a() | name: {:s}, id: {:s}", name, id);

    num_primes = 0;
    for (size_t i = ib; i < ie; ++i)
    {
        if (MTH::is_prime(vec[i]))
            num_primes++;
    }

    std::println("\nEXIT  count_primes_a() | name: {:s}, id: {:s}, num_primes {:d}",
        name, id, num_primes);
}

void Ch20_03_ex1()
{
    // number of concurrent threads may be different than number of
    // physical processor threads
    auto num_concurrent_threads = std::thread::hardware_concurrency();
    std::println("number of supported concurrent threads: {}",
        num_concurrent_threads);

    // create test vector
    std::vector<int> vec1 = get_test_vector();
    size_t num_primes1 {};
    size_t num_primes2 {};

    // count primes using multiple threads
    std::println("\nlaunching thread1 and thread2");

    std::thread thread1(count_primes_a, "thread1", std::cref(vec1),
        0, vec1.size() / 2, std::ref(num_primes1));

    std::thread thread2(count_primes_a, "thread2", std::cref(vec1),
        vec1.size() / 2, vec1.size(), std::ref(num_primes2));

    // count primes from current thread (for comparison purposes)
    // executes in parallel with other threads
    size_t num_primes3 {};
    count_primes_a("Ch20_03_ex1", vec1, 0, vec1.size(), num_primes3);

    // wait for threads to complete
    thread1.join();
    thread2.join();
    std::println("\nthread1 and thread2 joined");

    // check prime number counts
    bool count_check = num_primes1 + num_primes2 == num_primes3;
    std::println("\ncount_check: {:s} (expect true)", count_check);
}

void Ch20_03_ex2()
{
    size_t num_primes1 {};
    size_t num_primes2 {};
    std::vector<int> vec1 = get_test_vector();

    std::println("launching thread1 and thread2");

    std::jthread thread1(count_primes_a, "thread1", std::cref(vec1),
        0, vec1.size() / 2, std::ref(num_primes1));

    std::jthread thread2(count_primes_a, "thread2", std::cref(vec1),
        vec1.size() / 2, vec1.size(), std::ref(num_primes2));

    // thread1.join() and thread2.join() called in destructors
}

void count_primes_b(std::stop_token stop_tkn, const char* name,
    const std::vector<int>& vec, size_t ib, size_t ie, size_t& num_primes)
{
    std::string id = THR::get_this_thread_id();
    std::println("ENTER count_primes_b() | name: {:s}, id: {:s}, ", name, id);

    num_primes = 0;

    for (size_t i = ib; i < ie; ++i)
    {
        if (i % 1000)
        {
            // check for stop request
            if (stop_tkn.stop_requested())
            {
                std::println("\ncount_primes_b() - stop request received");
                std::println("EXIT  count_primes_b() | name: {:s}, id: {:s}, "
                    "num_primes: {:d}", name, id, num_primes);
                return;
            }
        }

        if (MTH::is_prime(vec[i]))
            num_primes += 1;
    }

    std::println("\ncount_primes_b() - normal termination");
    std::println("EXIT  count_primes_b() | name: {:s}, id: {:s}, "
        "num_primes: {:d}", name, id, num_primes);
}

void Ch20_03_ex3()
{
    // launch test thread
    std::println("launching thread1");

    std::vector<int> vec1 = get_test_vector();
    size_t num_primes1 {};
    std::jthread thread1(count_primes_b, "thread1", vec1, 0, vec1.size(),
        std::ref(num_primes1));

    // wait a bit, then send stop request to thread1
    THR::sleep_for_random_ms(1500, 2000);
    thread1.request_stop();

    // explict join() used to ensure value of num_primes1 is final
    thread1.join();
    std::println("\nnum_primes1: {:d}", num_primes1);

    // running count_primes_b() to completion
    std::println("launching thread2");
    size_t num_primes2 {};
    std::jthread thread2(count_primes_b, "thread2", vec1, 0, vec1.size(),
        std::ref(num_primes2));

    // explict join() used since jthread destructor calls request_stop()
    thread2.join();
    std::println("\nnum_primes2: {:d}", num_primes2);
}

void Ch20_03_ex()
{
    std::println("\n----- Ch20_03_ex1() -----");
    Ch20_03_ex1();

    std::println("\n----- Ch20_03_ex2() -----");
    Ch20_03_ex2();

    std::println("\n----- Ch20_03_ex3() -----");
    Ch20_03_ex3();
}
