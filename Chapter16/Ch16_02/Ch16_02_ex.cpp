//-----------------------------------------------------------------------------
// Ch16_02_ex.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <typeinfo>
#include "Ch16_02.h"

namespace chrono = std::chrono;

//#define PRINT_DURATION_TYPEID  // remove comment to print duration typeids

void Ch16_02_ex1()
{
    // using chrono::duration
    chrono::duration<int, std::ratio<3600 * 24>> day {1};
    chrono::duration<int, std::ratio<3600 * 24 * 7>> week {1};
    chrono::duration<int, std::ratio<3600 * 24 * 14>> fortnight {1};

    // chrono::duration arithmetic - days
    auto num_days = 2 * fortnight - 4 * day + 3 * week;
    std::println("num_days:    {}", num_days);

    // using chrono::duration_cast<>
    auto num_hours = chrono::duration_cast<chrono::hours>(num_days);
    std::println("num_hours:   {}", num_hours);

    // using chrono::duration (non-int tick type)
    chrono::duration<double, std::ratio<3600>> minutes90 {1.5};

    // more chrono::duration arithmetic
    auto num_hours_d = 20.0 * minutes90 + 0.5 * minutes90;
    auto num_minutes = chrono::duration_cast<chrono::minutes>(num_hours_d);
    std::println("\nnum_hours_d:   {}", num_hours_d);
    std::println("num_minutes:   {}", num_minutes);

#ifdef PRINT_DURATION_TYPEID
    std::println("\ntypeid(num_days):    {}", typeid(num_days).name());
    std::println("typeid(num_hours):   {}", typeid(num_hours).name());
    std::println("typeid(num_hours_d): {}", typeid(num_hours_d).name());
    std::println("typeid(num_minutes): {}", typeid(num_minutes).name());
#endif
}

void Ch16_02_ex2()
{
    using namespace std::chrono_literals;

    // using standard durations
    chrono::days x_days {5};
    chrono::hours x_hours {18};
    chrono::minutes x_minutes {12};
    chrono::seconds x_seconds {7};

    auto a_seconds = x_days + x_hours - x_minutes + x_seconds;
    auto a_minutes = chrono::duration_cast<chrono::minutes>(a_seconds);
    auto a_hours = chrono::duration_cast<chrono::hours>(a_seconds);
    auto a_days = chrono::duration_cast<chrono::days>(a_seconds);

    auto a_err = a_seconds - a_days;

    std::println("\na_seconds:   {:8}  a_minutes: {:8}", a_seconds, a_minutes);
    std::println("a_hours:     {:8}  a_days:    {:8}", a_hours, a_days);
    std::println("a_err:       {:8}", a_err);
 
    // using time suffixes (hours, minutes, seconds)
    auto b_seconds = 17h + 47min + 18s + a_seconds;
    auto b_minutes = chrono::duration_cast<chrono::minutes>(b_seconds);
    auto b_hours = chrono::duration_cast<chrono::hours>(b_seconds);
    auto b_days = chrono::duration_cast<chrono::days>(b_seconds);

    auto b_err = b_seconds - b_days;

    std::println("\nb_seconds:   {:8}  b_minutes: {:8}", b_seconds, b_minutes);
    std::println("b_hours:     {:8}  b_days:    {:8}", b_hours, b_days);
    std::println("b_err:       {:8}", b_err);

    // using time suffixes (milliseconds, microseconds, nanoseconds)
    // period for duration c is std::ratio<1, 1000000000>
    auto c = 12s + 340ms + 5600us + 78901ns;

    auto c_ns = chrono::duration_cast<chrono::nanoseconds>(c);
    auto c_us = chrono::duration_cast<chrono::microseconds>(c);
    auto c_ms = chrono::duration_cast<chrono::milliseconds>(c);
    auto c_sec = chrono::duration_cast<chrono::seconds>(c);

    std::println("\nc_ns: {:15} c_us:  {:15}", c_ns, c_us);
    std::println("c_ms: {:15} c_sec: {:15}", c_ms, c_sec);

    std::println("\nc_sec (decimal): {:%S}", c);    // %S specifies decimal seconds

#ifdef PRINT_DURATION_TYPEID
    std::println("\ntypeid(b_seconds): {}", typeid(b_seconds).name());
    std::println("typeid(b_minutes): {}", typeid(b_minutes).name());
    std::println("typeid(b_hours):   {}", typeid(b_hours).name());
    std::println("typeid(c):         {}", typeid(c).name());
#endif
}

void Ch16_02_ex3()
{
    using namespace std::chrono_literals;

    // print rel ops results
    auto print_rel_ops = [](const auto& ymd1, const auto& ymd2)
    {
        std::print("\nymd1 == ymd2: {:5s}    ", ymd1 == ymd2);
        std::println("ymd1 != ymd2: {:5s}", ymd1 != ymd2);
        std::print("ymd1 <  ymd2: {:5s}    ", ymd1 <  ymd2);
        std::println("ymd1 <= ymd2: {:5s}", ymd1 <= ymd2);
        std::print("ymd1 >  ymd2: {:5s}    ", ymd1 >  ymd2);
        std::println("ymd1 >= ymd2: {:5s}", ymd1 >= ymd2);
    };

    // using chrono date suffixes
    chrono::year_month_day ymd1 {2025y/6/21d};
    chrono::year_month_day ymd2 {2027y/6/21d};
    std::println("ymd1 | ymd2 (initial values):   {} | {}", ymd1, ymd2);
    print_rel_ops(ymd1, ymd2);

    // using chrono date suffixes - more formats
    auto ymd3 {9/20d/2026y};
    auto ymd4 {19d/3/2028y};
    std::println("\nymd3 | ymd4 (initial values):   {} | {}", ymd3, ymd4);

    // ymd calendar arithmetic - months and years
    ymd1 += chrono::months(6);
    ymd2 -= chrono::months(18);
    std::println("\nymd1 | ymd2 (after arithmetic): {} | {}", ymd1, ymd2);
    print_rel_ops(ymd1, ymd2);

    auto ymd5 = ymd3 + chrono::years(4);
    auto ymd6 = ymd4 - chrono::years(1);
    std::println("\nymd5 | ymd6 (initial values):   {} | {}", ymd5, ymd6);

    // ymd calendar arithmetic - days
    auto ymd7 = chrono::sys_days(ymd5) + chrono::days(7);
    auto ymd8 = chrono::sys_days(ymd6) - chrono::days(28);
    std::println("\nymd7 | ymd8 (initial values):   {} | {}", ymd7, ymd8);
}

void Ch16_02_ex()
{
    std::println("\n----- Ch16_02_ex1() -----");
    Ch16_02_ex1();

    std::println("\n----- Ch16_02_ex2() -----");
    Ch16_02_ex2();

    std::println("\n----- Ch16_02_ex3() -----");
    Ch16_02_ex3();
}
