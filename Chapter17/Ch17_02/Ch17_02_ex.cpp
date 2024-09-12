//-----------------------------------------------------------------------------
// Ch17_02_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <sstream>
#include "Ch17_02.h"
#include "MF.h"

namespace chrono = std::chrono;
namespace fs = std::filesystem;

void Ch17_02_ex1()
{
    // NOTE - change code_path to book's source code directory on your system
#if defined(_WIN32) || defined(_WIN64)
    fs::path code_path = "x:\\CppSTL\\SourceCode";
#else
    fs::path code_path = "/home/homer/SambaWin/CppSTL/SourceCode";
#endif
    std::println("code_path: {:s}", code_path.string());

    // using fs::is_directory
    bool is_dir = fs::is_directory(code_path);
    std::println("fs::is_directory({:s}): {:s}", code_path.string(), is_dir);

    if (!is_dir)
        return;

    // initialize recursive_directory_iterator
    fs::directory_options options = fs::directory_options::skip_permission_denied;
    fs::recursive_directory_iterator rdi =
        fs::recursive_directory_iterator(code_path, options);

    // search for .cpp and .h files
    size_t num_files {0};
    size_t num_files_h {0};
    size_t num_files_cpp {0};

    for (const fs::directory_entry& dir_entry : rdi)
    {
        // using is_regular_file
        if (fs::is_regular_file(dir_entry))
        {
            // extract extension
            fs::path file = dir_entry.path();
            const std::string& file_ext = file.extension().string();

            // update file counts
            ++num_files;

            if (file_ext == ".cpp")
                ++num_files_cpp;
            else if (file_ext == ".h")
                ++num_files_h;
        }
    }

    std::println("\nnum_files:     {:d}", num_files);
    std::println("num_files_cpp: {:d}", num_files_cpp);
    std::println("num_files_h:   {:d}", num_files_h);
}

void Ch17_02_ex2()
{
    // set old file threshold in days
    constexpr chrono::days num_days {15};

    // base path for old file search
    fs::path base_path = fs::temp_directory_path();

    // get current time
    auto now = chrono::file_clock::now();

    // create old test files (ensures that some files are found)
    constexpr size_t num_levels {4};
    constexpr size_t num_files {3};
    fs::path test_path = base_path / "Ch17_02_ex3";

    std::println("test_path: {:s}", test_path.string());

    MF::create_test_files(test_path, "Ch17_02_ex3", num_levels, num_files,
        now, -num_days, false);

    // set recursive directory iterator options
    auto options = fs::directory_options::skip_permission_denied;
    auto rdi = fs::recursive_directory_iterator(base_path, options);

    size_t num_directories {};
    size_t num_old_files {};
    constexpr size_t num_old_files_print_max {25};

    // search base_path for old files
    for (auto const& dir_entry : rdi)
    {
        // using is_directory
        if (fs::is_directory(dir_entry))
            ++num_directories;

        // using is_regular_file
        if (fs::is_regular_file(dir_entry))
        {
            auto lwt = dir_entry.last_write_time();

            // found old file?
            if (now - lwt >= num_days)
            {
                if (++num_old_files <= num_old_files_print_max)
                {
                    auto s = MF::to_string(lwt);
                    std::println("old {:2d}: {:s} {:s}", num_old_files, s,
                        dir_entry.path().string());
                }
            }
        }
    }

    // print counts and remove test_path
    std::println("\nnum_directories: {:d}", num_directories);
    std::println("num_old_files:   {:d}", num_old_files);
    fs::remove_all(test_path);
}

void Ch17_02_ex()
{
    try
    {
        std::println("\n----- Ch17_02_ex1() -----");
        Ch17_02_ex1();

        std::println("\n----- Ch17_02_ex2() -----");
        Ch17_02_ex2();
    }

    catch (const fs::filesystem_error& ex)
    {
        // std::exception information
        std::println("\nexception - fs::filesystem_error");
        std::println("what(): {:s}", ex.what());

        // fs::filesystem_error information
        std::println("path1(): {:s}", ex.path1().string());
        std::println("path2(): {:s}", ex.path2().string());
        std::println("code().value(): {:d}", ex.code().value());
        std::println("code().message(): {:s}", ex.code().message());
    }
}
