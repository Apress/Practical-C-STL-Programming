//-----------------------------------------------------------------------------
// Ch18_03_misc.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <fstream>
#include <numbers>
#include <random>
#include <vector>
#include "Ch18_03.h"

template <class T> std::vector<T> gen_norm_dist(T mean, T sd, size_t n,
    T x_min, T x_step)
{
    using namespace std::numbers;
    T x = x_min;
    std::vector<T> vec1(n);

    for (size_t i = 0; i < n; ++i, x += x_step)
    {
        T t1 = 1.0 / sd * std::sqrt(2.0 * pi);
        T t2 = ((x - mean) * (x - mean)) / (2.0 * sd * sd);
        vec1[i] = t1 * std::exp(-t2);
    }

    return vec1;
}

void Ch18_03_misc()
{
    constexpr size_t n {1500};
    constexpr double x_min {-7.0};
    constexpr double x_step {1.0 / 32.0};

    //
    std::vector<double> vec1 = gen_norm_dist(0.0, 1.0, n, x_min, x_step);
    std::vector<double> vec2 = gen_norm_dist(0.0, 1.5, n, x_min, x_step);
    std::vector<double> vec3 = gen_norm_dist(0.0, 2.0, n, x_min, x_step);
    std::vector<double> vec4 = gen_norm_dist(0.0, 2.5, n, x_min, x_step);

    //
    std::ofstream ofs("Ch18_03_misc.csv", std::ios::out | std::ios::trunc);

    if (!ofs.good())
        throw std::runtime_error("save_histogram - file open error");

    for (size_t i = 0; i < n; ++i)
    {
        std::print(ofs, "{:d}, ", i);

        auto v1 = (i < vec1.size()) ? vec1[i] : 0.0;
        auto v2 = (i < vec2.size()) ? vec2[i] : 0.0;
        auto v3 = (i < vec3.size()) ? vec3[i] : 0.0;
        auto v4 = (i < vec4.size()) ? vec4[i] : 0.0;

        std::print(ofs, "{:.6f}, ", v1);
        std::print(ofs, "{:.6f}, ", v2);
        std::print(ofs, "{:.6f}, ", v3);
        std::println(ofs, "{:.6f}", v4);
    }

    ofs.close();
}
