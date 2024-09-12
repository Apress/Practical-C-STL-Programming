//-----------------------------------------------------------------------------
// MTH.h
//-----------------------------------------------------------------------------

#ifndef MTH_H_
#define MTH_H_

#include <algorithm>
#include <complex>
#include <concepts>
#include <cmath>
#include <numbers>
#include <type_traits>
#include <vector>

namespace MTH
{
    // degree/radian conversion templates
    template <typename T> T deg_to_rad(T deg)
        { return deg * std::numbers::pi_v<T> / T(180); }

    template <typename T> T rad_to_deg(T rad)
        { return rad * T(180) / std::numbers::pi_v<T>; }

    // common trig template functions
    template <typename T> T csc(T x)
        { return T(1) / std::sin(x); }

    template <typename T> T sec(T x)
        { return T(1) / std::cos(x); }

    template <typename T> T cot(T x)
        { return T(1) / std::tan(x); }

    // sine wave generation template function
    template <typename T, class C = std::vector<T>> requires std::floating_point<T>
    auto generate_sine_wave(T amplitude, T frequency,T phase_deg,
        T t_start, T t_end, T t_step)
    {
        // create target container
        auto num_points = static_cast<std::size_t>((t_end - t_start) / t_step) + 1;
        C sine_wave(num_points);

        // define lambda expression for std::ranges::generate_n
        T omega = 2 * std::numbers::pi_v<T> * frequency;
        T phase_rad = MTH::deg_to_rad(phase_deg);

        auto sw_op = [t = t_start, t_step, omega, amplitude, phase_rad]() mutable
        {
            auto x = amplitude * std::sin(omega * t + phase_rad);
            t += t_step;
            return x;
        };

        // using std::ranges::generate_n
        std::ranges::generate_n(std::begin(sine_wave), sine_wave.size(), sw_op);
        return sine_wave;
    }

    template <typename T> requires std::integral<T>
    bool is_prime(T x)
    {
        static_assert(std::is_same_v<bool, T> == false,
            "invalid use of type bool");

        if (x == 2 || x == 3)
            return true;

        if ((x % 2 == 0) || (x % 3 == 0) || (x <= 1))
            return false;

        for (T i = 5; i * i <= x; i += 6)
        {
            if ((x % i == 0) || (x % (i + 2) == 0))
                return false;
        }

        return true;
    }

    template <typename T> requires std::floating_point<T>
    std::vector<std::complex<T>> dft(const std::vector<std::complex<T>>& x, bool inv)
    {
        // create result vector
        const size_t N = x.size();
        std::vector<std::complex<T>> result(N);

        // set sign for normal or inverse
        const T sign = (inv) ? 1 : -1;

        for (size_t k = 0; k < N; ++k)
        {
            std::complex<T> sum {};

            for (size_t n = 0; n < N; ++n)
            {
                T t1 = 2 * std::numbers::pi_v<T> * n * static_cast<T>(k) / N;
                std::complex<T> t2(0, sign * t1);

                // using std::exp(std::complex)
                sum += x[n] * std::exp(t2);
            }

            // apply pre-factor
            if (inv)
                sum /= static_cast<T>(N);

            result[k] = sum;
        }

        return result;
    }
}

#endif
