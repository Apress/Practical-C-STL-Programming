//-----------------------------------------------------------------------------
// Ch17_01_ex.cpp
//-----------------------------------------------------------------------------

#include <filesystem>
#include <fstream>
#include "Ch17_01.h"
#include "MF.h"

namespace fs = std::filesystem;

void Ch17_01_ex1()
{
    // using fs::current_path
    fs::path path1 = fs::current_path();
    std::println("\npath1: {:s}", path1.string());
    path1.append("test1.txt");
    std::println("path1: {:s}", path1.string());

    // using fs::temp_directory_path
    fs::path path2 = fs::temp_directory_path();
    std::println("\npath2: {:s}", path2.string());
    path2 /= "test2.txt";
    std::println("path2: {:s}", path2.string());

    // using fs::current_path - bad path
    fs::path path3 = fs::current_path();
    std::println("\npath3: {:s}", path3.string());
    path3 /= "Bad//Filename.txt";
    std::println("path3: {:s}", path3.string());

    std::ofstream ofs(path3);
    std::println("\nofs.good(): {:s} (expecting false)", ofs.good());
}

void Ch17_01_ex2()
{
    // create test path
    fs::path path1 = fs::current_path() / "test1.txt";
    std::println("path1:               {:s}", path1.string());

    // using fs::path decomposition functions
    fs::path path1_root_name = path1.root_name();
    fs::path path1_root_dir = path1.root_directory();
    fs::path path1_root_path = path1.root_path();
    fs::path path1_relative_path = path1.relative_path();
    fs::path path1_parent_path = path1.parent_path();
    fs::path path1_filename = path1.filename();
    fs::path path1_stem = path1.stem();
    fs::path path1_extension = path1.extension();

    std::println("path1_root_name:     {:s}", path1_root_name.string());
    std::println("path1_root_dir:      {:s}", path1_root_dir.string());
    std::println("path1_root_path:     {:s}", path1_root_path.string());
    std::println("path1_relative_path: {:s}", path1_relative_path.string());
    std::println("path1_parent_path:   {:s}", path1_parent_path.string());
    std::println("path1_filename:      {:s}", path1_filename.string());
    std::println("path1_stem:          {:s}", path1_stem.string());
    std::println("path1_extension:     {:s}", path1_extension.string());
}

void Ch17_01_ex3()
{
    // initialize test subdirectory path
    fs::path sub_dir1 = fs::current_path() / "sub1";

    // using fs::exists
    bool rc = fs::exists(sub_dir1);
    std::println("\nfs::exists({:s})\nrc = {:s}", sub_dir1.string(), rc);

    if (!rc)
    {
        // using fs::create_directory
        rc = fs::create_directory(sub_dir1);
        std::println("\nfs::create_directory({:s})\nrc = {:s}",
            sub_dir1.string(), rc);

        if (!rc)
            return;
    }

    // write a test file to sub_dir1
    fs::path fn1 = sub_dir1 / "TestA.txt";
    rc = MF::create_test_file(fn1);
    std::println("\nwrite_test_file({:s})\nrc = {:s}", fn1.string(), rc);

    // using fs::exists
    rc = fs::exists(fn1);
    std::println("\nfs::exists({:s})\nrc = {:s}", fn1.string(), rc);

    // using fs::remove to delete test file
    rc = fs::remove(fn1);
    std::println("\nfs::remove({:s})\nrc = {:s}", fn1.string(), rc);

    // using fs::remove to delete test subdirectory (must be empty)
    rc = fs::remove(sub_dir1);
    std::println("\nfs::remove({:s})\nrc = {:s}", sub_dir1.string(), rc);
}

void Ch17_01_ex4()
{
    // create fs::paths
    fs::path base_dir = fs::temp_directory_path();
    fs::path sub_tree_top = base_dir / "d1";
    fs::path sub_tree_bot = sub_tree_top / "d2/d3/d4";

    // path sub_tree_bot exists?
    bool rc = fs::exists(sub_tree_bot);
    std::println("\nfs::exists({:s})\nrc = {:s}", sub_tree_bot.string(), rc);

    if (!rc)
    {
        // using fs::create_directories to create sub_tree_bot
        rc = fs::create_directories(sub_tree_bot);
        std::println("\nfs::create_directories({:s})\nrc = {:s}",
            sub_tree_bot.string(), rc);

        if (!rc)
            return;
    }

    // write test file to sub_tree_top
    fs::path fn1 = sub_tree_top / "TestA.txt";
    rc = MF::create_test_file(fn1);
    std::println("\nfn1.generic_string(): {:s}", fn1.generic_string());
    std::println("fn1.string():         {:s}", fn1.string());
    std::println("rc:                   {:s}", rc);
   
    // write test file to sub_tree_bot
    fs::path fn2 = sub_tree_bot / "TestB.txt";
    rc = MF::create_test_file(fn2);
    std::println("\nfn2.generic_string(): {:s}", fn2.generic_string());
    std::println("fn2.string():         {:s}", fn2.string());
    std::println("rc:                   {:s}", rc);

    // using fs::remove_all to delete sub_tree_top
    auto num_deletes = fs::remove_all(sub_tree_top);
    std::println("\nfs::remove_all({:s})\nnum_deletes = {:d}",
        sub_tree_top.generic_string(), num_deletes);
}

void Ch17_01_ex()
{
    try
    {
        std::println("\n----- Ch17_01_ex1() -----");
        Ch17_01_ex1();

        std::println("\n----- Ch17_01_ex2() -----");
        Ch17_01_ex2();

        std::println("\n----- Ch17_01_ex3() -----");
        Ch17_01_ex3();

        std::println("\n----- Ch17_01_ex4() -----");
        Ch17_01_ex4();
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
