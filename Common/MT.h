//-----------------------------------------------------------------------------
// MT.h
//-----------------------------------------------------------------------------

#ifndef MT_H_
#define MT_H_
#include <map>
#include <queue>
#include <typeinfo>
#include <unordered_map>
#include <valarray>
#include <vector>
#include "Common.h"

// namespace MT contains miscellaneous template functions that are
// used in multiple source examples.

namespace MT
{
    // print_ctr - prints elements of the specfied container
    template <typename T> void print_ctr(const char* msg, /*const*/ T& ctr,
        const std::string& fmt, size_t epl_max = 0)
    {
        if (msg != nullptr)
            std::print("{:s}", msg);

        size_t epl {};                 // elements per line counter
        size_t num_elem {};
        bool final_nl = true;

        for (const auto& elem : ctr)
        {
            ++num_elem;
            std::print("{:s}", std::vformat(fmt, std::make_format_args(elem)));

            if (epl_max != 0)
            {
                if ((++epl % epl_max) == 0)
                {
                    std::println("");
                    final_nl = false;
                }
                else
                    final_nl = true;
            }
        }

        if (num_elem == 0)
        {
            std::print("<empty>\n");
            return;
        }

        if (final_nl)
            std::println("");
    }

    // print_multimap - prints elements of specified std::multimap
    template <typename T, typename U>
    void print_multimap(const char* msg, const std::multimap<T, U>& m,
        const char* fmt1, const char* fmt2, size_t epl_max = 0)
    {
        if (msg != nullptr)
            std::print("{:s}", msg);

        if (m.empty())
        {
            std::println("<empty>");
            return;
        }

        size_t epl {0};                 // elements per line counter
        bool final_nl = true;

        for (const auto& [key, val] : m)
        {
            std::print("{:s}", std::vformat(fmt1, std::make_format_args(key)));
            std::print("{:s}", std::vformat(fmt2, std::make_format_args(val)));

            if (epl_max != 0)
            {
                if ((++epl % epl_max) == 0)
                {
                    std::println("");
                    final_nl = false;
                }
                else
                    final_nl = true;
            }
        }

        if (final_nl)
            std::println("");
    }

    // print_map - prints elements of specified std::map
    template <typename T, typename U>
    void print_map(const char* msg, const std::map<T, U>& m,
        const char* fmt1, const char* fmt2, size_t epl_max = 0)
    {
        // code below is tolerable for small maps, inefficient for large maps
        std::multimap<T, U> mm(m.begin(), m.end());
        print_multimap(msg, mm, fmt1, fmt2, epl_max);
    }

    // print_multimap - prints elements of specified std::multimap
    template <typename T, typename U>
    void print_unordered_map(const char* msg, const std::unordered_map<T, U>& m,
        const char* fmt1, const char* fmt2, size_t epl_max = 0)
    {
        // code below is tolerable for small maps, inefficient for large maps
        std::multimap<T, U> mm(m.begin(), m.end());
        print_multimap(msg, mm, fmt1, fmt2, epl_max);
    }

    template <typename T>
    void print_queue(const char* msg, const std::queue<T>& q,
        const char* fmt, size_t epl_max = 0)
    {
        if (msg != nullptr)
            std::print("{:s}", msg);

        if (q.empty())
        {
            std::print("<empty>\n");
            return;
        }

        size_t epl {0};
        bool final_nl = true;

        // code below is tolerable for small queues, inefficient for large queues
        std::queue<T> temp {q};
        size_t n {temp.size()};

        for (size_t i {}; i < n; ++i)
        {
            std::print("{:s}", std::vformat(fmt,
                std::make_format_args(temp.front())));

            temp.pop();

            if ((++epl % epl_max) == 0)
            {
                std::println("");
                final_nl = false;
            }
            else
                final_nl = true;
        }

        if (final_nl)
            std::println("");
    }

    template <typename T, typename U, typename V>
    void print_priority_queue(const char* msg, const std::priority_queue<T, U, V>& pq,
        const char* fmt, size_t epl_max = 0)
    {
        size_t n {pq.size()};
        std::priority_queue pq_temp {pq};
        std::queue<T> q_temp {};

        for (size_t i = 0; i < n; ++i)
        {
            q_temp.push(pq_temp.top());
            pq_temp.pop();
        }

        print_queue(msg, q_temp, fmt, epl_max);
    }

    template <typename T> void pt(T& obj)
        { std::println("typeid: [{:s}]", typeid(obj).name()); }

    template <typename T> void pt(const std::string& msg, T& obj)
        { std::println("{:s} [{:s}]", msg, typeid(obj).name()); }
}

#endif  // MT_H_
