//-----------------------------------------------------------------------------
// Ch09_01.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch09_01.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch09_01 -----");
        Ch09_01_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}

