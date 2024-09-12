//-----------------------------------------------------------------------------
// Ch01_08.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch01_08.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch01_08 -----");
        Ch01_08_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
