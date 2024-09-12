//-----------------------------------------------------------------------------
// Image.cpp
//-----------------------------------------------------------------------------

#include <cstdint>
#include <format>
#include <ostream>
#include <string>
#include <vector>
#include "Image.h"

#define IMAGE_DTOR_PRINTLN       // comment out to disable dtor std::println

// parameterized constructor
Image::Image(std::size_t height, std::size_t width) : m_Height {height},
    m_Width {width}
{
    m_PixelBuff.resize(m_Height * m_Width);
}

// copy constructor
Image::Image(const Image& im) : m_Height {im.m_Height}, m_Width {im.m_Width},
    m_PixelBuff {im.m_PixelBuff}
{
}

// move constructor
Image::Image(Image&& im) noexcept : m_Height {im.m_Height}, m_Width {im.m_Width},
    m_PixelBuff {std::move(im.m_PixelBuff)}
{
    im.reset();
}

Image::~Image()
{
#ifdef IMAGE_DTOR_PRINTLN
    // std::println used for demonstration purposes
    std::println("Image::~Image() {}", *this);
#endif
}

// copy assignment
Image& Image::operator=(const Image& im)
{
    m_Height = im.m_Height;
    m_Width = im.m_Width;
    m_PixelBuff = im.m_PixelBuff;
    return *this;
}

// move assignment
Image& Image::operator=(Image&& im) noexcept
{
    m_Height = im.m_Height;
    m_Width = im.m_Width;
    m_PixelBuff = std::move(im.m_PixelBuff);
    im.reset();
    return *this;
}

// relational operators
bool operator==(const Image& im1, const Image& im2)
{
    if (im1.m_Height != im2.m_Height || im1.m_Width != im2.m_Width)
        return false;

    return im1.m_PixelBuff == im2.m_PixelBuff;
}

bool operator!=(const Image& im1, const Image& im2)
{
    return !operator==(im1, im2);
}

// other operators
std::ostream& operator<<(std::ostream& os, const Image& im)
{
    os << im.to_str();
    return os;
}

void Image::reset()
{
    m_Height = 0;
    m_Width = 0;
}

std::string Image::to_str() const
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
