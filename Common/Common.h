//-----------------------------------------------------------------------------
// Common.h
//-----------------------------------------------------------------------------

#ifndef COMMON_H_
#define COMMON_H_
#include <cstddef>      // for std::size_t

#include <version>
#ifdef __cpp_lib_print
#include <print>
#else
#include <format>
#include <iostream>

// This file contains template functions that facilitate compilation of
// the example source code using a C++ compiler that doesn't fully support
// the std::print functions (e.g., GCC 13, Clang 17). Adding user code to
// namespace std raises the possibility of undefined behavior. This is a 
// not a concern for code that's intended for instructional purposes but
// potentially dangerous for production code. For more information regarding
// this topic, see https://en.cppreference.com/w/cpp/language/extending_std.

namespace std
{
    // print
    template <typename... Args>
    void print(const std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << std::vformat(fmt.get(), std::make_format_args(args...));
    }

    template <typename... Args>
    void print(const std::wformat_string<Args...> wfmt, Args&&... args)
    {
        std::wcout << std::vformat(wfmt.get(), std::make_wformat_args(args...));
    }

    // print (ostream overloads)
    template <typename... Args>
    void print(std::ostream& os, const std::format_string<Args...> fmt,
        Args&&... args)
    {
        os << std::vformat(fmt.get(), std::make_format_args(args...));
    }

    template <typename... Args>
    void print(std::wostream& wos, const std::format_string<Args...> wfmt,
        Args&&... args)
    {
        wos << std::vformat(wfmt.get(), std::make_wformat_args(args...));
    }

    // println
    template <typename... Args>
    void println(const std::format_string<Args...> fmt, Args&&... args)
    {
        std::cout << std::vformat(fmt.get(), std::make_format_args(args...))
                  << '\n';
    }

    template <typename... Args>
    void println(const std::wformat_string<Args...> wfmt, Args&&... args)
    {
        std::wcout << std::vformat(wfmt.get(), std::make_wformat_args(args...))
                   << L'\n';
    } 

    // println (ostream overloads)
    template <typename... Args>
    void println(std::ostream& os, const std::format_string<Args...> fmt,
        Args&&... args)
    {
        os << std::vformat(fmt.get(), std::make_format_args(args...))
                  << '\n';
    }

    template <typename... Args>
    void println(std::wostream& wos, const std::format_string<Args...> wfmt,
        Args&&... args)
    {
        wos << std::vformat(wfmt.get(), std::make_wformat_args(args...))
            << L'\n';
    }
}

#endif  // __cpp_lib_print
#endif  // COMMON_H_
