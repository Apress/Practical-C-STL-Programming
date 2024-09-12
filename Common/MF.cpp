//-----------------------------------------------------------------------------
// MF.cpp
//-----------------------------------------------------------------------------

#include <chrono>
#include <format>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include "Common.h"
#include "MF.h"

void MF::mk_test_dir()
{
    fs::path test_dir {c_TestDir};

    if (!fs::exists(test_dir))
    {
        if (!fs::create_directory(test_dir))
          throw std::runtime_error("mk_test_dir() - create_directory() failed");
    }
}

std::string MF::mk_test_filename(const std::string& base_fn)
{
    mk_test_dir();
    std::string test_fn = c_TestDir + c_TestFilenamePrefix + base_fn;
    return test_fn;
}

std::string MF::to_string(const fs::file_time_type& ftime)
{
    auto ft = chrono::clock_cast<chrono::system_clock>(ftime);
    chrono::zoned_time zt(chrono::current_zone(), ft);

    std::string s {};
    std::format_to(std::back_inserter(s), "[{0:%F} {0:%X}]", zt.get_local_time());
    return s;
}

void MF::create_test_files(const fs::path& base_dir, const std::string& base_name,
    size_t num_levels, size_t num_files,
    const chrono::time_point<chrono::file_clock>& tp_base, chrono::days tp_adj_days,
    bool verbose)
{
    // create base_dir
    if (fs::exists(base_dir))
    {
        if (!fs::is_directory(base_dir))
            throw std::runtime_error("fs::is_directory() failed");
    }
    else
    {
        if (!fs::create_directory(base_dir))
            throw std::runtime_error("fs::create_directory() failed");
    }

    fs::path sub_dir = base_dir;

    // create subdirs and files
    for (size_t i = 0; i < num_levels; ++i)
    {
        sub_dir /= std::format("D{:02d}", i);

        if (!fs::exists(sub_dir))
        {
            if (!fs::create_directory(sub_dir))
                throw std::runtime_error("fs::create_directory() failed");
        }

        for (size_t j =  0; j < num_files; ++j)
        {
            fs::path fn = sub_dir / 
                std::format("{:s}-{:02d}-{:02d}.txt", base_name, i, j);

            if (!MF::create_test_file(fn.string()))
                throw std::runtime_error("MF::create_test_file() failed");

            if (verbose)
                std::println("created {:s}", fn.string());

            // set last write_time
            if (tp_adj_days != chrono::days{0})
                fs::last_write_time(fn, tp_base + tp_adj_days);
        }
    }
}

bool MF::create_test_file(const std::string& name, bool empty)
{
    // create test file
    std::ofstream ofs(name, std::ios_base::out | std::ios_base::trunc);

    if (!ofs.good())
        return false;

    if (!empty)
    {
        // write sample data to test file
        auto tp_now = chrono::system_clock::now();
        chrono::zoned_time tp_now_zt {chrono::current_zone(), tp_now};

        std::println(ofs, "test file:  {:s}", name);
        std::println(ofs, "created on: {0:%F} {0:%T} {0:%Z}", tp_now);
        std::println(ofs, "created on: {0:%F} {0:%T} {0:%Z}", tp_now_zt);
    }

    ofs.close();
    return !ofs.fail();
}

bool MF::create_test_file(const fs::path& name, bool empty)
{
    return MF::create_test_file(name.string(), empty);
}
