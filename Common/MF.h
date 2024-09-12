//-----------------------------------------------------------------------------
// MF.h
//-----------------------------------------------------------------------------

#ifndef MF_H_
#define MF_H_
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace MF
{
    namespace chrono = std::chrono;
    namespace fs = std::filesystem;

    // test filename prefix - added to simplify deletion of test files
    static const std::string c_TestFilenamePrefix {"~~"};

    // test directory (requires trailing slash)
    static const std::string c_TestDir {"./"};

    // miscellaneous inline functions
    inline char to_lower(char c)
        { return static_cast<char>(std::tolower(static_cast<unsigned char>(c))); }

    inline std::string& to_lower(std::string& s)
    {
        auto to_lo = [](unsigned char c) { return std::tolower(c); };
        std::ranges::transform(s, s.begin(), to_lo);
        return s;
    }

    inline char to_upper(char c)
        { return static_cast<char>(std::toupper(static_cast<unsigned char>(c))); }

    inline std::string& to_upper(std::string& s)
    {
        auto to_up = [](unsigned char c) { return std::toupper(c); };
        std::ranges::transform(s, s.begin(), to_up);
        return s;
    }

    // helper functions defined in MF.cpp
    void mk_test_dir();
    std::string mk_test_filename(const std::string& base_fn);
    std::string to_string(const fs::file_time_type& ftime);

    void create_test_files(const fs::path& base_dir, const std::string& base_name,
        size_t num_levels, size_t num_files,
        const chrono::time_point<chrono::file_clock>& tp_base = chrono::time_point<chrono::file_clock> {},
        chrono::days tp_adj_days = chrono::days{0},
        bool verbose = false);

    bool create_test_file(const std::string& name, bool empty = false);
    bool create_test_file(const fs::path& name, bool empty = false);
};

#endif
