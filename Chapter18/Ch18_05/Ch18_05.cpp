//-----------------------------------------------------------------------------
// Ch18_05.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch18_05.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch18_05 -----");
        Ch18_05_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
