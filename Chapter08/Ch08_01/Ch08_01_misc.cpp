//-----------------------------------------------------------------------------
// Ch08_01_misc.cpp
//-----------------------------------------------------------------------------

#include "Ch08_01.h"
#include "HtmlColor.h"

template <typename T>
void print_stats(const char* msg, const T& uno_set)
{
    // print stats
    std::println("{:s}  ", msg);
    std::print("size: {:d}  ", uno_set.size());
    std::print("bucket_count: {:d}  ", uno_set.bucket_count());
    std::println("load_factor: {:.4f}\n", uno_set.load_factor());
}

void print_buckets(const char* msg, const uno_set_str_t& strings)
{
    print_stats(msg, strings);

    // print buckets of strings
    for (size_t i = 0; i < strings.bucket_count(); ++i)
    {
        if (strings.bucket_size(i) > 0)
        {
            std::print("bucket {:2d}: ", i);

            for (auto iter = strings.begin(i); iter != strings.end(i); ++iter)
                std::print("'{}' ", *iter);
            std::println("");
        }
    }
}

void print_buckets(const char* msg, const uno_set_hc_t& colors)
{
    print_stats(msg, colors);

    // print buckets of colors
    for (size_t i = 0; i < colors.bucket_count(); ++i)
    {
        if (i >= HtmlColor::hash_func_bucket_count)
            break;

        if (colors.bucket_size(i) > 0)
        {
            std::print("bucket {:2d}: ", i);

            for (auto iter = colors.begin(i); iter != colors.end(i); ++iter)
                std::print(" {}", iter->Name());
            std::println("");
        }
    }
}
