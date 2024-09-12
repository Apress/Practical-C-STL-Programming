//-----------------------------------------------------------------------------
// THR.h
//-----------------------------------------------------------------------------

#ifndef THR_H_
#define THR_H_
#include <chrono>
#include <format>
#include <random>
#include <sstream>
#include <string>
#include <thread>

namespace THR
{
    std::string get_this_thread_id()
    {
        auto thread_id {std::this_thread::get_id()};

#if __cpp_lib_formatters >= 202302L
        return std::format("{}", thread_id);
#else
        std::ostringstream oss {};
        oss << thread_id;
        return oss.str();
#endif
    }

    void sleep_for_random_ms(unsigned int min, unsigned int max)
    {
        if (max <= min)
            throw std::runtime_error("sleep_for_random() - argument error");

        static std::random_device rd;
        unsigned int delay = min + rd() % (max - min);

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

#endif
