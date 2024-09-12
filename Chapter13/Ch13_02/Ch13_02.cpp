//-----------------------------------------------------------------------------
// Ch13_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch13_02.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch13_02 -----");
        Ch13_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
