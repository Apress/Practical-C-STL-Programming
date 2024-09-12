//-----------------------------------------------------------------------------
// Ch09_04_ex.cpp
//-----------------------------------------------------------------------------

#include <version>
#ifdef __cpp_lib_flat_set
#include <flat_set>
#endif
#include "Ch09_04.h"

#ifdef __cpp_lib_flat_set

void Ch09_04_ex1()
{
//    std::flat_set<int> fset1 {};
    std::println("Ch09_04_ex1() - std::flat_set now available");
}

void Ch09_04_ex2()
{
//    std::flat_multiset<int> fmset1 {};
    std::println("Ch09_04_ex2() - std::flat_multiset now available");
}

#endif  // __cpp_lib_flat_set

void Ch09_04_ex()
{
#ifdef __cpp_lib_flat_set
    std::println("\n----- Ch09_04_ex1() -----");
    Ch09_04_ex1();

    std::println("\n----- Ch09_04_ex2() -----");
    Ch09_04_ex2();
#else
    std::println("Ch09_04 requires cpp_lib_flat_set (C++23)");
#endif
}
