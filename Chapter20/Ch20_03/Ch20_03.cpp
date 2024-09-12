//-----------------------------------------------------------------------------
// Ch20_03.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch20_03.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch20_03 -----");
        Ch20_03_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
