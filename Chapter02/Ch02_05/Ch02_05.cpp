//-----------------------------------------------------------------------------
// Ch02_05.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch02_05.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch02_05 -----");
        Ch02_05_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
