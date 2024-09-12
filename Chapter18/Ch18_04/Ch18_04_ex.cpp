//-----------------------------------------------------------------------------
// Ch18_04_ex.cpp
//-----------------------------------------------------------------------------

#include "Ch18_04.h"
#include "AminoAcid.h"
#include "DiceSet.h"

void Ch18_04_ex1()
{
    constexpr size_t num_rolls {30};
    constexpr unsigned int num_dice {2};
    constexpr unsigned int num_sides {6};
    constexpr unsigned int seed {0};

    // allocate dice set (uses default values for side names)
    DiceSet dice(num_dice, num_sides, seed);

    // perform simulated rolls
    std::println("\nusing class DiceSet ");
    std::println("(num_dice = {:d}, num_sides = {:d})\n", num_dice, num_sides);

    for (unsigned int i = 0; i < num_rolls; ++i)
    {
        std::print("roll {:2d}: ", i);

        // roll dice
        std::vector<unsigned int> roll_values = dice.roll();

        // sum values of all dice
        unsigned int total {};
        for (unsigned int j = 0; j < num_dice; ++j)
        {
            total += roll_values[j];
            std::print("{:1d} ", roll_values[j]);
        }

        std::print(" ({:2d})", total);

        if ((i + 1) % 2 == 0)
            std::println("");
        else
            std::print("  |  ");
    }
}

void Ch18_04_ex2()
{
    constexpr size_t num_rolls {20};
    constexpr unsigned int num_dice {15};
    constexpr unsigned int num_sides {20};
    constexpr unsigned int seed {0};

    // allocate dice set and initialize side names
    DiceSet dice_aa(num_dice, num_sides, seed);

    std::vector<std::string> aa_code3 = AminoAcid::get_vector_all_code3();
    for (unsigned int i = 0; i < num_dice; ++i)
        dice_aa.set_side_names(i, aa_code3);

    // perform simulated rolls
    std::println("\nusing class DiceSet ");
    std::println("(num_dice = {:d}, num_sides = {:d})\n", num_dice, num_sides);

    for (unsigned int i = 0; i < num_rolls; ++i)
    {
        std::vector<std::string> roll_values = dice_aa.roll_names();

        std::print("roll {:2d}:  ", i);
        for (unsigned int j = 0; j < num_dice; ++j)
            std::print("{:4s} ", roll_values[j]);
        std::println("");
    }
}

void Ch18_04_ex()
{
    std::println("\n----- Ch18_04_ex1() -----");
    Ch18_04_ex1();

    std::println("\n----- Ch18_04_ex2() -----");
    Ch18_04_ex2();
}
