//-----------------------------------------------------------------------------
// Ch02_03_misc.cpp
//-----------------------------------------------------------------------------

#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include "Ch02_03.h"

void format_ex1()
{
    int a {100};
    unsigned int b {200};
    unsigned long long c {0x123456789ABC};
    float d = std::sqrt(300.0f);
    double e = std::log(400.0);
    double f = e * -0.5;
    std::string g {"abcdefghij"};
    
    std::string s1 = std::format("a={:d}, b={:6d}, c={:#016X}", a, b ,c);
    std::string s2 = std::format("f={2:.4f}, e={1:<12.8f}, d={0:.2f}", d, e, f);
    std::string s3 = std::format("{0:~<20s}, {0:#^20s}, {0:=>20s}", g);

    std::cout << s1 << '\n';
    std::cout << s2 << '\n';
    std::cout << s3 << '\n';
}
