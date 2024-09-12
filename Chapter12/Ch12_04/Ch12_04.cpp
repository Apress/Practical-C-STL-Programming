//-----------------------------------------------------------------------------
// Ch12_04.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch12_04.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch12_04 -----");
        Ch12_04_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
