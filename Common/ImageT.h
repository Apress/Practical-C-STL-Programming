//-----------------------------------------------------------------------------
// ImageT.h
//-----------------------------------------------------------------------------

#ifndef IMAGE_T_H_
#define IMAGE_T_H_
#include <concepts>
#include <cstdint>
#include <format>
#include <ostream>
#include <string>
#include <vector>
#include "Common.h"

#define IMAGE_T_DTOR_PRINTLN     // comment out to disable dtor std::println

template <typename T> requires std::unsigned_integral<T>
class Image
{
    friend struct std::formatter<Image<T>>;

public:
    // default constructor
    Image() = default;

    // parameterized constructor
    Image(std::size_t height, std::size_t width) : m_Height {height},
        m_Width {width}
    {
        m_PixelBuff.resize(m_Height * m_Width);
    }

    // copy constructor
    Image(const Image& im) : m_Height {im.m_Height}, m_Width {im.m_Width},
        m_PixelBuff {im.m_PixelBuff}
    {
    }

    // move constructor
    Image(Image&& im) noexcept : m_Height {im.m_Height}, m_Width {im.m_Width},
        m_PixelBuff {std::move(im.m_PixelBuff)}
    {
        im.reset();
    }

    // destructor
    virtual ~Image()
    {
#ifdef IMAGE_T_DTOR_PRINTLN
        // std::println used for demonstration purposes
        std::println("Image::~Image() {}", *this);
#endif
     }

    // copy assignment
    Image& operator=(const Image& im)
    {
        m_Height = im.m_Height;
        m_Width = im.m_Width;
        m_PixelBuff = im.m_PixelBuff;
        return *this;
    }

    // move assignment
    Image& operator=(Image&& im) noexcept
    {
        m_Height = im.m_Height;
        m_Width = im.m_Width;
        m_PixelBuff = std::move(im.m_PixelBuff);
        im.reset();
        return *this;
    }

    // accessors
    std::size_t height() const {return m_Height;}
    std::size_t width() const {return m_Width;}
    std::size_t num_pixels() const {return m_Height * m_Width;}

    // relational operators
    friend bool operator==(const Image& im1, const Image& im2)
    {
        if (im1.m_Height != im2.m_Height || im1.m_Width != im2.m_Width)
            return false;

        return im1.m_PixelBuff == im2.m_PixelBuff;
    }

    friend bool operator!=(const Image& im1, const Image& im2)
    {
        return !operator==(im1, im2);
    }

    // other operators
    friend std::ostream& operator<<(std::ostream& os, const Image& im)
    {
        os << im.to_str();
        return os;
    }

private:
    void reset()
    {
        m_Height = 0;
        m_Width = 0;
    }

    std::string to_str() const
    {
        std::string s {};
        std::format_to(std::back_inserter(s), "[{:5d} ", m_Height);
        std::format_to(std::back_inserter(s), "{:5d} ", m_Width);
        std::format_to(std::back_inserter(s), "{:8d} ", m_Height * m_Width);

        constexpr int pb_w {(sizeof(void*) <= 4) ? 8 : 16};
        std::uintptr_t pb = reinterpret_cast<std::uintptr_t>(m_PixelBuff.data());
        std::format_to(std::back_inserter(s), "0x{:0>{}X}]", pb, pb_w);
        return s;
    }

    // attributes
    std::size_t m_Height {};
    std::size_t m_Width {};
    std::vector<T> m_PixelBuff {};
};

// class Image<T> formatter
template <typename T> struct std::formatter<Image<T>> : std::formatter<std::string>
{
    constexpr auto parse(std::format_parse_context& fpc)
        { return fpc.begin(); }
    
    auto format(const Image<T>& im, std::format_context& fc) const
        {  return std::format_to(fc.out(), "{}", im.to_str()); }
};

#endif
