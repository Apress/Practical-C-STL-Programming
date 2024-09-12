//-----------------------------------------------------------------------------
// Ch21_02_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <chrono>
#include <latch>
#include <string>
#include <thread>
#include "Ch21_02.h"
#include "MTH.h"
#include "THR.h"

struct CountPrimesThread
{
    CountPrimesThread() = delete;

    explicit CountPrimesThread(const char* name, int begin, int end) :
        Name(name), Begin(begin), End(end) {};

    static void thread_proc(CountPrimesThread& cpt, std::latch& start_latch,
        std::latch& finish_latch)
    {
        std::print("{:s} - ENTER thread_proc()\n", cpt.Name);
        std::print("{:s} - waiting for start_latch\n", cpt.Name);

        // wait for latch
        start_latch.arrive_and_wait();

        //
        cpt.Count = 0;
        std::print("{:s} - counting primes between [{:d}, {:d})\n",
            cpt.Name, cpt.Begin, cpt.End);

        for (int i = cpt.Begin; i < cpt.End; ++i)
        {
            if (MTH::is_prime(i))
                ++cpt.Count;
        }

        // update finish latch
        finish_latch.count_down();
        std::print("{:s} - EXIT thread_proc()\n", cpt.Name);
    }

    std::string Name {};                    // thread name
    int Begin {}, End {}, Count {};         // count data
    std::jthread Thread {};                 // thread object
};

void Ch21_02_ex1()
{
    std::println("Ch21_02_ex1() - this example may take a while to complete");

    // CountPrimeThread instances
    std::array<CountPrimesThread, 4> cpts
    {
        CountPrimesThread {"CPT0",           0,   50'000'001},
        CountPrimesThread {"CPT1",  50'000'000,   75'000'001},
        CountPrimesThread {"CPT2",  75'000'000,  175'000'001},
        CountPrimesThread {"CPT3", 175'000'000,  250'000'001}
    };

    // thread start and finish latches
    std::latch start_latch(cpts.size() + 1);
    std::latch finish_latch(cpts.size());

    // launch threads
    for (size_t i = 0; i < cpts.size(); ++i)
    {
        cpts[i].Thread = std::jthread(CountPrimesThread::thread_proc,
            std::ref(cpts[i]), std::ref(start_latch), std::ref(finish_latch));
    }

    // commence execution of threads
    THR::sleep_for_random_ms(50, 75);
    start_latch.count_down();

    // wait for finish latch to signal all threads complete
    std::println("Ch21_02_ex1() - waiting for finish_latch");
    finish_latch.wait();
    std::println("Ch21_02_ex1() - all threads finished\n");

    for (size_t i = 0; i < cpts.size(); ++i)
    {
        std::println("Name: {:6s}  Begin: {:10d}  End: {:10d}  Count: {:10d}",
            cpts[i].Name, cpts[i].Begin, cpts[i].End, cpts[i].Count);
    }
}

void Ch21_02_ex()
{
    std::println("\n----- Ch21_02_ex1() -----");
    Ch21_02_ex1();
}
