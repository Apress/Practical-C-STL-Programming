//-----------------------------------------------------------------------------
// Ch01_05_ex.cpp
//-----------------------------------------------------------------------------

#include <cstdint>
#include <utility>
#include "Ch01_05.h"
#include "ImageT.h"

void Ch01_05_ex1()
{
    // create image objects
    Image<uint8_t> im0 {};
    std::println("im0: {} - after ctor", im0);
    Image<uint8_t> im1 {100, 200};
    std::println("im1: {} - after ctor", im1);
    Image<uint8_t> im2 {300, 400};
    std::println("im2: {} - after ctor", im2);

    // using std::move
    Image<uint8_t> im3 = std::move(im1);
    std::println("im3: {} - after move ctor", im3);

#pragma warning(disable:26800)  // disable MSVC warning (use of moved object)
    std::println("im1: {} - after move (bad!)", im1);
#pragma warning(default:26800)
}

void Ch01_05_ex2()
{
    // create image objects
    Image<uint8_t> im0 {1000, 2000};
    std::println("im0: {} - after ctor", im0);
    Image<uint8_t> im1 {im0};
    std::println("im1: {} - after ctor", im1);
    Image<uint8_t> im2 {3000, 4000};
    std::println("im2: {} - after ctor", im2);

    // using relational operators
    std::println("im1 == im2 (expect false): {}", im1 == im2);
    std::println("im1 != im2 (expect true):  {}", im1 != im2);

    // using operator=
    Image<uint8_t> im3 {5000, 6000};
    std::println("im3: {} - after ctor", im3);

    im1 = im3;
    std::println("im1: {} - after assignment", im1);
    std::println("im1 == im3 (expect true):  {}", im1 == im3);
    std::println("im1 != im3 (expect false): {}", im1 != im3);
}

void Ch01_05_ex3()
{
    // create image objects (uint16_t)
    Image<uint16_t> im0 {1000, 2000};
    std::println("im0: {} - after ctor", im0);

    Image<uint16_t> im1 {3840, 2160};
    std::println("im1: {} - after ctor", im1);

    // using operator=
    im0 = im1;
    std::println("im0: {} - after assignment", im0);
    std::println("im0 == im1 (expect true):  {}", im0 == im1);
    std::println("im0 != im1 (expect false): {}", im0 != im1);

    // create image objects (uint32_t)
    Image<uint32_t> im2 {3840, 2160};
    std::println("im2: {} - after ctor", im2);
    Image<uint32_t> im3 {1920, 1080};
    std::println("im3: {} - after ctor", im3);

    // using operator=
    Image<uint32_t> im4 {im3};
    std::println("im4: {} - after ctor", im4);
    std::println("im4 == im2 (expect false): {}", im4 == im2);
    std::println("im4 == im3 (expect true):  {}", im4 == im3);

//  Image<int16_t> im5;       // compiler error - constraints not satisfied
//  Image<std::string> im5;   // compiler error - constraints not satisfied
}

void Ch01_05_ex()
{
    std::println("\n---- Ch01_05_ex1() -----");
    Ch01_05_ex1();

    std::println("\n---- Ch01_05_ex2() -----");
    Ch01_05_ex2();

    std::println("\n---- Ch01_05_ex3() -----");
    Ch01_05_ex3();
}
