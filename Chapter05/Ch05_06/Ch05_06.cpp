//-----------------------------------------------------------------------------
// Ch05_06.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch05_06.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch05_06 -----");
        Ch05_06_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
