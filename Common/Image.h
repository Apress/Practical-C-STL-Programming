//-----------------------------------------------------------------------------
// Image.h
//-----------------------------------------------------------------------------

#ifndef IMAGE_H_
#define IMAGE_H_
#include <cstdint>
#include <format>
#include <ostream>
#include <string>
#include <vector>
#include "Common.h"

class Image
{
    using pixel_t = uint8_t;                        // alias for image pixel type
    friend struct std::formatter<Image>;

public:
    Image() = default;                              // default constructor

    Image(std::size_t height, std::size_t width);   // parameterized constructor

    Image(const Image& im);                         // copy constructor
    Image(Image&& im) noexcept;                     // move constructor

    virtual ~Image();                               // destructor

    Image& operator=(const Image& im);              // copy assignment
    Image& operator=(Image&& im) noexcept;          // move assignment

    // accessors
    std::size_t height() const {return m_Height;}
    std::size_t width() const {return m_Width;}
    std::size_t num_pixels() const {return m_Height * m_Width;}

    // relational operators
    friend bool operator==(const Image& im1, const Image& im2);
    friend bool operator!=(const Image& im1, const Image& im2);

    // other operators
    friend std::ostream& operator<<(std::ostream& os, const Image& im);

private:
    // private member functions
    void reset();
    std::string to_str() const;

    // attributes
    std::size_t m_Height {};
    std::size_t m_Width {};
    std::vector<pixel_t> m_PixelBuff {};
};

// class Image formatter
template <> struct std::formatter<Image> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const Image& im, std::format_context& fc) const
        { return std::format_to(fc.out(), "{:s}", im.to_str()); }
};

#endif
