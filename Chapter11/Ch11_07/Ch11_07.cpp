//-----------------------------------------------------------------------------
// Ch11_07.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch11_07.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch11_07 -----");
        Ch11_07_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
