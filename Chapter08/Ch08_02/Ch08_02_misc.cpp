//-----------------------------------------------------------------------------
// Ch08_02_misc.cpp
//-----------------------------------------------------------------------------

#include "Ch08_02.h"
#include "HtmlColor.h"

void print_buckets(const char* msg, const uno_mset_t& colors)
{
    // print stats
    std::println("{:s}", msg);
    std::print("size: {}  ", colors.size());
    std::print("bucket_count: {}  ", colors.bucket_count());
    std::println("load_factor:  {}", colors.load_factor());

    // print buckets
    std::string sep = '\n' + std::string(11, ' ');

    for (size_t i = 0; i < colors.bucket_count(); ++i)
    {
        if (i >= HtmlColor::hash_func_bucket_count)
            break;

        if (colors.bucket_size(i) != 0)
        {
            unsigned int add_nl {};
            std::print("\nbucket {:2d}: ", i);

            // print elements in current bucket
            for (auto iter = colors.begin(i); iter != colors.end(i); ++iter)
            {
                std::print("{}  ", *iter);

                if ((++add_nl % 2) == 0 && std::next(iter) != colors.end(i))
                    std::print("{:s}", sep);
            }
        }
    }

    std::println("");
}
