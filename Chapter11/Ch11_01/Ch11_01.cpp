//-----------------------------------------------------------------------------
// Ch11_01.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch11_01.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch11_01 -----");
        Ch11_01_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
