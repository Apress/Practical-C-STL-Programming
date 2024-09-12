//-----------------------------------------------------------------------------
// Ch11_03.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch11_03.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch11_03 -----");
        Ch11_03_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
