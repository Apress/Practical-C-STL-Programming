//-----------------------------------------------------------------------------
// Ch10_01.cpp
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "Ch10_01.h"

int main(int, char** argv)
{
    int rc {};

    try
    {
        std::println("\n----- Results for example Ch10_01 -----");
        Ch10_01_ex();
    }

    catch (const std::exception& ex)
    {
        rc = 1;
        std::println("Exception occurred in program {:s}", argv[0]);
        std::println("{:s}", ex.what());
    }

    return rc;
}

