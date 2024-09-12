//-----------------------------------------------------------------------------
// Mineral.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <limits>
#include <random>
#include <string>
#include <vector>
#include "Mineral.h"

namespace
{
    const std::vector<Mineral> c_Minerals
    {
        Mineral {"Talc", 1.0},                  Mineral {"Dimorphite", 1.5},
        Mineral {"Todorokite", 1.5},            Mineral {"Gypsum", 2.0},
        Mineral {"Kinoite", 2.5},               Mineral {"Galena", 2.625},
        Mineral {"Chalcocite", 2.75},           Mineral {"Calcite", 3.0},
        Mineral {"Hanksite", 3.25},             Mineral {"Roselite", 3.5},
        Mineral {"Aragonite", 3.75},            Mineral {"Fluorite", 4.0},
        Mineral {"Zincite", 4.25},              Mineral {"Conichalcite", 4.5},
        Mineral {"Lindgrenite", 4.5},           Mineral {"Apatite", 5.0},
        Mineral {"Perovskite", 5.25},           Mineral {"Agrellite", 5.5},
        Mineral {"Anatase", 5.75},              Mineral {"Orthoclase", 6.0},
        Mineral {"Chloritoid", 6.5},            Mineral {"Quartz", 7.0},
        Mineral {"Bowieite", 7.0},              Mineral {"Zircon", 7.5},
        Mineral {"Topaz", 8.0},                 Mineral {"Chrysoberyl", 8.5},
        Mineral {"Tongbaite", 8.5},             Mineral {"Corundum", 9.0},
        Mineral {"Moissanite", 9.25},           Mineral {"Diamond", 10.0},
    };
};

std::vector<Mineral> Mineral::get_vector_all()
{
    return c_Minerals;
}

std::vector<Mineral> Mineral::get_vector_all_shuffle(unsigned int rng_seed,
    unsigned int num_shuffles)
{
    std::mt19937_64 rng {rng_seed};
    std::vector<Mineral> minerals {c_Minerals};

    for (unsigned int i {0}; i < num_shuffles; ++i)
        std::shuffle(minerals.begin(), minerals.end(), rng);
    return minerals;
}

std::vector<Mineral> Mineral::get_vector_random(std::size_t vec_size,
    unsigned int rng_seed)
{
    const int dist_max = static_cast<int>(c_Minerals.size() - 1);
    std::mt19937 rng {rng_seed};
    std::uniform_int_distribution<int> dist {0, dist_max};

    std::vector<Mineral> minerals(vec_size);

    for (size_t i {}; i < minerals.size(); ++i)
        minerals[i] = c_Minerals[dist(rng)];
    return minerals;
}

std::vector<Mineral> Mineral::get_vector_sample(size_t vec_size,
    unsigned int rng_seed)
{
    std::vector<Mineral> minerals {};
    std::mt19937_64 rng {rng_seed};
    size_t n = std::min(c_Minerals.size(), vec_size);

    std::sample(c_Minerals.cbegin(), c_Minerals.cend(),
        std::back_inserter(minerals), n, rng);
    std::shuffle(minerals.begin(), minerals.end(), rng);
    return minerals;
}

std::string Mineral::to_str() const
{
    std::string s{};

    std::format_to(std::back_inserter(s), "[{:<13s} ", m_Name);
    std::format_to(std::back_inserter(s), "{:7.3f}]", m_Hardness);
    return s;
}
