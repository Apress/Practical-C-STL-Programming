//-----------------------------------------------------------------------------
// Ch05_04.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch05_04.h"

int main(int argc, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch05_04 -----");
        Ch05_04_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}\n", ex.what());
    }

    return rc;
}
