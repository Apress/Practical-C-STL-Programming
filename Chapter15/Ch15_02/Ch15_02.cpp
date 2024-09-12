//-----------------------------------------------------------------------------
// Ch15_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch15_02.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch15_02 -----");
        Ch15_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
