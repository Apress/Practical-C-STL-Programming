//-----------------------------------------------------------------------------
// Ch09_05_ex.cpp
//-----------------------------------------------------------------------------

#include <version>
#ifdef __cpp_lib_flat_map
#include <flat_map>
#endif
#include "Ch09_05.h"

#ifdef __cpp_lib_flat_map

void Ch09_05_ex1()
{
//    std::flat_map<int> fmap1 {};
    std::println("Ch09_05_ex1() - std::flat_map now available");
}

void Ch09_05_ex2()
{
//    std::flat_multimap<int> fmmap1 {};
    std::println("Ch09_04_ex2() - std::flat_multimap now available");
}

#endif // __cpp_lib_flat_map

void Ch09_05_ex()
{
#ifdef __cpp_lib_flat_map
    std::println("\n----- Ch09_05_ex1() -----");
    Ch09_05_ex1();

    std::println("\n----- Ch09_05_ex2() -----");
    Ch09_05_ex2();
#else
    std::println("Ch09_05 requires cpp_lib_flat_map (C++23)");
#endif
}
