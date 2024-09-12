//-----------------------------------------------------------------------------
// Ch19_03_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <numeric>
#include <stdexcept>
#include <valarray>
#include "Ch19_03.h"
#include "Matrix.h"

void Ch19_03_ex1()
{
    auto print_va = [](const char* msg, const std::valarray<int>& va)
    {
        std::print("{:s}", msg);
        for (int x : va)
            std::print("{:3d}", x);
        std::println("");
    };

    // create test valarray<>
    std::valarray<int> va1(20);
    std::iota(std::begin(va1), std::end(va1), 0);
    print_va("va1: ", va1);

    // using std::slice - first four elements of va1
    size_t size = 4;
    std::slice sl1(0, size, 1);
    std::slice_array<int> sa1 = va1[sl1];
    std::valarray<int> va2 = sa1;
    print_va("va2: ", va2);

    // using std::slice - last n elements of va1
    size = 7;
    std::valarray<int> va3 = va1[std::slice(va1.size() - size, size, 1)];
    print_va("va3: ", va3);

    // using std::slice - even elements of va1
    size = va1.size() / 2 + va1.size() % 2;
    std::valarray<int> va4 = va1[std::slice(0, size, 2)];
    print_va("va4: ", va4);

    // using std::slice - odd elements va1
    size = va1.size() / 2;
    std::valarray<int> va5 = va1[std::slice(1, size, 2)];
    print_va("va5: ", va5);

    // using std::slice - every fifth element of va1
    size = va1.size() / 5;
    std::valarray<int> va6 = va1[std::slice(0, size, 5)];
    print_va("va6: ", va6);
}

void Ch19_03_ex2()
{
    // create test matrix
    Matrix<double> m1(4, 4);
    m1.iota(1);
    std::println("\nm1:\n{:9.1f}", m1);

    // print rows and columns of matrix m1
    for (size_t i = 0; i < m1.NumRows(); ++i)
    {
        Matrix<double> m1_row(1, m1.NumCols(), m1.row(i));
        std::println("\nm1 row {:d}:\n{:9.1f}", i, m1_row);
    }

    for (size_t i = 0; i < m1.NumCols(); ++i)
    {
        Matrix<double> m1_col(m1.NumRows(), 1, m1.col(i));
        std::println("\nm1 col {:d}:\n{:9.1f}", i, m1_col);
    }

    // create test matricies
    Matrix<double> m2(4, 7);
    m2.iota(10);
    std::println("\nm2:\n{:9.1f}", m2);

    Matrix<double> m3(7, 4);
    m3.iota(20);
    std::println("\nm3:\n{:9.1f}", m3);

    // matrix multiplication
    Matrix<double> m4 = m2 * m3;
    std::println("\nm4:\n{:9.1f}", m4);

    // matrix multiplication (::mul uses for loops and indicies)
    Matrix<double> m5 = Matrix<double>::mul(m2, m3);
    std::println("\nm4 == m5: {:s} (expect true)", m4 == m5);

    // matrix addition
    Matrix<double> m6 = m4 + m1;
    std::println("\nm6:\n{:9.1f}", m6);

    // matrix trace
    std::println("\nm1.trace(): {:.1f}", m1.trace());
}

void Ch19_03_ex()
{
    std::println("\n----- Ch19_03_ex1() -----");
    Ch19_03_ex1();

    std::println("\n----- Ch19_03_ex2() -----");
    Ch19_03_ex2();
}
