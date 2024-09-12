//-----------------------------------------------------------------------------
// Ch16_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch16_02.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch16_02 -----");
        Ch16_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
