//-----------------------------------------------------------------------------
// Ch04_03.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch04_03.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch04_03 -----");
        Ch04_03_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
