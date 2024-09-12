//-----------------------------------------------------------------------------
// Ch05_05.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch05_05.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch05_05 -----");
        Ch05_05_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
