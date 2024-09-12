//-----------------------------------------------------------------------------
// Ch05_02_ex.cpp
//-----------------------------------------------------------------------------

#include <numbers>
#include <string>
#include <string_view>
#include <typeinfo>
#include <utility>
#include "Ch05_02.h"
#include "Point2D.h"

void Ch05_02_ex1()
{
    using namespace std::string_view_literals;

    // four-element tuple - explicit types
    std::tuple<int, double, std::string_view, char> tup1
        {10, 20.123456, "Hello, World!", '#'};

    std::println("\nstd::get<0>(tup1): {:d}", std::get<0>(tup1));
    std::println("std::get<1>(tup1): {:f}", std::get<1>(tup1));
    std::println("std::get<2>(tup1): {:s}", std::get<2>(tup1));
    std::println("std::get<3>(tup1): {:c}", std::get<3>(tup1));

    // four-element tuple - std::make_tuple
    auto tup2 {std::make_tuple(100, 200.123456, "Bonjour le Monde!"sv, '&')};
    static_assert(typeid(tup1) == typeid(tup2));

    std::println("\nstd::get<0>(tup2): {:d}", std::get<0>(tup2));
    std::println("std::get<1>(tup2): {:f}", std::get<1>(tup2));
    std::println("std::get<2>(tup2): {:s}", std::get<2>(tup2));
    std::println("std::get<3>(tup2): {:c}", std::get<3>(tup2));

    // four-element tuple - type deduction
    std::tuple tup3 {1000, 2000.123456, "Hallo Welt!"sv, '*'};
    static_assert(typeid(tup1) == typeid(tup3));

    std::println("\nstd::get<0>(tup3): {:d}", std::get<0>(tup3));
    std::println("std::get<1>(tup3): {:f}", std::get<1>(tup3));
    std::println("std::get<2>(tup3): {:s}", std::get<2>(tup3));
    std::println("std::get<3>(tup3): {:c}", std::get<3>(tup3));

    // using std::tuple_size
    std::println("\ntup3_size {:d}", std::tuple_size<decltype(tup3)>::value);

    // using std::tuple_element
    std::println("\ntup3 types:");
    std::println("{:s}", typeid(std::tuple_element<0, decltype(tup3)>::type).name());
    std::println("{:s}", typeid(std::tuple_element<1, decltype(tup3)>::type).name());
    std::println("{:s}", typeid(std::tuple_element<2, decltype(tup3)>::type).name());
    std::println("{:s}", typeid(std::tuple_element<3, decltype(tup3)>::type).name());
}

void Ch05_02_ex2()
{
    using tup_t = std::tuple<std::string, int, double>;

    // create test tuples
    tup_t tup0 {"aaaa", 1, 100.0};
    tup_t tup1 {"bbbb", 2, 200.0};
    tup_t tup2 {"cccc", 3, 300.0};
    tup_t tup3 {"dddd", 4, 400.0};

    // print test tuples
    auto print_tup = [](const char* msg, const tup_t& tup)
    {
        std::println("{:s}: [{:s} | {:d} | {:.2f}]", msg,
            std::get<0>(tup), std::get<1>(tup), std::get<2>(tup));
    };

    print_tup("\ntup0 (initial value)", tup0);
    print_tup("tup1 (initial value)", tup1);
    print_tup("tup2 (initial value)", tup2);
    print_tup("tup3 (initial value)", tup3);

    // modification of elements
    tup_t tup4 {tup0};
    print_tup("\ntup4 (initial value)", tup4);
    std::get<0>(tup4) = "AAAA";
    std::get<1>(tup4) *= -1;
    std::get<2>(tup4) /= std::get<2>(tup3);
    print_tup("tup4 (after modifications)", tup4);

    // relational operators
    auto tup5 {tup0};
    print_tup("\ntup5 (initial value)", tup5);
    std::println("tup0 == tup5: {:s}", tup0 == tup5);

    std::get<2>(tup5) *= 1.5;
    print_tup("\ntup5 (after modification)", tup5);
    std::println("tup0 <  tup5: {:s}", tup0 <  tup5);

    std::get<1>(tup5) -= 7;
    print_tup("\ntup5 (after modification)", tup5);
    std::println("tup0 <  tup5: {:s}", tup0 <  tup5);
}

