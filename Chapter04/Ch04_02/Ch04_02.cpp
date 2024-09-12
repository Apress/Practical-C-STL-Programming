//-----------------------------------------------------------------------------
// Ch04_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch04_02.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch04_02 -----");
        Ch04_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
