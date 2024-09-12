//-----------------------------------------------------------------------------
// Ch04_04.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch04_04.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch04_04 -----");
        Ch04_04_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
