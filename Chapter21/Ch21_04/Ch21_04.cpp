//-----------------------------------------------------------------------------
// Ch21_04.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch21_04.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch21_04 -----");
        Ch21_04_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
