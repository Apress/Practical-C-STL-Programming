//-----------------------------------------------------------------------------
// Book.cpp
//-----------------------------------------------------------------------------

#include <format>
#include <stdexcept>
#include <string>
#include "Book.h"
#include "Common.h"

// note: std::println() calls in ctors and dtor are for demo purposes only

Book::Book()
{
//  std::println("class Book - default ctor");
}

Book::Book(const char* author, const char* title, int year_pub, int num_copies) :
    m_Author {author}, m_Title {title},
    m_YearPub {year_pub}, m_NumCopies {num_copies}
{
//  std::println("class Book - ctor for '{:s}'", m_Title);
}

Book::~Book()
{
//  std::println("class Book - dtor for '{:s}'", m_Title);
}

int Book::sell(int num_copies)
{
    if (num_copies < 0)
        throw std::runtime_error("Book::sell() - invalid value: 'num_copies'");

    if (m_NumCopies >= num_copies)
    {
        m_NumCopies -= num_copies;
        return num_copies;
    }
    else
    {
        int nc_ret = m_NumCopies;
        m_NumCopies = 0;
        return nc_ret;
    }
}

void Book::buy(int num_copies)
{
    if (num_copies < 0)
        throw std::runtime_error("Book::buy() - invalid value: 'num_copies'");

    m_NumCopies += num_copies;
}

std::string Book::to_str() const
{
    std::string s {};

    std::format_to(std::back_inserter(s), {"[{:s}, '{:s}', {:d}, {:d}]"},
        m_Author, m_Title, m_YearPub, m_NumCopies);

    return s;
}
