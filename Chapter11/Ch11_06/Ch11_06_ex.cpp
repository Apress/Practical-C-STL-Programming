//-----------------------------------------------------------------------------
// Ch11_06_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <vector>
#include "Ch11_06.h"
#include "AminoAcid.h"
#include "MT.h"

void Ch11_06_ex1()
{
#ifdef __cpp_lib_ranges_starts_ends_with
    const char* fmt = "{:3s} ";
    std::size_t epl_max {20};
    constexpr std::size_t num_aa {80};

    // generate vector of random amino acids (code3)
    std::vector<std::string> vec1 {AminoAcid::get_vector_random_code3(num_aa, 100)};
    MT::print_ctr("\nvec1:\n", vec1, fmt, epl_max);

    // create test sequences of amino acids
    std::vector<std::string> seq1(vec1.begin(), vec1.begin() + 4);
    MT::print_ctr("\nseq1: ", seq1, fmt, epl_max);

    std::vector<std::string> seq2(vec1.end() - 4, vec1.end());
    MT::print_ctr("seq2: ", seq2, fmt, epl_max);

    // using std:ranges::starts_with
    bool bsw1 = std::ranges::starts_with(vec1, seq1);
    bool bsw2 = std::ranges::starts_with(vec1, seq2);
    std::println("\nvec1 starts with aminio acid sequence seq1: {:s}", bsw1);
    std::println("vec1 starts with aminio acid sequence seq2: {:s}", bsw2);

    // using std:ranges::ends_with
    bool bew1 = std::ranges::ends_with(vec1, seq1);
    bool bew2 = std::ranges::ends_with(vec1, seq2);
    std::println("\nvec1 ends with aminio acid sequence seq1: {:s}", bew1);
    std::println("vec1 ends with aminio acid sequence seq2: {:s}", bew2);
#else
    std::println("Ch11_06_ex1() requires __cpp_lib_ranges_starts_ends_with (C++23)");
#endif
}

void Ch11_06_ex()
{
    std::println("\n----- Ch11_06_ex1() -----");
    Ch11_06_ex1();
}