template <size_t I = 0, typename... TUP_Ts>
constexpr void print_tuple(const char* msg, const std::tuple<TUP_Ts...>& tup)
{
    if constexpr(I == 0)
        std::print("{:s}", msg);

    if constexpr(I < sizeof...(TUP_Ts))
    {
        std::print(" | {}", std::get<I>(tup));
        print_tuple<I + 1>(msg, tup);
    }
    else
        std::println(" |");
}

void Ch05_02_ex3()
{
    using namespace std::numbers;
    using namespace std::string_literals;
    using namespace std::string_view_literals;
    using point2d_t = Point2D<unsigned int>;

    // using print_tuple
    auto tup1 = std::make_tuple("Black"s, 1, pi);
    print_tuple("tup1:", tup1);

    auto tup2 = std::make_tuple(pi * 2, "Blue"s, -1, "NFC North"sv);
    print_tuple("tup2:", tup2);

    auto tup3 = std::make_tuple("Chicago Bears"sv, "Detroit Lions"sv,
        "Green Bay Packers"sv, "Minnesota Vikings"sv);
    print_tuple("tup3:", tup3);

    auto tup4 = std::make_tuple(point2d_t {10, 20}, "upper left"s,
        point2d_t {100, 125}, "lower right"s, ln2_v<float>);
    print_tuple("tup4:", tup4);
}

void Ch05_02_ex4()
{
    using namespace std::string_literals;

    // using std::tie to unpack tuple
    int x1 {};
    std::string s1 {}, s2 {}, s3 {};

    auto tup1 = std::make_tuple(1, "one"s, "eins"s, "uno"s);
    std::tie(x1, s1, s2, s3) = tup1;
    std::println("x1: {:d}  s1: {:s}  s2: {:s}  s3: {:s}", x1, s1, s2, s3);

    // using std::tie and std::ignore to unpack tuple
    s2 = "****";
    std::tie(x1, s1, std::ignore, s3) = tup1;
    std::println("x1: {:d}  s1: {:s}  s2: {:s}  s3: {:s}", x1, s1, s2, s3);

    // using structured binding to unpack tuple
    auto tup2 {std::make_tuple(2, "two"s, "zwei"s, "dos"s)};
    auto [x2, s4, s5, s6] = tup2;
    std::println("x2: {:d}  s4: {:s}  s5: {:s}  s6: {:s}", x2, s4, s5, s6);

    // using std::tuple_cat (example 1)
    auto tup3 {std::make_tuple(3, "three"s, "drei"s, "tres"s)};
    auto tup4 {std::make_tuple(4, "four"s, "veir"s, "cuatro"s)};
    auto tup5 = std::tuple_cat(tup3, tup4);

    print_tuple("\ntup5: ", tup5);
    std::println("tup5 size: {:d}", std::tuple_size<decltype(tup5)>::value);

    // using std::tuple_cat (example 2)
    auto tup6 = std::tuple_cat(tup3, std::make_tuple(10.5, 20.8), tup4);

    print_tuple("\ntup6: ", tup6);
    std::println("tup6 size: {:d}", std::tuple_size<decltype(tup6)>::value);
}

void Ch05_02_ex()
{
    std::println("\n----- Ch05_02_ex1() -----");
    Ch05_02_ex1();

    std::println("\n----- Ch05_02_ex2() -----");
    Ch05_02_ex2();

    std::println("\n----- Ch05_02_ex3() -----");
    Ch05_02_ex3();

    std::println("\n----- Ch05_02_ex4() -----");
    Ch05_02_ex4();
}
