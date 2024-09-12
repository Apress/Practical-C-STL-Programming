//-----------------------------------------------------------------------------
// Ch09_03.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch09_03.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch09_03 -----");
        Ch09_03_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}

