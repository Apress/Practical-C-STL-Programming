//-----------------------------------------------------------------------------
// RN.h
//-----------------------------------------------------------------------------

#ifndef RN_H_
#define RN_H_
#include <deque>
#include <limits>
#include <random>
#include <valarray>
#include <vector>

namespace RN
{
    constexpr static int s_RngMinDef {1};
    constexpr static int s_RngMaxDef {1000};
    constexpr static unsigned int s_RngSeedDef {42};

    // fill buffer using random values from interval [rng_min, rng_max]
    template <typename T> void fill_buffer(T* buff, size_t n,
        int rng_min = s_RngMinDef, int rng_max = s_RngMaxDef,
        unsigned int rng_seed = s_RngSeedDef)
    {
        std::mt19937 rng {};
        std::uniform_int_distribution<int> rng_dist(rng_min, rng_max);

        if (rng_seed == 0)
        {
            std::random_device rd {};
            rng.seed(rd());
        }
        else
            rng.seed(rng_seed);

        for (size_t i = 0; i < n; ++i)
            buff[i] = static_cast<T>(rng_dist(rng));
    }

    // fill container using random values from interval [rng_min, rng_max]
    template <typename T> void fill_ctr(T& ctr,
        int rng_min = s_RngMinDef, int rng_max = s_RngMaxDef,
        unsigned int rng_seed = s_RngSeedDef)
    {
        std::mt19937 rng {};
        std::uniform_int_distribution<int> rng_dist(rng_min, rng_max);

        if (rng_seed == 0)
        {
            std::random_device rd {};
            rng.seed(rd());
        }
        else
            rng.seed(rng_seed);

        for (auto& x : ctr)
            x = static_cast<T::value_type>(rng_dist(rng));
    }

    // return a single random value
    template <typename T> T get_value()
    {
        static std::random_device rd {};
        constexpr int dist_max = std::numeric_limits<int>::max();
        static std::uniform_int_distribution<int> dist(1, dist_max);

        return static_cast<T>(dist(rd));
    }

    template <typename T> std::valarray<T> get_valarray(size_t n,
        int rng_min = s_RngMinDef, int rng_max = s_RngMaxDef,
        unsigned int rng_seed = s_RngSeedDef)
    {
        // create random number generator and distribution
        std::mt19937 rng {};
        std::uniform_int_distribution<int> rng_dist(rng_min, rng_max);

        // seed generator
        if (rng_seed == 0)
        {
            std::random_device rd {};
            rng.seed(rd());
        }
        else
            rng.seed(rng_seed);

        // generate valarray with random numbers
        std::valarray<T> va(n);
        for (auto& x : va)
            x = static_cast<T>(rng_dist(rng));
        return va;
    }

    template <typename T> std::vector<T> get_vector(size_t n,
        int rng_min = s_RngMinDef, int rng_max = s_RngMaxDef,
        unsigned int rng_seed = s_RngSeedDef)
    {
        // create random number generator and distribution
        std::mt19937 rng {};
        std::uniform_int_distribution<int> rng_dist(rng_min, rng_max);

        // seed generator
        if (rng_seed == 0)
        {
            std::random_device rd {};
            rng.seed(rd());
        }
        else
            rng.seed(rng_seed);

        // generate vector with random numbers
        std::vector<T> vec(n);
        for (auto& x : vec)
            x = static_cast<T>(rng_dist(rng));
        return vec;
    }
}

#endif
