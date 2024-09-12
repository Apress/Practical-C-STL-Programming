//-----------------------------------------------------------------------------
// RGB.cpp
//-----------------------------------------------------------------------------

#include <format>
#include <string>
#include "RGB.h"

std::string RGB::to_str(bool use_hex) const
{
    std::string s {};

    if (use_hex)
    {
        uint32_t c = ValUint();
        std::format_to(std::back_inserter(s), "0x{:06X}", c);
    }
    else
    {
        std::format_to(std::back_inserter(s), "({:3d},{:3d},{:3d})",
            m_R, m_G, m_B);
    }

    return s;
}
