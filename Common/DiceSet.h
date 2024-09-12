//-----------------------------------------------------------------------------
// DiceSet.h
//-----------------------------------------------------------------------------

#ifndef DICE_SET_H_
#define DICE_SET_H_
#include <random>
#include <string>
#include <vector>

class DiceSet
{
public:
    DiceSet() = delete;
    DiceSet(unsigned int num_dice, unsigned int num_sides, unsigned int rng_seed);

    unsigned int NumDice() const { return m_NumDice; }
    unsigned int NumSides() const { return m_NumSides; }

    std::vector<unsigned int> roll(unsigned int offset = 1);
    std::vector<std::string> roll_names();

    void set_side_names(unsigned int die_num,
        const std::vector<std::string>& side_names);

private:
    bool check_args(unsigned int num_dice, unsigned int num_sides);

    // dice attributes
    unsigned int m_NumDice {};
    unsigned int m_NumSides {};
    unsigned int m_RngSeed {};
    std::vector<std::string> m_SideNames {};

    // random number generation attributes
    std::random_device m_RngDevice {};
    std::mt19937 m_RngEngine {};
    std::uniform_int_distribution<unsigned int> m_RngDist {};
};

#endif