//-----------------------------------------------------------------------------
// Ch11_08_misc.cpp
//-----------------------------------------------------------------------------

#include <array>
#include "Ch11_08.h"

void Ch11_08_misc()
{
    std::array<double, 5> x {1.0, 2.0, 3.0, 4.0, 5.0};

    auto op = [](double a, double b) { return a + b; };

    double l_init {0.0};
    double l_fold = op(op(op(op(op(l_init, x[0]), x[1]), x[2]), x[3]), x[4]);

    double r_init {1000.0};
    double r_fold = op(x[0], op(x[1], op(x[2], op(x[3], op(x[4], r_init)))));

    std::println("l_fold: {:.1f}  r_fold: {:.1f}", l_fold, r_fold);
}
