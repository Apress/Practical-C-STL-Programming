//-----------------------------------------------------------------------------
// TowerOfHanoi.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Common.h"
#include "TowerOfHanoi.h"

TowerOfHanoi::uint_t TowerOfHanoi::top_and_pop(peg_t& peg)
{
#ifdef _DEBUG
    if (peg.empty())
        throw std::runtime_error("peg stack is empty()");
#endif

    // pop disc from peg, return value to caller
    uint_t disc = peg.top();
    peg.pop();
    return disc;
}

void TowerOfHanoi::move_disc(peg_t& peg_from, peg_t& peg_to, const char* msg)
{
    // move disc
    uint_t disc = top_and_pop(peg_from);
    peg_to.push(disc);

    if (m_Verbose)
        std::println("{:s}", msg);
}

void TowerOfHanoi::print_pegs()
{
    print_peg("PegA", m_PegA);
    print_peg("PegB", m_PegB);
    print_peg("PegC", m_PegC);
}

void TowerOfHanoi::print_peg(const char* msg, const peg_t& peg)
{
    peg_t peg_temp {peg};
    std::print("{:s}:", msg);

    while (!peg_temp.empty())
        std::print("{:2d} ", top_and_pop(peg_temp));
    std::println("");
}

void TowerOfHanoi::run(uint_t num_discs, bool verbose)
{
    if (num_discs == 0 || num_discs > s_NumDiscsMax)
        throw std::runtime_error("invalid value - 'num_discs'");

    // num_moves = pow(2, num_discs) - 1
    // target_peg = PegB/PegC for num_discs odd/even
    m_Verbose = verbose;
    uint_t num_moves = (uint_t(1) << num_discs) - 1;
    std::string target_peg = (num_discs & 1) ? "PegB" : "PegC";

    // place discs on source peg (m_PegA)
    for (uint_t i {num_discs}; i >= 1; --i)
        m_PegA.push(i);

    std::println(
        "Start (num_discs: {:d}, num_moves: {:d}, target_peg: {:s})",
        num_discs, num_moves, target_peg);
    print_pegs();

    for (uint_t i {0}; i < num_moves; ++i)
    {
        if (m_Verbose)
            std::print("\nMove {:d} - ", i);

        if (i % 3 == 0)
        {
            if (!m_PegA.empty() && (m_PegB.empty() || m_PegA.top() < m_PegB.top()))
                move_disc(m_PegA, m_PegB, "PegA to PegB");
            else
                move_disc(m_PegB, m_PegA, "PegB to PegA");
        }
        else if (i % 3 == 1)
        {
            if (!m_PegA.empty() && (m_PegC.empty() || m_PegA.top() < m_PegC.top()))
                move_disc(m_PegA, m_PegC, "PegA to PegC");
            else
                move_disc(m_PegC, m_PegA, "PegC to PegA");
        }
        else
        {
            if (!m_PegB.empty() && (m_PegC.empty() || m_PegB.top() < m_PegC.top()))
                move_disc(m_PegB, m_PegC, "PegB to PegC");
            else
                move_disc(m_PegC, m_PegB, "PegC to PegB");
        }

        if (m_Verbose)
            print_pegs();
    }

    std::println(
        "\nStop (num_discs: {:d}, num_moves: {:d}, target_peg: {:s})",
        num_discs, num_moves, target_peg);
    print_pegs();
}
