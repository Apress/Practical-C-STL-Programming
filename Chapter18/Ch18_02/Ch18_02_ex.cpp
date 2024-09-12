//-----------------------------------------------------------------------------
// Ch18_02_ex.cpp
//-----------------------------------------------------------------------------

#include <complex>
#include <concepts>
#include <format>
#include "Ch18_02.h"
#include "MTH.h"

void Ch18_02_ex1()
{
    using namespace std::complex_literals;

    // complex variables
    std::complex<double> z0 {};                 // 0 + 0i
    std::complex<double> z1 {3.0, 4.0};
    std::complex<double> z2 {7.0, -3.0};

    std::println("\nz0: ({:.3f}, {:.3f})", z0.real(), z0.imag());
    std::println("z1: ({:.3f}, {:.3f})", z1.real(), z1.imag());
    std::println("z2: ({:.3f}, {:.3f})", z2.real(), z2.imag());

    // complex arithmetic
    std::complex<double> z3 = z1 + z2;
    std::complex<double> z4 = z1 - z2;
    std::complex<double> z5 = z1 * z2;
    std::complex<double> z6 = z1 / z2;

    std::println("\nz3: ({:.3f}, {:.3f})", z3.real(), z3.imag());
    std::println("z4: ({:.3f}, {:.3f})", z4.real(), z4.imag());
    std::println("z5: ({:.3f}, {:.3f})", z5.real(), z5.imag());
    std::println("z6: ({:.3f}, {:.3f})", z6.real(), z6.imag());

    // more complex arithmetic (using complex literals)
    z1 += 1.0 + 2.0i;
    z2 -= 2.0;
    z3 *= 4.0i;
    std::complex<double> z7 = z1 + 1.5 + 3.0i;

    std::println("\nz1: ({:.3f}, {:.3f})", z1.real(), z1.imag());
    std::println("z2: ({:.3f}, {:.3f})", z2.real(), z2.imag());
    std::println("z3: ({:.3f}, {:.3f})", z3.real(), z3.imag());
    std::println("z7: ({:.3f}, {:.3f})", z7.real(), z7.imag());

    // relational ops
    std::complex<double> z8 {4.0, 6.0};
    std::complex<double> z9 {5.0, 12.0};
    std::println("\nz8: ({:.3f}, {:.3f})", z8.real(), z8.imag());
    std::println("z9: ({:.3f}, {:.3f})", z9.real(), z9.imag());
    std::println("z8 == z9: {:s}", z8 == z9);
    std::println("z8 != z9: {:s}", z8 != z9);
    std::println("z9 == (4.0 + 6.0i): {:s}", z9 == 4.0 + 6.0i);
    std::println("z9 != (4.0 + 6.0i): {:s}", z9 != 4.0 + 6.0i);
}

void Ch18_02_ex2()
{
    // using common complex functions
    std::complex<double> z1 {3.0, 4.0};
    auto z1_abs = std::abs(z1);
    auto z1_arg = std::arg(z1);
    auto z1_conj = std::conj(z1);
    
    std::println("\nz1:      ({:.3f}, {:.3f})", z1.real(), z1.imag());
    std::println("z1_abs:  {:.4f}", z1_abs);
    std::println("z1_arg:  {:.4f} radians", z1_arg);
    std::println("z1_arg:  {:.4f} degrees)", MTH::rad_to_deg(z1_arg));
    std::println("z1_conj: ({:.4f}, {:.4f})", z1_conj.real(), z1_conj.imag());
}

template <typename T> requires std::floating_point<T>
void print_complex_vec(const char* msg, const std::vector<std::complex<T>>& x,
    T eps = 0)
{
    std::print("{:s}", msg);
    for (const std::complex<T>& z : x)
    {
        T re = z.real();
        T im = z.imag();

        // flush to zero (for display purposes only)
        if (eps > 0)
        {
            if (fabs(re) < eps)
                re = 0;
            if (fabs(im) < eps)
                im = 0;
        }
        
        std::println("({:11.6f}, {:11.6f})", re, im);
    }
}

void Ch18_02_ex3()
{
    constexpr double eps = 1.0e-9;
    using namespace std::complex_literals;

    // initialize test input signal
    std::vector<std::complex<double>> x
    {
        {1.0}, {3.0 - 1.0i}, {5.0i}, {-1.0 + 2.0i},
        {-8.0 - 3.0i}, {7.0 - 4.0i}, {5.0 + 11.0i}, {-6.0 - 2.0i}
    };

    print_complex_vec("\noriginal signal x:\n", x);

    // calculate discrete Fourier transform
    std::vector<std::complex<double>> X = MTH::dft(x, false);
    print_complex_vec("\nDFT signal X:\n", X);

    // calculate inverse discrete Fourier transform
    std::vector<std::complex<double>> X_inv = MTH::dft(X, true);
    print_complex_vec("\ninverse DFT signal X_inv:\n", X_inv, eps);
}

void Ch18_02_ex()
{
    std::println("\n----- Ch18_02_ex1() -----");
    Ch18_02_ex1();

    std::println("\n----- Ch18_02_ex2() -----");
    Ch18_02_ex2();

    std::println("\n----- Ch18_02_ex3() -----");
    Ch18_02_ex3();
}
