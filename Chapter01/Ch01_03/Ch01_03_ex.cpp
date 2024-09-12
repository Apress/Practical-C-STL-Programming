//-----------------------------------------------------------------------------
// Ch01_03_ex.cpp
//-----------------------------------------------------------------------------

#include <string>
#include <string_view>
#include <version>
#include "Ch01_03.h"

void Ch01_03_ex1(const std::string& s1, const std::string& s2,
    char c, const char* s)
{
    std::println("s1: '{}'", s1);
    std::println("s2: '{}'", s2);
    std::println("c:  '{}'", c);
    std::println("s:  '{}'", s);

    // string concatenation
    std::string s3 = s1 + ' ' + s2;
    std::string s4 = s3 + c + s;
    std::println("\ns3: '{}'", s3);
    std::println("s4: '{}'", s4);

    // using std::string relational operators
    std::println("\ns1 <  s2: {}", s1 < s2);
    std::println("s1 <= s2: {}", s1 <= s2);
    std::println("s1 == s2: {}", s1 == s2);
    std::println("s1 != s2: {}", s1 != s2);
    std::println("s1 >  s2: {}", s1 > s2);
    std::println("s1 >= s2: {}", s1 >= s2);
}

void Ch01_03_ex2(const std::string& s1, const std::string s_find)
{
    std::println("s1: '{}", s1);
    std::println("substring: {}", s_find);

    // find substring
    std::size_t pos = s1.find(s_find);

    if (pos == std::string::npos)
        std::println("not found");
    else
        std::println("found at position {}", pos);
}

void Ch01_03_ex3(const std::string& s1, const std::string& s_old,
    const std::string& s_new)
{
    std::println("\ns1: '{}'", s1);
    std::string s2 {s1};

    // using find and replace
    auto n_find = s2.find(s_old);

    if (n_find != std::string::npos)
    {
        std::string s3 {s2};
        s3.replace(n_find, s_old.size(), s_new);
        std::println("s3: '{}", s3);
    }
    else
        std::println("substring '{}' not found", s_old);
}

void Ch01_03_ex4(const std::string& s1, const std::string& s_find,
    const std::string& s_insert)
{
    std::println("\ns1: '{}'", s1);
    std::string s2 {s1};

    // using find, insert
    auto n_find = s2.find(s_find);

    if (n_find != std::string::npos)
    {
        s2.insert(n_find + s_find.size(), s_insert);
        std::println("s2: '{}", s2);
    }
    else
        std::println("substring '{}' not found", s_find);
}

void Ch01_03_ex5(const std::string& s1, const std::string_view& s_test)
{
    // using starts_with, ends_with
    bool b_sw = s1.starts_with(s_test);
    bool b_ew = s1.ends_with(s_test);

    std::println("\n'{}' starts with string '{}' - {}", s1, s_test, b_sw);
    std::println("'{}' ends with string '{}' - {}", s1, s_test, b_ew);

    // using contains
#ifdef __cpp_lib_string_contains
    bool b_c = s1.contains(s_test);
    std::println("'{}' contains string '{}' - {}", s1, s_test, b_c);
#else
    std::println("Ch01_03_ex5() uses string::contains() - requires C++23";
#endif
}

void Ch01_03_ex()
{
    std::println("\n----- Ch01_03_ex1() -----");
    const std::string s1 {"Hello"};
    const std::string s2 {"World"};
    const char c {'='};
    const char* s = "Hallo Welt";
    Ch01_03_ex1(s1, s2, c, s);

    std::println("\n----- Ch01_03_ex2() -----");
    const std::string s3 {"one two three four five "
                          "six seven eight nine ten"};
    Ch01_03_ex2(s3, "eight");
    Ch01_03_ex2(s3, "eleven");

    std::println("\n---- Ch01_03_ex3() -----");
    const std::string s4 {"red green blue cyan magenta "
                          "yellow orange brown purple gray"};
    Ch01_03_ex3(s4, "blue", "BLUE");
    Ch01_03_ex3(s4, "cyan", "TAN");
    Ch01_03_ex3(s4, "magenta", "**MAGENTA**");
    Ch01_03_ex3(s4, "indigo", "INDIGO");

    std::println("\n---- Ch01_03_ex4() -----");
    Ch01_03_ex4(s3, "four", " (4)");
    Ch01_03_ex4(s3, "ten", " (10)");
    Ch01_03_ex4(s3, "eleven", " (11)");

    std::println("\n---- Ch01_03_ex5() -----");
    const std::string s5 {"apple banana orange raspberry pear"};
    const std::string_view sv1 {"apple"};
    const std::string_view sv2 {"pear"};
    const std::string_view sv3 {"raspberry"};
    Ch01_03_ex5(s5, sv1);
    Ch01_03_ex5(s5, sv2);
    Ch01_03_ex5(s5, sv3);
}
