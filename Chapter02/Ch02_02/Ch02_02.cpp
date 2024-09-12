//-----------------------------------------------------------------------------
// Ch02_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch02_02.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch02_02 -----");
        Ch02_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
