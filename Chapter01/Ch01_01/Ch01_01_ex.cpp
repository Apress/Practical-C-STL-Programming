//-----------------------------------------------------------------------------
// Ch01_01_ex.cpp
//-----------------------------------------------------------------------------

#include <string>
#include "Ch01_01.h"
#include "Point2D.h"

// function template - adds values
template <typename T> T add_values(T a, T b, T c)
{
    return a + b + c;
}

void Ch01_01_ex1()
{
    // uniform initialization
    int a {10};
    int b {20};
    int c {30};
//  int x = 2.1;        // compiler warning (maybe), x = 2
//  int y {2.1};        // compiler error

    // using template function add_values()
    int sum1 = add_values(a, b, c);
    std::println("a: {}  b: {}  c: {}  sum1: {}", a, b, c, sum1);

    // using template function add_values()
    double d {100.0};
    double e {200.0};
    double f {300.0};
    double sum2 = add_values(d, e, f);
    std::println("d: {}  e: {}  f: {}  sum2: {}", d, e, f, sum2);

    // add_values() works for any class that defines operator+
    std::string s1 {"one "};
    std::string s2 {"two "};
    std::string s3 {"three"};
    std::string s4 = add_values(s1, s2, s3);
    std::print("s1: \"{}\" s2: \"{}\" s3: \"{}\"", s1, s2, s3);
    std::println(" - s4: \"{}\"", s4);
}

// abbreviated function template - calculates mean
double calc_mean(auto a, auto b, auto c)
{
    return (a + b + c) / 3.0;
}

void Ch01_01_ex2()
{
    // using calc_mean() - same data types
    int a {12};
    int b {28};
    int c {36};
    double mean1 = calc_mean(a, b, c);
    std::println("a: {}  b: {}  c: {}  mean1: {}", a, b, c, mean1);

    // using calc_mean() - different data types
    float x {201.1f};
    long long y {108};
    unsigned short z {307};
    double mean2 = calc_mean(x, y, z);
    std::println("x: {}  y: {}  z: {}  mean3: {}", x, y, z, mean2);

    // calc_mean() - operator+ must be defined for all argument types
//  auto mean3 = calc_mean(a, b, "thirty");   // compiler error
}

void Ch01_01_ex3()
{
    // using template function add_values() with type Point2D<int>
    Point2D<int> p1 {10, 20};
    Point2D<int> p2 {30, 40};
    Point2D<int> p3 {50, 60};
    Point2D<int> p4 = add_values(p1, p2, p3);
    std::println("p1: {}  p2: {}  p3: {}  p4: {}", p1, p2, p3, p4);

    // using Point2D equality operators
    std::println("p1 == p2: {}", p1 == p2);
    std::println("p1 != p2: {}", p1 != p2);

    // using Point2D accessors & mutators
    int x = p1.X() * 10;
    int y = p1.Y() * 20;
    std::println("x: {}, y: {}", x, y);
    p1.X() -= 1;
    p1.Y() -= 2;
    std::println("p1: {}", p1);

    // using Point2D::distance()
    std::println("p1.distance(p2): {}", p1.distance());

    // using template function add_values() with type Point2D<double>
    Point2D<double> p5 {100.0, 200.0};
    Point2D<double> p6 {300.0, 400.0};
    Point2D<double> p7 {500.0, 600.0};
    Point2D<double> p8 = add_values(p5, p6, p7);
    std::println("p5: {}  p6: {}  p7: {}  p8: {}", p5, p6, p7, p8);
}

void Ch01_01_ex()
{
    std::println("\n---- Ch01_01_ex1() -----");
    Ch01_01_ex1();

    std::println("\n---- Ch01_01_ex2() -----");
    Ch01_01_ex2();

    std::println("\n---- Ch01_01_ex3() -----");
    Ch01_01_ex3();
}
