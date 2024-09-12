//-----------------------------------------------------------------------------
// Ch11_06.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch11_06.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch11_06 -----");
        Ch11_06_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
