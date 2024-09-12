//-----------------------------------------------------------------------------
// Ch01_04_ex.cpp
//-----------------------------------------------------------------------------

#include <utility>
#include "Ch01_04.h"
#include "Image.h"

void Ch01_04_ex1()
{
    // create image objects
    Image im0 {};
    std::println("im0: {} - after ctor", im0);
    Image im1 {100, 200};
    std::println("im1: {} - after ctor", im1);
    Image im2 {300, 400};
    std::println("im2: {} - after ctor", im2);

    // using std::move
    Image im3 = std::move(im1);
    std::println("im3: {} - after move ctor", im3);

#pragma warning(disable:26800)  // disable MSVC warning (use of moved object)
    std::println("im1: {} - after move (bad!)", im1);
#pragma warning(default:26800)
}

void Ch01_04_ex2()
{
    // create image objects
    Image im0 {1000, 2000};
    std::println("im0: {} - after ctor", im0);
    Image im1 {im0};
    std::println("im1: {} - after ctor", im1);

    Image im2 {3000, 4000};
    std::println("im2: {} - after ctor", im2);

    // using relational operators
    std::println("im1 == im2 (expect false): {}", im1 == im2);
    std::println("im1 != im2 (expect true):  {}", im1 != im2);

    // using operator=
    Image im3 {5000, 6000};
    std::println("im3: {} - after ctor", im3);

    im1 = im3;
    std::println("im1: {} - after assignment", im1);
    std::println("im1 == im3 (expect true):  {}", im1 == im3);
    std::println("im1 != im3 (expect false): {}", im1 != im3);
}

void Ch01_04_ex()
{
    std::println("\n---- Ch01_04_ex1() -----");
    Ch01_04_ex1();

    std::println("\n---- Ch01_04_ex2() -----");
    Ch01_04_ex2();
}
