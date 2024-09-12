//-----------------------------------------------------------------------------
// TowerOfHanoi.h
//-----------------------------------------------------------------------------

#ifndef TOWER_OF_HANOI_H_
#define TOWER_OF_HANOI_H_

#include <cstdint>
#include <stack>
#include <vector>

class TowerOfHanoi
{
public:
    using uint_t = uint64_t;
    constexpr static uint_t s_NumDiscsMax {63};

    void run(uint_t num_discs, bool verbose);

private:
    using peg_t = std::stack<uint_t, std::vector<uint_t>>;

    uint_t top_and_pop(peg_t& peg);
    void move_disc(peg_t& peg_from, peg_t& peg_to, const char* msg);

    void print_pegs();
    void print_peg(const char* msg, const peg_t& peg);

    peg_t m_PegA {};            // source peg
    peg_t m_PegB {};            // target peg (num discs is odd)
    peg_t m_PegC {};            // target peg (num discs is even)
    bool m_Verbose {};          // print status messages if true
};

#endif
