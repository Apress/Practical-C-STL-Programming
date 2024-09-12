//-----------------------------------------------------------------------------
// Ch02_05_ex.cpp
//-----------------------------------------------------------------------------

#include <fstream>
#include <stdexcept>
#include <string>
#include "Ch02_05.h"
#include "MF.h"

namespace
{
    const char* s_Strings[]
    {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
        "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
        "sixteen", "seventeen", "eighteen", "nineteen"
    };
}

void Ch02_05_ex1(const std::string& filename)
{
    std::ofstream ofs {filename};

    if (!ofs.good())
    {
        std::println("file open error: {:s}", filename);
        return;
    }

    std::println("writing data to file: {:s}", filename);

    // using iterators to access elements of C-style array
    for (auto iter = std::begin(s_Strings); iter != std::end(s_Strings); ++iter)
    {
        std::println(ofs, "{:s}", *iter);

        if (!ofs.good())
        {
            std::println("file write error: {:s}\n", filename);
            return;
        }
    }

    ofs.close();
}

void Ch02_05_ex2(const std::string& filename)
{
    std::ifstream ifs {filename};

    if (!ifs.good())
    {
        std::println("file open error: {:s}", filename);
        return;
    }

    std::println("reading data from file: {:s}", filename);

    size_t i {};
    std::string str {};

    while (1)
    {
        // get next string value from ifs
        ifs >> str;

        if (ifs.eof())
            break;

        if (ifs.fail())
        {
            std::println("file read error: {:s}", filename);
            break;
        }

        // verify string value
        std::print("test string: {:15s} | compare: ", str);

        if (str == s_Strings[i++])
            std::println("OK");
        else
        {
            std::println("failed!");
            break;
        }
    }

    ifs.close();
}

void Ch02_05_ex3(const std::string& filename)
{
    std::ifstream ifs {filename};

    if (!ifs.good())
    {
        std::println("file open error: {:s}", filename);
        return;
    }

    std::println("reading data from file: {:s}", filename);

    size_t num_lines {};
    std::string line {};

    while (1)
    {
        // read next line from ifs
        std::getline(ifs, line);

        if (ifs.eof())
            break;

        if (ifs.fail())
        {
            std::println("file read error: {:s}", filename);
            break;
        }

        std::println("line {:4d}: {:s}", ++num_lines, line);
    }

    std::println("\nnum_lines: {:d}\n", num_lines);
    ifs.close();
}

void Ch02_05_ex()
{
    std::string fn1 = MF::mk_test_filename("ch02_05.txt");

    std::println("\n----- Ch02_05_ex1() -----");
    Ch02_05_ex1(fn1);

    std::println("\n----- Ch02_05_ex2() -----");
    Ch02_05_ex2(fn1);

    std::println("\n----- Ch02_05_ex3() -----");
    Ch02_05_ex3(fn1);
}
