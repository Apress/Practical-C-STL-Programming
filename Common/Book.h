//-----------------------------------------------------------------------------
// Book.h
//-----------------------------------------------------------------------------

#include <format>
#include <ostream>
#include <string>

class Book
{
    friend struct std::formatter<Book>;

public:
    Book();
    Book(const char* author, const char* title, int year_pub, int num_copies);
    ~Book();

    std::string Author() const { return m_Author; };
    std::string Title() const { return m_Title; };
    int YearPub() const { return m_YearPub; };
    int NumCopies() const { return m_NumCopies; };

    void set(const char* author, const char* title, int year_pub, int num_copies)
    {
        m_Author = author;
        m_Title = title;
        m_YearPub = year_pub;
        m_NumCopies = num_copies;
    }

    int sell(int num_copies);
    void buy(int num_copies);

private:
    std::string to_str() const;

    std::string m_Author {};
    std::string m_Title {};
    int m_YearPub {};
    int m_NumCopies {};
};

// class Book formatter
template <> struct std::formatter<Book> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const Book& book, std::format_context& fc) const
        {  return std::format_to(fc.out(), "{}", book.to_str()); }
};
