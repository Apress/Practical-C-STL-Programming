//-----------------------------------------------------------------------------
// Ch21_01_ex.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <format>
#include <numeric>
#include <semaphore>
#include <string>
#include <thread>
#include <vector>
#include "Ch21_01.h"
#include "MT.h"
#include "MTH.h"
#include "THR.h"

template <typename T> struct BinSemVec
{
    BinSemVec() = delete;

    explicit BinSemVec(size_t vec_size)
    {
        Vec.resize(vec_size);

#ifdef __cpp_lib_ranges_iota        // C++23
        std::ranges::iota(Vec, 0);
#else
        std::iota(Vec1.begin(), Vec1.end(), 0);
#endif
    }

    static void thread_proc(BinSemVec<T>& bin_sem_vec)
    {
        std::print("\nwaiting to acquire Sem1\n");
        bin_sem_vec.Sem1.acquire();

        // sleep period added to simulate long processing time
        THR::sleep_for_random_ms(1000, 1500);
        std::ranges::transform(bin_sem_vec.Vec, bin_sem_vec.Vec.begin(),
            [](T x) { return x * x; });

        std::print("\nreleasing Sem2\n");
        bin_sem_vec.Sem2.release();
    }

    std::vector<T> Vec {};                  // test vector
    std::binary_semaphore Sem1 {0};         // thread start start
    std::binary_semaphore Sem2 {0};         // thread end signal
};

void Ch21_01_ex1()
{
    const char* fmt = "{:5d} ";
    constexpr size_t epl_max {12};

    // instantiate BinSemVec
    BinSemVec<int> bin_sem_vec1(24);
    MT::print_ctr("\nbin_sem_vec1.Vec (initial values):\n",
        bin_sem_vec1.Vec, fmt, epl_max);

    // start thread_proc
    std::println("\nlaunching thread_proc");
    std::jthread thread1(BinSemVec<int>::thread_proc, std::ref(bin_sem_vec1));
    THR::sleep_for_random_ms(1000, 1500);
    bin_sem_vec1.Sem1.release();

    // wait for Sem2
    std::println("\nwaiting to acquire Sem2");
    bin_sem_vec1.Sem2.acquire();
    MT::print_ctr("\nbin_sem_vec1.Vec (after processing):\n",
        bin_sem_vec1.Vec, fmt, epl_max);
}

void count_primes_thread(std::string name, int begin, int end, int& count,
    std::counting_semaphore<>& cs)
{
    std::print("{:s} - ENTER count_primes_thread()\n", name);
    std::print("{:s} - counting primes between [{:d}, {:d})\n", name, begin, end);

    // count primes
    count = 0;
    for (int i = begin; i < end; ++i)
    {
        if (MTH::is_prime(i))
            count++;
    }

    // release semaphore (sleep added to force timeout errors)
    THR::sleep_for_random_ms(50, 60);
    cs.release();
    std::print("{:s} - EXIT count_primes_thread()\n", name);
}

void Ch21_01_ex2()
{
    // size counts and data vectors
    constexpr size_t num_total_threads {12};                // total threads to run
    constexpr size_t num_active_threads_max {3};            // max active threads

    std::vector<std::jthread> threads(num_total_threads);   // thread pool
    std::vector<std::string> names(num_total_threads);      // thread names
    std::vector<int> counts(num_total_threads);             // prime num counts

    // counting semaphore to restrict number of active threads
    std::counting_semaphore<> cs(num_active_threads_max);

    // vars for count ranges
    constexpr int step {25000};
    int begin {};
    int end {step};
    size_t i {};

    while (i < threads.size())
    {
        if (!cs.try_acquire_for(std::chrono::milliseconds(5)))
            std::println("cs.try_acquire_for() time out occurred");
        else
        {
            // launch thread to count primes between [begin, end)
            names[i] = std::format("Thread{:02d}", i);

            threads[i] = std::jthread(count_primes_thread, names[i], begin, end,
                std::ref(counts[i]), std::ref(cs));

            begin = end;
            end += step;
            ++i;
        }
    }

    // wait for all threads to finish
    for (auto& thread : threads)
        thread.join();

    // print results
    begin = 0;
    end = step;
    std::println("");

    for (size_t i = 0; i < threads.size(); ++i)
    {
        std::println("{:10s}: [{:8d}, {:8d}) = {:5d}  ",
            names[i], begin, end, counts[i]);
        begin = end;
        end += step;
    }
}

void Ch21_01_ex()
{
    std::println("\n----- Ch21_01_ex1() -----");
    Ch21_01_ex1();

    std::println("\n----- Ch21_01_ex2() -----");
    Ch21_01_ex2();
}
