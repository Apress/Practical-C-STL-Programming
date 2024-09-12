//-----------------------------------------------------------------------------
// Ch16_01_ex.cpp
//-----------------------------------------------------------------------------

#include <ratio>
#include "Ch16_01.h"

void Ch16_01_ex1()
{
    // using std::ratio
    using ra = std::ratio<12, 20>;      // reduced to 3 / 5
    std::println("ra::num: {:3d} ra::den: {:3d}", ra::num, ra::den);

    using rb = std::ratio<1, 15>;
    std::println("rb::num: {:3d} rb::den: {:3d}", rb::num, rb::den);

    using rc = std::ratio<42>;          // 42 / 1
    std::println("rc::num: {:3d} rc::den: {:3d}", rc::num, rc::den);

    // std::ratio arithmetic
    using rd_add = std::ratio_add<ra, rb>;
    using rd_sub = std::ratio_subtract<ra, rb>;
    using rd_mul = std::ratio_multiply<ra, rb>;
    using rd_div = std::ratio_divide<ra, rb>;

    std::println("");
    std::println("rd_add::num: {:3d} rd_add::den: {:3d}", rd_add::num, rd_add::den);
    std::println("rd_sub::num: {:3d} rd_sub::den: {:3d}", rd_sub::num, rd_sub::den);
    std::println("rd_mul::num: {:3d} rd_mul::den: {:3d}", rd_mul::num, rd_mul::den);
    std::println("rd_div::num: {:3d} rd_div::den: {:3d}", rd_div::num, rd_div::den);

    // std::ratio relational operators
    std::println("\nra == rb: {:s}", std::ratio_equal<ra, rb>::value);
    std::println("ra == rb: {:s}", std::ratio_not_equal<ra, rb>::value);
    std::println("ra <  rb: {:s}", std::ratio_less<ra, rb>::value);
    std::println("ra <= rb: {:s}", std::ratio_less_equal<ra, rb>::value);
    std::println("ra >  rb: {:s}", std::ratio_greater<ra, rb>::value);
    std::println("ra >= rb: {:s}", std::ratio_greater_equal<ra, rb>::value);
}

void Ch16_01_ex2()
{
    // using SI ratios
    using ra = std::milli;
    using rb = std::nano;

    std::ratio_add<ra, rb> rc_add;
    std::ratio_subtract<ra, rb> rc_sub;
    std::ratio_multiply<ra, std::micro> rc_mul;
    std::ratio_divide<ra, rb> rc_div;

    std::println("ra::num:    {:<20d} ra::den:    {:<20d}", ra::num, ra::den);
    std::println("rb::num:    {:<20d} rb::den:    {:<20d}", rb::num, rb::den);
    std::println("");
    std::println("rc_add.num: {:<20d} rc_add.den: {:<20d}", rc_add.num, rc_add.den);
    std::println("rc_sub.num: {:<20d} rc_sub.den: {:<20d}", rc_sub.num, rc_sub.den);
    std::println("rc_mul.num: {:<20d} rc_mul.den: {:<20d}", rc_mul.num, rc_mul.den);
    std::println("rc_div.num: {:<20d} rc_div.den: {:<20d}", rc_div.num, rc_div.den);

    // compile-time arithmetic overflow
//  using bad = std::ratio_multiply<rb, std::atto>;

    // more SI ratios
    using rd = std::giga;
    using re = std::tera;

    std::ratio_add<rd, std::mega> rf_add;
    std::ratio_subtract<std::peta, rd> rf_sub;
    std::ratio_multiply<std::kilo, rd> rf_mul;
    std::ratio_divide<rd, re> rf_div;

    std::println("");
    std::println("rd::num:    {:<20d} rd::den:    {:<20d}", rd::num, rd::den);
    std::println("re::num:    {:<20d} re::den:    {:<20d}", re::num, re::den);
    std::println("");
    std::println("rf_add.num: {:<20d} rf_add.den: {:<20d}", rf_add.num, rf_add.den);
    std::println("rf_sub.num: {:<20d} rf_sub.den: {:<20d}", rf_sub.num, rf_sub.den);
    std::println("rf_mul.num: {:<20d} rf_mul.den: {:<20d}", rf_mul.num, rf_mul.den);
    std::println("rf_div.num: {:<20d} rf_div.den: {:<20d}", rf_div.num, rf_div.den);
}

void Ch16_01_ex()
{
    std::println("\n----- Ch16_01_ex1() -----");
    Ch16_01_ex1();

    std::println("\n----- Ch16_01_ex2() -----");
    Ch16_01_ex2();
}
