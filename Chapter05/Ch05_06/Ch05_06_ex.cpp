//-----------------------------------------------------------------------------
// Ch05_06_ex.cpp
//-----------------------------------------------------------------------------

#include <cerrno>
#include <cfenv>
#include <cmath>
#include <concepts>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>
#include <vector>
#include <version>
#include "Ch05_06.h"
#include "MF.h"

#if __cpp_lib_expected >= 202211L
#include <expected>

enum class ErrorCode
    {OpenError, WriteError, CloseError, DomainError, RangeError};

std::string to_string(ErrorCode ec)
{
    static std::string ec_strings[]
        {"OpenError", "WriteError", "CloseError", "DomainError", "RangeError"};

    switch (ec)
    {
        case ErrorCode::OpenError:
        case ErrorCode::WriteError:
        case ErrorCode::CloseError:
        case ErrorCode::DomainError:
        case ErrorCode::RangeError:
            return ec_strings[static_cast<int>(ec)];
        default:
            return "unknown error code";
    }
}

std::expected<std::string, ErrorCode> file_op(const std::string& base_fn)
{
    // add name of results dir to base_fn
    std::string fn = MF::mk_test_filename(base_fn);

    // create test file (fails on invalid base_fn)
    std::ofstream ofs {fn, std::ios_base::out | std::ios_base::trunc};

    if (!ofs.good())
        return std::unexpected(ErrorCode::OpenError);

    // test file writes
    for (char c {'A'}; c <= 'Z'; ++c)
    {
        ofs << std::string(72, c) << '\n';

        if (!ofs.good())
            return std::unexpected(ErrorCode::WriteError);
    }

    // explicit close
    ofs.close();
    if (ofs.fail())
        return std::unexpected(ErrorCode::CloseError);

    // return final filename to caller
    return fn;
}

void Ch05_06_ex1()
{
    // test base name strings (good and bad)
    const std::string base_names[] =
        {"test1.txt", "test2\\.txt", "test3.txt", "test4/.txt"};

    // Perform test file operations
    for (const std::string& bn : base_names)
    {
        // build base name string
        std::string bn2 {"Ch05_06_ex1_"};
        bn2 += bn;
        std::println("\nbase name: {:s}", bn2);

        // perform file operation
        std::expected<std::string, ErrorCode> result = file_op(bn2);

        if (result.has_value())
        {
            // successful file operation, delete temp file
            std::println("file_op() successful");
            std::println("removing test file {:s}", result.value());
            std::filesystem::remove(result.value());
        }
        else
        {
            // file operation error
            ErrorCode error_code = result.error();
            std::println("file_op() failed ({:s})", to_string(error_code));
        }
    }
}

template <typename T> requires std::floating_point<T>
std::expected<std::vector<T>, ErrorCode> calc_result(const std::vector<T>& vec)
{
    errno = 0;
    std::vector<T> result(vec.size());

    // perform test calculation (flag domain & range errors)
    for (size_t i = 0; i < result.size(); ++i)
    {
        T temp1 = log10(vec[i]);
        if (errno == EDOM)
            return std::unexpected(ErrorCode::DomainError);
        if (errno == ERANGE)
            return std::unexpected(ErrorCode::RangeError);

        T temp2 = sqrt(temp1);
        if (errno == EDOM)
            return std::unexpected(ErrorCode::DomainError);

        result[i] = temp2;
    }

    return result;
}

void Ch05_06_ex2()
{
    int test_id {};

    // test vectors
    std::vector<std::vector<double>> vecs
    {
        {10.0, 20.0, 30.0, 40.0, 50.0},
        {10.0, 20.0, 0.0, 40.0, 50.0},              // RE - log10(0.0)
        {100.0, 200.0, 300.0, 400.0, 500.0},        
        {100.0, 200.0, -300.0, 400.0, 500.0},       // DE - log10(-300.0)
        {1000.0, 2000.0, 3000.0, 4000.0, 5000.0},
        {10.0, 20.0, 0.5, 40.0, 50.0}               // DE - sqrt(log10(0.5))
    };

    auto print_vec = [](const std::vector<double>& vec)
    {
        for (double x : vec)
            std::print("{:9.4f} ", x);
        std::println("");
    };

    for (const std::vector<double>& vec : vecs)
    {
        std::print("\ntest #{:d} vec:    ", test_id);
        print_vec(vec);

        std::print("test #{:d} result: ", test_id++);

        std::expected<std::vector<double>, ErrorCode> result = calc_result(vec);

        if (result)
        {
            std::vector<double> result_vec = result.value();
            print_vec(result_vec);
        }
        else
        {
            ErrorCode ec = result.error();
            std::print("{:s}\n", to_string(ec));
        }
    }
}

#endif  // __cpp_lib_expected

void Ch05_06_ex()
{
#if __cpp_lib_expected >= 202211L
    std::println("\n----- Ch05_06_ex1() -----");
    Ch05_06_ex1();

    std::println("\n----- Ch05_06_ex2() -----");
    Ch05_06_ex2();
#else
    std::println("Example Ch05_06_ex() requires std::expected (C++23)");
#endif
}
