//-----------------------------------------------------------------------------
// Ch01_08_ex.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <iostream>
#include <string>
#include <stdexcept>
#include "Ch01_08.h"

void Ch01_08_ex1()
{
    const char* de_text =
        "std::sqrt() domain error, try again";

    while (true)
    {
        std::print("\nEnter a positive number, ctrl-z to exit: ");

        try
        {
            std::string x_str {};
            std::getline(std::cin, x_str);

            if (!std::cin.good())
            {
                if (!std::cin.eof())
                    std::println("std::cin error");
                return;
            }

            double x = std::stod(x_str);

            if (x < 0.0)
                throw std::domain_error(de_text);

            double x_sqrt = std::sqrt(x);
            std::println("x: {:f} x_sqrt: {:.4f}", x, x_sqrt);
        }

        // catch std::domain_error from above
        catch (const std::domain_error& ex)
        {
            std::println("{}", ex.what());
        }

        // catch std::invalid_argument or std::out_of_range
        // (thrown by std::stod())
        catch (const std::invalid_argument& ex)
        {
            std::println("{}", ex.what());
        }

        catch (const std::out_of_range& ex)
        {
            std::println("{}", ex.what());
        }

        // catch all other exceptions
        catch (...)
        {
            std::println("unknown exception has occurred");
        }
    }
}

void Ch01_08_ex()
{
    std::println("\n----- Ch01_08_ex1() -----");
    Ch01_08_ex1();
}
