//-----------------------------------------------------------------------------
// Ch17_04_ex.cpp
//-----------------------------------------------------------------------------

#include <filesystem>
#include "Ch17_04.h"
#include "MF.h"

namespace fs = std::filesystem;

void Ch17_04_ex1()
{
    // create test directory
    std::error_code ec {};
    fs::path test_path = fs::temp_directory_path() / "Ch17_04_ex1";
    
    if (fs::exists(test_path))
        remove_all(test_path);      // for debug/test

    if (!fs::create_directory(test_path, ec))
    {
        std::println("ec: {:s}", ec.message());
        return;
    }

    // create test files
    fs::path test_file1 = test_path / "TestFile1.txt";  // source file
    MF::create_test_file(test_file1);
    fs::path test_file2 = test_path / "TestFile2.txt";  // destination file

    for (int i = 0; i < 3; ++i)
    {
        // set copy_options (default is fs:copy_options::none)
        fs::copy_options copy_opt {};

        if (i == 2)
            copy_opt = fs::copy_options::overwrite_existing;

        std::println("\nusing fs::copy_file() - test #{:d}", i);
        std::println("source file:      {:s}", test_file1.string());
        std::println("destination file: {:s}", test_file2.string());

        // using copy_file (fails when i == 1 is true)
        bool status = fs::copy_file(test_file1, test_file2, copy_opt, ec);
        std::println("status:           {:s}", status);
        std::println("ec.message():     {:s}", ec.message());
    }

    fs::remove_all(test_path);
}

void Ch17_04_ex2()
{
    std::error_code ec {};

    // create path names
    fs::path source_dir = fs::temp_directory_path() / "Ch17_04_ex2_S";
    fs::path dest_dir = fs::temp_directory_path() / "Ch17_04_ex2_D";

    fs::remove_all(source_dir, ec);     // remove old dirs 
    fs::remove_all(dest_dir, ec);       // (for debug/test)

    // create test files in source_dir (remove_all delete
    if (!fs::create_directory(source_dir))
        throw std::runtime_error("create_directory() failed");

    MF::create_test_files(source_dir, "Ch17_04_ex2", 4, 3);

    // copy source_dir to dest_dir (fs::copy() is void)
    fs::copy_options copy_opt = fs::copy_options::recursive;
    fs::copy(source_dir, dest_dir, copy_opt, ec);

    if (ec)
    {
        std::println("error: {:s}", ec.message());
        return;
    }

    // display files in source_dir and des_dir
    for (int i = 0; i < 2; ++i)
    {
        fs::path display_path = (i == 0) ? source_dir : dest_dir;
        std::println("\ndisplay_path: {:s}", display_path.string());

        for (auto const& de : fs::recursive_directory_iterator(display_path))
        {
            if (fs::is_directory(de) || fs::is_regular_file(de))
                std::println("{:s}", de.path().string());
        }
    }

    fs::remove_all(source_dir);
    fs::remove_all(dest_dir);
}

void Ch17_04_ex()
{
    try
    {
        std::println("\n----- Ch17_04_ex1() -----");
        Ch17_04_ex1();

        std::println("\n----- Ch17_04_ex2() -----");
        Ch17_04_ex2();
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
