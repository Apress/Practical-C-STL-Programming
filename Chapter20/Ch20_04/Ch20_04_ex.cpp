//-----------------------------------------------------------------------------
// Ch20_04_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <atomic>
#include <format>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include "Ch20_04.h"
#include "THR.h"

struct Values
{
    int Ival {};
    double Dval {};

    std::atomic<int> IvalAtomic {};
    std::atomic<double> DvalAtomic {};
};

void thread1_func(Values& v, int n)
{
    for (int i = 0; i < n; ++i)
    {
        // non-atomic adds
        v.Ival += 1;
        v.Dval += 1.0;

        // atomic adds
        v.IvalAtomic += 1;
        v.DvalAtomic += 1.0;
    }
}

void Ch20_04_ex1()
{
    Values v {};

    // print lock_free status
    std::println("v.IvalAtomic.is_lock_free(): {:s}", v.IvalAtomic.is_lock_free());
    std::println("v.DvalAtomic.is_lock_free(): {:s}", v.DvalAtomic.is_lock_free());

    std::println("\nstd::atomic<int>::is_always_lock_free:    {:s}",
        std::atomic<int>::is_always_lock_free);

    std::println("std::atomic<double>::is_always_lock_free: {:s}",
        std::atomic<double>::is_always_lock_free);

    constexpr int n {100000};
    constexpr int n_threads {5};

    auto run_threads = [&v, n]()
    {
        {
            // elements of thread_pool default initialized, not actual threads
            std::array<std::jthread, n_threads> thread_pool {};

            // std::jthread::operator= performs move
            for (size_t i = 0; i < thread_pool.size(); ++i)
                thread_pool[i] = std::jthread(thread1_func, std::ref(v), n);
        }

        // all threads joined here
    };

    // run threads, print results
    run_threads();

    std::println("\nv.Ival:       {:7d}  v.Dval:       {:9.1f}", v.Ival, v.Dval);
    std::println("v.IvalAtomic: {:7d}  v.DvalAtomic: {:9.1f}",
            int(v.IvalAtomic), double(v.DvalAtomic));

    std::println("\nexpected result for all values: {:d}", n * n_threads);
}

void thread2_func(std::atomic<int>& x, size_t delay_ms)
{
    std::println("\nENTER thread2_func() | x: {:d}, delay_ms = {:d}", int(x), delay_ms);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));

    // change value and send notification
    x += 1;
    x.notify_one();

    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    std::println("EXIT thread2_func()  | x: {:d}, delay_ms = {:d}", int(x), delay_ms);
}

void Ch20_04_ex2()
{
    constexpr size_t delay_ms {1000};

    // launch test thread
    constexpr int test_val1 {100};
    std::atomic<int> at_int1 {test_val1};

    std::jthread thread2(thread2_func, std::ref(at_int1), delay_ms);

    // wait for change notification
    at_int1.wait(test_val1);
    std::println("at_int1.wait() complete | at_int1: {:d}", int(at_int1));
}

void thread3_func(std::string name, std::atomic<bool>& x)
{
    std::print("ENTER thread3_func() | name: {:s}, x: {:s}\n", name, bool(x));

    x.wait(false);
    std::print("recevied notification | name: {:s}\n", name);

    // sleep_for_random_ms() used to simulate work following wait()
    THR::sleep_for_random_ms(500, 1000);
    std::print("EXIT thread3_func() | name: {:s}, x: {:s}\n", name, bool(x));
}

void Ch20_04_ex3()
{
    // launch test threads using thread3_func
    std::atomic<bool> at_bool1 {};
    std::array<std::jthread, 10> thread_pool {};

    for (size_t i = 0; i < thread_pool.size(); ++i)
    {
        std::string name = std::format("thread{:02d}", i);
        thread_pool[i] = std::jthread(thread3_func, name, std::ref(at_bool1));
    }

    // allow time for all threads to begin wait
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // change value and notify all waiting threads
    at_bool1 = true;
    at_bool1.notify_all();
    std::println("Ch20_04_ex3() - after at_bool1.notify_all()");

    // all threaded joined here
}

void Ch20_04_ex()
{
    std::println("\n----- Ch20_04_ex1() -----");
    Ch20_04_ex1();

    std::println("\n----- Ch20_04_ex2() -----");
    Ch20_04_ex2();

    std::println("\n----- Ch20_04_ex3() -----");
    Ch20_04_ex3();
}
