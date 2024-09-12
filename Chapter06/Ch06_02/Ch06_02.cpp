//-----------------------------------------------------------------------------
// Ch06_02.cpp
//-----------------------------------------------------------------------------

#include <stdexcept>
#include "Ch06_02.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch06_02 -----");
        Ch06_02_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}
