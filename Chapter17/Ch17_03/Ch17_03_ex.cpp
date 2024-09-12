//-----------------------------------------------------------------------------
// Ch17_03_ex.cpp
//-----------------------------------------------------------------------------

#include <filesystem>
#include "Ch17_03.h"
#include "MF.h"

namespace fs = std::filesystem;

void Ch17_03_ex1()
{
    auto print_path_info = []
        (const char* msg, const fs::path& p)
    {
        // print paths
        std::println("\n{:s}", msg);
        std::println("raw string:     {:s}", p.string());
        std::println("generic string: {:s}", p.generic_string());

        // compose path forms
        fs::path absolute = fs::absolute(p);
        fs::path canonical = fs::canonical(p);
        fs::path relative = fs::relative(p);
        std::println("absolute:       {:s}", absolute.string());
        std::println("canonical:      {:s}", canonical.string());
        std::println("relative:       {:s}", relative.string());
    };

    // print_path_info example #1
    fs::path path1 = "../../test1.txt";
    MF::create_test_file(path1);
    print_path_info("path1 information:", path1);
    fs::remove(path1);

    // print_path_info example #2
    fs::path path2_base = fs::current_path() / "D0";
    fs::path path2 = path2_base / "D1/D2";
    fs::create_directories(path2);

    path2 /= "test2.txt";
    MF::create_test_file(path2);
    print_path_info("path2 information:", path2);
    fs::remove_all(path2_base);
}

void create_dir(const char* msg, const fs::path& dir)
{
    std::println("\n{:s} - dir: {:s}", msg, dir.string());

    // using fs::create_directory (noexcept) and std::error_code
    std::error_code ec {};

    if (fs::create_directory(dir, ec))
         std::println("#1 - created directory {:s}", dir.string());
    else
    {
        if (!ec)
            std::println("#1 - directory {:s} already exists", dir.string());
        else
        {
            std::println("ec.value:   {:d}", ec.value());
            std::println("ec.message: {:s}", ec.message());
        }
    }

    // using fs::create_directory and fs::filesystem_error
    try
    {
        if (fs::create_directory(dir))
            std::println("#2 - created directory {:s}", dir.string());
        else
            std::println("#2 - directory {:s} already exists", dir.string());
    }

    catch (const fs::filesystem_error& ex)
    {
        // std::exception information
        std::println("\ncaught fs::filesystem_error exception");
        std::println("what():           {:s}", ex.what());

        // fs::filesystem_error information
        std::println("path1():          {:s}", ex.path1().string());
        std::println("path2():          {:s}", ex.path2().string());
        std::println("code().value():   {:d}", ex.code().value());
        std::println("code().message(): {:s}", ex.code().message());
    }
}

void Ch17_03_ex2()
{
    // using create_dir with valid path
    fs::path dir1 = fs::temp_directory_path() / "good_dir_name";
    create_dir("test case #1", dir1);
    create_dir("test case #2", dir1);
    fs::remove(dir1);

    // using create_dir with invalid path
    fs::path dir2 = fs::temp_directory_path() / "bad//_dir_name";
    create_dir("test case #3", dir2);
}

void Ch17_03_ex3()
{
    auto print_types = [](const fs::path& p)
    {
        std::println("\npath: {:s}", p.string());

        // code below uses fs std::error_code overloads, which are noexcept
        std::string s {"| "};
        std::error_code ec {};

        if (fs::exists(p, ec))
        {
            if (fs::is_block_file(p, ec))
                s += "is_block_file | ";
            if (fs::is_character_file(p, ec))
               s += "is_character_file | ";
            if (fs::is_directory(p, ec))
                s += "is_directory | ";
            if (fs::is_fifo(p, ec))
                s += "is_fifo | ";
            if (fs::is_other(p, ec))
                s += "is_other | ";
            if (fs::is_regular_file(p, ec))
                s += "is_regular_file | ";
            if (fs::is_socket(p, ec))
                s += "is_socket | ";
            if (fs::is_symlink(p, ec))
                s += "is_symlink | ";
            if (fs::is_empty(p, ec))
                s += "is_empty |";
        }
        else
            s += "does not exist |";

        if (s == "")
            s += "unknown or implementation specific |";

        std::println("{:s}", s);
    };

    // using create_directory
    fs::path test_path1 = fs::temp_directory_path() / "Ch17_03_ex2";
    fs::create_directory(test_path1);
    fs::path test_path2 = test_path1 / "EmptyDir";
    fs::create_directory(test_path2);

    // create test files
    fs::path test_file1 = test_path1 / "test1-data-file.txt";
    MF::create_test_file(test_file1);
    fs::path test_file2 = test_path1 / "test2-empty-file.txt";
    MF::create_test_file(test_file2, true);

    // print types
    print_types(test_path1);
    print_types(test_path2);
    print_types(test_file1);
    print_types(test_file2);

    // test paths for Windows
    print_types("C:\\");
    print_types("C:\\Windows\\notepad.exe");
    print_types("\\\\carbon2\\projects");

    // test paths for Linux and similar operating systems
    print_types("/etc");
    print_types("/etc/fstab");
    print_types("/dev/sda");
    print_types("/dev/tty0");

    fs::remove_all(test_path1);
}

void Ch17_03_ex()
{
    try
    {
        std::println("\n----- Ch17_03_ex1() -----");
        Ch17_03_ex1();

        std::println("\n----- Ch17_03_ex2() -----");
        Ch17_03_ex2();

        std::println("\n----- Ch17_03_ex3() -----");
        Ch17_03_ex3();
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
