//-----------------------------------------------------------------------------
// Ch01_04.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch01_04.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch01_04 -----");
        Ch01_04_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
