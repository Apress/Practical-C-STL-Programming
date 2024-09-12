//-----------------------------------------------------------------------------
// Ch16_04_ex.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <string>
#include <typeinfo>
#include <vector>
#include "Ch16_04.h"

namespace chrono = std::chrono;
using namespace std::chrono_literals;

void Ch16_04_ex1()
{
    // display current UTC time
    auto now_sys = chrono::system_clock::now();
    std::println("now_sys:      {0:%F} {0:%X} {0:%Z}", now_sys);

    // using zoned time (current zone)
    chrono::zoned_time now_sys_zt(chrono::current_zone(), now_sys);

    // %r = %H:%M (locale's 12 hour time), %c = locale's date and time
    std::println("\nother formatting examples using now_sys_zt");
    std::println("now_sys_zt:   {0:%F} {0:%X} {0:%Z}", now_sys_zt);
    std::println("12 hour time: {0:%F} {0:%r}", now_sys_zt);
    std::println("explicit YMD: {0:%Y}-{0:%m}-{0:%d}", now_sys_zt);
    std::println("explicit MDY: {0:%m}/{0:%d}/{0:%y}", now_sys_zt);
    std::println("locale:       {0:%c}", now_sys_zt);

    // using zoned time (explicit zones)
    std::vector<std::string> zones 
        { "America/New_York", "Europe/Berlin", "Asia/Kolkata",
          "Asia/Shanghai","Asia/Tokyo", "America/Vancouver" };

    std::println("\ndate and time using explicit zones");

    for (auto zone : zones)
    {
        chrono::zoned_time now_sys_zt {zone, now_sys};
        std::println("{0:25s} {1:%F} {1:%X} {1:%Z}", zone, now_sys_zt);
    }
}

//#define PRINT_TYPE_INFO     // remove comment to print type info

void Ch16_04_ex2()
{
    // calculate number of leap seconds since 2000-01-01
    auto sys_days1 = chrono::sys_days(2000y/1/1d);
    auto sys_seconds1 = chrono::sys_seconds(sys_days1);
    auto sys_tse1 = sys_seconds1.time_since_epoch();

    auto utc_seconds1 = chrono::clock_cast<chrono::utc_clock>(sys_seconds1);
    auto utc_tse1 = utc_seconds1.time_since_epoch();
    auto num_leap_seconds1 = utc_tse1 - sys_tse1;

    std::println("sys_days1:         {0:%F} {0:%X} {0:%Z}", sys_days1);
    std::println("sys_tse1:          {}", sys_tse1);
    std::println("utc_tse1:          {}", utc_tse1);
    std::println("num_leap_seconds1: {}", num_leap_seconds1);

    // calculate number of leap seconds since now()
    auto tp_now = chrono::system_clock::now();
    auto tp_now_utc = chrono::clock_cast<chrono::utc_clock>(tp_now);
    auto tp_tse_delta = tp_now_utc.time_since_epoch() - tp_now.time_since_epoch();
    auto num_leap_seconds2 = chrono::duration_cast<chrono::seconds>(tp_tse_delta);

    std::println("\ntp_now:            {0:%F} {0:%X} {0:%Z}", tp_now);
    std::println("num_leap_seconds2: {}", num_leap_seconds2);

    // confirm chrono class types
#ifdef PRINT_TYPE_INFO
    std::println("\nsys_day1:     {:s}", typeid(sys_days1).name());
    std::println("sys_seconds1: {:s}", typeid(sys_seconds1).name());
    std::println("sys_tse1:     {:s}", typeid(sys_tse1).name());
    std::println("utc_seconds1: {:s}", typeid(utc_seconds1).name());
#endif

    static_assert(typeid(sys_days1)
        == typeid(chrono::time_point<chrono::system_clock, chrono::days>));
    static_assert(typeid(sys_seconds1)
        == typeid(chrono::time_point<chrono::system_clock, chrono::seconds>));
    static_assert(typeid(sys_tse1) == typeid(chrono::seconds));
    static_assert(typeid(utc_seconds1)
        == typeid(chrono::time_point<chrono::utc_clock, chrono::seconds>));
}

void Ch16_04_ex()
{
    std::println("\n----- Ch16_04_ex1() -----");
    Ch16_04_ex1();

    std::println("\n----- Ch16_04_ex2() -----");
    Ch16_04_ex2();
}
