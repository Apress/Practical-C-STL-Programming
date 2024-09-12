//-----------------------------------------------------------------------------
// Ch01_07_ex.cpp
//-----------------------------------------------------------------------------

#include <compare>
#include <vector>
#include "Ch01_07.h"
#include "Line.h"

void Ch01_07_ex1()
{
    std::vector<int> a_vals {5, -8,  37};
    std::vector<int> b_vals {7, -15, 37};

    for (std::size_t i = 0; i < a_vals.size(); ++i)
    {
        auto cmp_ab = a_vals[i] <=> b_vals[i];

        std::println("\ntest case #{:d}:  a = {:d}, b = {:d}",
            i, a_vals[i], b_vals[i]);

        std::println("cmp_ab <   0 | {:s}", cmp_ab <  0);
        std::println("cmp_ab ==  0 | {:s}", cmp_ab == 0);
        std::println("cmp_ab >   0 | {:s}", cmp_ab >  0);
    }
}

void Ch01_07_ex2()
{
    std::vector<double> a_vals {5.0, -8.0,  37.0};
    std::vector<double> b_vals {7.0, -15.0, 37.0};

    for (std::size_t i = 0; i < a_vals.size(); ++i)
    {
        auto cmp_ab = a_vals[i] <=> b_vals[i];

        std::println("\ntest case #{:d}:  a = {:.1f}, b = {:.1f}",
            i, a_vals[i], b_vals[i]);

        std::println("cmp_ab <   0 | {:s}", cmp_ab <  0);
        std::println("cmp_ab ==  0 | {:s}", cmp_ab == 0);
        std::println("cmp_ab >   0 | {:s}", cmp_ab >  0);
    }
}

void Ch01_07_ex3()
{
    std::vector<Line<int>> lines1
    {
        Line<int> {0, 0, 3, 4}, Line<int> {90, 100, 125, 130},
        Line<int> {8, 41, 17, 44}
    };

    std::vector<Line<int>> lines2
    {
        Line<int> {0, 0, 6, 8}, Line<int> {100, 100, 110, 115},
        Line<int> {8, 41, 17, 44}
    };

    for (std::size_t i = 0; i < lines1.size(); ++i)
    {
        auto& line1 = lines1[i];
        auto& line2 = lines2[i];

        std::println("\nline1: {}\nline2: {}", line1, line2);
        std::println("line1 == line2): {:s}", line1 == line2);
        std::println("line1 != line2): {:s}", line1 != line2);
        std::println("line1 <  line2): {:s}", line1 <  line2);
        std::println("line1 <= line2): {:s}", line1 <= line2);
        std::println("line1 >  line2): {:s}", line1 >  line2);
        std::println("line1 >= line2): {:s}", line1 >= line2);
    }
}

void Ch01_07_ex()
{
    std::println("\n---- Ch01_07_ex1() -----");
    Ch01_07_ex1();

    std::println("\n---- Ch01_07_ex2() -----");
    Ch01_07_ex2();

    std::println("\n---- Ch01_07_ex3() -----");
    Ch01_07_ex3();
}
