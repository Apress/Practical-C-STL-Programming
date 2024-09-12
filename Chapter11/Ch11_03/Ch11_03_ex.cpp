//-----------------------------------------------------------------------------
// Ch11_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <fstream>
#include <vector>
#include "Ch11_03.h"
#include "MF.h"
#include "MT.h"
#include "MTH.h"

void Ch11_03_ex1()
{
    const char* fmt = "{:8.2f}";
    constexpr size_t epl_max {10};

    // using std:generate
    // note: no arguments allowed for gen_op()
    std::vector<double> vec1(20);
   
    auto gen_op = [next_val = 0.0]() mutable
        { double x = next_val; next_val += 0.25; return x; };

    std::generate(vec1.begin(), vec1.end(), gen_op);
    MT::print_ctr("vec1:\n", vec1, fmt, epl_max);
}

void Ch11_03_ex2()
{
    const char* fmt = "{:2c}";
    constexpr size_t epl_max {30};

    // using std::ranges::generate
    std::vector<char> vec1(26);

    auto gen_op = [next_char = 'A']() mutable
        { char c = next_char++; return (c & 0x01) ? c : MF::to_lower(c); };

    std::ranges::generate(vec1, gen_op);
    MT::print_ctr("vec1: ", vec1, fmt, epl_max);
}

void Ch11_03_ex3()
{
    constexpr double amplitude {1.0};
    constexpr double frequency {5.0};
    constexpr double phase {0.0};
    constexpr double t_start {0.0};
    constexpr double t_end {1.0};
    constexpr double t_step {0.001};

    // create sine wave vector (uses std::generate_n)
    std::vector<double> vec1 = MTH::generate_sine_wave(amplitude, frequency,
        phase, t_start, t_end, t_step);

    std::println("vec.size(): {:d}", vec1.size());

    // write sine wave vector to CSV file
    std::string fn = MF::mk_test_filename("ch11_03_ex2.csv");
    std::ofstream ofs {fn, std::ios_base::out | std::ios_base::trunc};

    if (!ofs.good())
    {
        std::println("file open failed: {:s}", fn);
        return;
    }

    double t {t_start};

    for (auto v : vec1)
    {
        std::println(ofs, "{:.6f}, {:.6f}", t, v);
        t += t_step;
    }
    
    ofs.close();
    std::println("results saved to file {:s}", fn);
}

void Ch11_03_ex()
{
    std::println("\n----- Ch11_03_ex1() -----");
    Ch11_03_ex1();

    std::println("\n----- Ch11_03_ex2() -----");
    Ch11_03_ex2();

    std::println("\n----- Ch11_03_ex3() -----");
    Ch11_03_ex3();
}
