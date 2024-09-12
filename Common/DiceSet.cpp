//-----------------------------------------------------------------------------
// DiceSet.cpp
//-----------------------------------------------------------------------------

#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include "DiceSet.h"

DiceSet::DiceSet(unsigned int num_dice, unsigned int num_sides,
    unsigned int rng_seed)
{
    // save DiceSet parameters
    if (!check_args(num_dice, num_sides))
        throw std::runtime_error("DiceSet ctor - invalid argument value");

    m_NumDice = num_dice;
    m_NumSides = num_sides;
    m_RngSeed = rng_seed;

    // initialize default side names (or face labels)
    m_SideNames.resize(m_NumDice * m_NumSides);
    for (size_t i = 0; i < m_NumDice; ++i)
    {
        for (size_t j = 0; j < m_NumSides; ++j)
            m_SideNames[i * m_NumSides + j] = std::to_string(j + 1);
    }

    // initialize RNG engine
    if (m_RngSeed == 0)
        m_RngEngine.seed(m_RngDevice());
    else
        m_RngEngine.seed(m_RngSeed);

    // initialize distribution
    std::uniform_int_distribution<unsigned int> temp_dist(0, num_sides - 1);
    m_RngDist.param(temp_dist.param());
}

void DiceSet::set_side_names(unsigned int dice_num,
    const std::vector<std::string>& side_names)
{
    if ((dice_num >= m_NumDice || side_names.size() != m_NumSides))
    {
        const char* msg = "DiceSet::set_side_names - invalid argument";
        throw std::runtime_error(msg);
    }

    for (unsigned int j = 0; j < m_NumSides; ++j)
        m_SideNames[dice_num * m_NumSides + j] = side_names[j];
}

std::vector<unsigned int> DiceSet::roll(unsigned int offset)
{
    // perform simulated roll, return integer values
    std::vector<unsigned int> roll_values(m_NumDice);

    for (size_t i = 0; i < roll_values.size(); ++i)
        roll_values[i] = m_RngDist(m_RngEngine) + offset;

    return roll_values;
}

std::vector<std::string> DiceSet::roll_names()
{
    // perform simulated roll, return side names
    std::vector<unsigned int> roll_values {roll(0)};
    std::vector<std::string> roll_names(roll_values.size());

    for (size_t i = 0; i < roll_names.size(); ++i)
        roll_names[i] = m_SideNames[i * m_NumSides + roll_values[i]];

    return roll_names;
}

bool DiceSet::check_args(unsigned int num_dice, unsigned int num_sides)
{
    // validate num_dice (arbitrary value for maximum number of dice)
    if (num_dice > 20)
        return false;

    // validate num_sides (most common die sizes are valid, can change)
    bool rc = (num_sides == 6  || num_sides == 4  || num_sides == 8 ||
               num_sides == 10 || num_sides == 12 || num_sides == 20);
    return rc;
}
