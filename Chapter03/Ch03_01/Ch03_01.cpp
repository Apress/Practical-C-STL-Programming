//-----------------------------------------------------------------------------
// Ch03_01.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch03_01.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch03_01 -----");
        Ch03_01_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
