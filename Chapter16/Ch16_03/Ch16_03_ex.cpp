//-----------------------------------------------------------------------------
// Ch16_03_ex.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <thread>
#include <typeinfo>
#include <vector>
#include "Ch16_03.h"

namespace chrono = std::chrono;
using namespace std::chrono_literals;

void Ch16_03_ex1()
{
    // clock information lambda
    auto print_clock_info = []<class CLK>(const char* msg, const CLK& clk)
    {
        std::println("\n{:s} ", msg);
        std::println("type name: {:s}", typeid(clk).name());
        std::println("is_steady: {:s}", clk.is_steady);
        std::println("period:    {:s}", typeid(typename CLK::period).name());
    };

    // print clock information for various clocks
    chrono::system_clock clk1 {};
    print_clock_info("clk1 (chrono::system_clock)", clk1);

    chrono::utc_clock clk2 {};
    print_clock_info("clk2 (chrono::utc_clock)", clk2);

    chrono::steady_clock clk3 {};
    print_clock_info("clk3 (chrono::steady_clock)", clk3);

    chrono::high_resolution_clock clk4 {};
    print_clock_info("clk4 (chrono::high_resolution_clock)", clk4);
}

void Ch16_03_ex2()
{
    // using chrono::time_point
    chrono::time_point<chrono::system_clock> tp1_sys {};
    chrono::time_point<chrono::utc_clock> tp1_utc {};

    // print epochs
    // %F = yyyy-mm-dd, %X = locale's time format, %Z = time zone
    std::println("\ntp1_sys epoch: {0:%F} {0:%X} {0:%Z}", tp1_sys);
    std::println("\ntp1_utc epoch: {0:%F} {0:%X} {0:%Z}", tp1_utc);

    // using chrono::system_clock
    auto tp2_sys = chrono::system_clock::now();
    auto tp2_sys_tse = tp2_sys.time_since_epoch();
    std::println("\ntp2_sys: {0:%F} {0:%X} {0:%Z}", tp2_sys);
    std::println("tp2_sys.time_since_epoch(): {}", tp2_sys_tse);

    // using chrono::utc_clock
    auto tp2_utc = chrono::utc_clock::now();
    auto tp2_utc_tse = tp2_utc.time_since_epoch();
    std::println("\ntp2_utc: {0:%F} {0:%X} {0:%Z}", tp2_utc);
    std::println("tp2_utc.time_since_epoch(): {}", tp2_utc_tse);

    // calculate sys/utc time difference (number of leap seconds since epoch)
    auto tp2_delta = tp2_utc_tse - tp2_sys_tse;
    std::println("\ntp2_delta: {:%S}", tp2_delta);

    // using zoned time (current zone)
    chrono::zoned_time tp2_sys_zt(chrono::current_zone(), tp2_sys);
    std::println("\ntp2_sys: {0:%F} {0:%X} {0:%Z}", tp2_sys_zt);

    // using chrono::steady_clock
    auto tp3_start = chrono::steady_clock::now();
    std::this_thread::sleep_for(500ms);
    auto tp3_stop = chrono::steady_clock::now();
    auto tp3_diff = tp3_stop - tp3_start;
    auto tp3_diff_ms = chrono::duration_cast<chrono::milliseconds>(tp3_diff);

    std::println("\ntp3_diff:    {}", tp3_diff);
    std::println("tp3_diff_ms: {}", tp3_diff_ms);
}

void Ch16_03_ex3()
{
    // %H = hours, %M = minutes, %S = decimal seconds
    auto print_tp = [](const char* msg, const auto& tp)
        { std::println("{0:<30s} {1:%F} {1:%H:%M:%S}", msg, tp); };

    // create time_point using specific date
    chrono::time_point<chrono::system_clock> tp = chrono::sys_days {2026y/7/4d};
    std::println("");
    print_tp("tp (initial value):", tp);

    // chrono::time_point arithmetic (date)
    tp += chrono::years(4) + chrono::months(5) + chrono::days(7);
    print_tp("tp (after date adjustments):", tp);

    // chrono::time_point arithmetic (time)
    tp += 12h + 30min + 45s + 123ms + 456us;
    print_tp("tp (after time adjustments):", tp);
}

void Ch16_03_ex4()
{
    // initialize chrono::time_points (%T = %H:%M:%S)
    auto tp1 = chrono::system_clock::now();
    std::this_thread::sleep_for(300ms);
    auto tp2 = chrono::system_clock::now();
    std::this_thread::sleep_for(200ms);
    auto tp3 = chrono::system_clock::now();

    std::println("tp1: {0:%F} {0:%T}", tp1);
    std::println("tp2: {0:%F} {0:%T}", tp2);
    std::println("tp3: {0:%F} {0:%T}", tp3);

    // perform chrono::time_point compares
    auto cmp_tp = [](const auto& tp1, const auto& tp2)
    {
        std::print("\ntp1 == tp2: {:5s}", tp1 == tp2);
        std::println("  tp1 != tp2: {:5s}", tp1 != tp2);
        std::print("tp1 <  tp2: {:5s}", tp1 <  tp2);
        std::println("  tp1 <= tp2: {:5s}", tp1 <= tp2);
        std::print("tp1 >  tp2: {:5s}", tp1 >  tp2);
        std::println("  tp1 >= tp2: {:5s}", tp1 >= tp2);
    };

    cmp_tp(tp1, tp2);
    cmp_tp(tp3, tp1);
}

void Ch16_03_ex5()
{
    auto tp_now = chrono::system_clock::now();
    std::println("tp_now:   {0:%F} {0:%T}", tp_now);

    // using chrono::time_point_cast
    auto tp_cast = chrono::time_point_cast<chrono::milliseconds>(tp_now);
    std::println("\ntp_cast:  {0:%F} {0:%T}", tp_cast);

    // using chrono::ceil, chrono::floor, chrono::round
    auto tp_ceil = chrono::ceil<chrono::microseconds>(tp_now);
    auto tp_floor = chrono::floor<chrono::microseconds>(tp_now);
    auto tp_round = chrono::round<chrono::microseconds>(tp_now);

    std::println("\ntp_ceil:  {0:%F} {0:%T}", tp_ceil);
    std::println("tp_floor: {0:%F} {0:%T}", tp_floor);
    std::println("tp_round: {0:%F} {0:%T}", tp_round);
}

void Ch16_03_ex()
{
    std::println("\n----- Ch16_03_ex1() -----");
    Ch16_03_ex1();

    std::println("\n----- Ch16_03_ex2() -----");
    Ch16_03_ex2();

    std::println("\n----- Ch16_03_ex3() -----");
    Ch16_03_ex3();

    std::println("\n----- Ch16_03_ex4() -----");
    Ch16_03_ex4();

    std::println("\n----- Ch16_03_ex5() -----");
    Ch16_03_ex5();
}
