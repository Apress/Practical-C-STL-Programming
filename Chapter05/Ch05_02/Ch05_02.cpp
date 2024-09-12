//-----------------------------------------------------------------------------
// Ch05_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch05_02.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch05_02 -----");
        Ch05_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
