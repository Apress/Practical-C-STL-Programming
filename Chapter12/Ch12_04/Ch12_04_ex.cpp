//-----------------------------------------------------------------------------
// Ch12_04_ex.cpp
//-----------------------------------------------------------------------------

#include <algorithm>
#include <format>
#include <string>
#include <vector>
#include "Ch12_04.h"
#include "MT.h"

template <class CMP = std::ranges::less>
void print_heap(const std::string& msg, const std::vector<std::string>& heap,
    CMP cmp = {})
{
    auto heap2 {heap};
    std::print("{:s}", msg);

    while (!heap2.empty())
    {
        std::print("{:3s} ", heap2.front());

        // using std::ranges::pop_heap
        std::ranges::pop_heap(heap2, cmp);
        heap2.pop_back();
    }

    std::println("");
}

void Ch12_04_ex1()
{
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {20};

    // using std::ranges::make_heap with std::less (default)
    // (root = largest element)
    std::vector<std::string> vec1 { "ink", "elf", "leg", "fan", "cat",
        "bag", "key", "dog", "gum", "ant", "net", "jam", "mat", "hat", "owl" };

    std::ranges::make_heap(vec1);
    MT::print_ctr("\nvec1 using MT::print_ctr():\n", vec1, fmt, epl_max);
    print_heap("\nvec1 using print_heap():\n", vec1);

    // usng std::ranges::make_heap with std::greater
    // (root = smallest element)
    std::vector<std::string> vec2 { "bag", "hat", "owl", "fan", "dog",
        "ink", "key", "cat", "gum", "ant", "net", "jam", "mat", "elf", "leg" };

    std::ranges::make_heap(vec2, std::greater {});
    MT::print_ctr("\nvec2 using MT::print_ctr():\n", vec2, fmt, epl_max);
    print_heap("\nvec2 using print_heap():\n", vec2, std::greater {});
}

void Ch12_04_ex2()
{
    const char* fmt = "{:3s} ";
    constexpr size_t epl_max {20};

    // using std::ranges::make_heap
    std::vector<std::string> vec1 { "ink", "elf", "leg", "fan", "cat",
        "bag", "key", "dog", "gum", "ant", "net", "jam", "mat", "hat", "owl" };

    std::ranges::make_heap(vec1);
    print_heap("\nvec1 after make_heap():\n", vec1);

    // insert more elements
    std::vector<std::string> more_vals { "cap", "pot", "bog", "lip" };

    for (const auto& val : more_vals)
    {
        // using std::ranges::push_heap
        vec1.push_back(val);
        std::ranges::push_heap(vec1);

        std::string msg = std::format(
            "\nvec1 after push_back() using '{:3s}':\n", val);
        print_heap(msg, vec1);
    }

    // remove four largest elements
    std::print("\nremoving elements: ");
    for (auto i = 0; i < 5; ++i)
    {
        auto pop_val = vec1.front();

        // using std::ranges::pop_heap
        std::ranges::pop_heap(vec1);
        vec1.pop_back();
        std::print("{:3s} ", pop_val);
    }
    print_heap("\n\nvec1 after pop_heap() operations:\n", vec1);

    // using std::ranges::is_heap
    std::println("is_heap(vec1): {:s}", std::ranges::is_heap(vec1));

    // using std::ranges::sort_heap (vec1 is no longer a heap)
    std::ranges::sort_heap(vec1);
    MT::print_ctr("\nvec1 after std::ranges::sort_heap:\n", vec1, fmt, epl_max);
    std::println("is_heap(vec1): {:s}", std::ranges::is_heap(vec1));
}

void Ch12_04_ex()
{
    std::println("\n----- Ch12_04_ex1() -----");
    Ch12_04_ex1();

    std::println("\n----- Ch12_04_ex2() -----");
    Ch12_04_ex2();
}
