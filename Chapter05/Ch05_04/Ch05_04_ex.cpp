//-----------------------------------------------------------------------------
// Ch05_04_ex.cpp
//-----------------------------------------------------------------------------

#include <array>
#include <cmath>
#include <optional>
#include <string>
#include "Ch05_04.h"
#include "Nut.h"

void Ch05_04_ex1()
{
    // std::optional objects
    std::optional<Nut> nut1 {Nut::get_nut(Nut::Type::Almond)};
    std::optional<Nut> nut2 {Nut::get_nut(Nut::Type::Pecan)};
    std::optional<Nut> nut3 {};

    std::print("{:s}", Nut::title_str());

    // using has_value()
    if (nut1.has_value())
        std::println("{}", nut1.value());
    else
        std::println("no value");

    // using operator bool()
    if (nut2)
        std::println("{}", *nut2);
    else
        std::println("no value");

    if (nut3)
        std::println("{}", *nut3);
    else
        std::println("no value");
}

void Ch05_04_ex2()
{
    // create std::optional<Nut> test objects
    std::optional<Nut> nut1 {Nut::get_nut(Nut::Type::Pecan)};
    std::optional<Nut> nut2 {nut1};
    std::optional<Nut> nut3 {Nut::get_nut(Nut::Type::Walnut)};
    std::optional<Nut> nut4 {};
    Nut nut5 {Nut::get_nut(Nut::Type::Almond)};     // value object

    std::println("nut1 name: {}", nut1.has_value() ? nut1->Name() : "no value");
    std::println("nut2 name: {}", nut2.has_value() ? nut2->Name() : "no value");
    std::println("nut3 name: {}", nut3.has_value() ? nut3->Name() : "no value");
    std::println("nut4 name: {}", nut4.has_value() ? nut4->Name() : "no value");
    std::println("nut5 name: {}", nut5.Name());

    // Relational operators - example 1
    std::println("\ncomparisons using two std::optional<Nut>");
    std::println("nut1 == nut2: {:s}", nut1 == nut2);
    std::println("nut1 <  nut2: {:s}", nut1 <  nut2);
    std::println("nut1 >  nut2: {:s}", nut1 >  nut2);

    std::println("\nnut1 == nut3: {:s}", nut1 == nut3);
    std::println("nut1 <  nut3: {:s}", nut1 <  nut3);
    std::println("nut1 >  nut3: {:s}", nut1 >  nut3);

    // Relational operators - example 2
    std::println("\ncomparisons using std::optional<Nut> and no value");
    std::println("nut1 == nut4: {:s}", nut1 == nut4);
    std::println("nut1 <  nut4: {:s}", nut1 <  nut4);
    std::println("nut1 >  nut4: {:s}", nut1 >  nut4);

    // Relational operators - example 3
    std::println("\ncomparisons using std::optional<Nut> and std::nullopt");
    std::println("nut1 == std::nullopt: {:s}", nut1 == std::nullopt);
    std::println("nut1 <  std::nullopt: {:s}", nut1 <  std::nullopt);
    std::println("nut1 >  std::nullopt: {:s}", nut1 >  std::nullopt);

    std::println("\nnut4 == std::nullopt: {:s}", nut4 == std::nullopt);
    std::println("nut4 <  std::nullopt: {:s}", nut4 >  std::nullopt);
    std::println("nut4 >  std::nullopt: {:s}", nut4 <  std::nullopt);

    // Relational operators - example 4
    std::println("\ncomparisons using using std::optional<Nut> and Nut");
    std::println("nut1 == nut5: {:s}", nut1 == nut5);
    std::println("nut1 <  nut5: {:s}", nut1 <  nut5);
    std::println("nut1 >  nut5: {:s}", nut1 >  nut5);
}

void Ch05_04_ex3()
{
#if __cpp_lib_optional >= 202110L

    std::array<std::optional<double>, 2> arr1
        { std::optional<double> {}, std::optional<double> {2.0} };

    for (const std::optional<double>& opt : arr1)
    {
        // print opt.value()
        std::print("\nopt.value(): ");
        if (opt)
            std::println("{:f}", opt.value());
        else 
            std::println("no value");

        // using std::optional<T>::and_then
        auto func_and_then = [](double x) -> std::optional<double>
            { return std::sqrt(x); };

        std::optional<double> result_and_then = opt.and_then(func_and_then);

        std::print("result_and_then.value(): ");
        if (result_and_then)
            std::println("{:f}", result_and_then.value());
        else 
            std::println("no value");

        // using std::optional<T>::transform
        auto func_transform = [](double x) -> int
            { return static_cast<int>(x * x * x); };

        std::optional<int> result_transform = opt.transform(func_transform);

        std::print("result_transform.value(): ");
        if (result_transform)
            std::println("{:d}", result_transform.value());
        else 
            std::println("no value");

        // using std::optional<T>::or_else
        auto func_or_else = []() -> std::optional<double>
            { return 20.0; };

        std::optional<double> result_or_else = opt.or_else(func_or_else);

        std::print("result_or_else.value(): ");
        if (result_or_else)
            std::println("{:f}", result_or_else.value());
        else 
            std::println("no value");
    }
#else
    std::println("Example Ch05_04_ex3() "
        "requires std::optional monadic operations (C++23)");
#endif
}

// helper functions
std::optional<Nut> get_test_nut(Nut::Type type)
{
    // return nullopt to simulate error
    if (type == Nut::Type::Pecan || type == Nut::Type::Pistachio)
        return std::nullopt;

    // return valid Nut
    return Nut::get_nut(type);
}

std::optional<float> protein_per_gram(const Nut& nut)
{
    // calculate grams of protein in 1 gram serving
    return nut.Protein() / 100.0f;
}

float protein_per_ounce(float ppg)
{
    // calculate grams of protein in 1 ounce serving
    return ppg * 28.3495f;
}

void Ch05_04_ex4()
{
#if __cpp_lib_optional >= 202110L

    Nut::Type nut_types[] { Nut::Type::Almond, Nut::Type::Cashew,
        Nut::Type::Pecan, Nut::Type::Walnut };

    for (Nut::Type nut_type : nut_types)
    {
        std::print("nut type: {:10s}", Nut::get_type_string(nut_type));

        // lambda expression for std::optional::or_else
        auto func_or_else = [nut_type]()
            { return std::optional<Nut> { Nut::get_nut(nut_type) }; };

        std::optional<Nut> nut1 = get_test_nut(nut_type);
        std::optional<Nut> nut2 = nut1.or_else(func_or_else);

        if (nut2)
        {
            // display protein per ounce (ppo)
            std::optional<float> ppg = nut2.and_then(protein_per_gram);
            std::optional<float> ppo = ppg.transform(protein_per_ounce);

            if (ppo)
                std::println("protein: {:.4f} g per ounce", ppo.value());
            else
                std::println("ppo has no value");
        }
        else
            std::println("nut2 has no value");
    }
#else
    std::println("Example Ch05_04_ex4() "
                 "requires std::optional monadic operations (C++23)";
#endif
}

void Ch05_04_ex5()
{
#if __cpp_lib_optional >= 202110L

    Nut::Type nut_types[] { Nut::Type::Almond, Nut::Type::Cashew,
        Nut::Type::Pecan, Nut::Type::Walnut };

    for (Nut::Type nut_type : nut_types)
    {
        std::print("nut type: {:10s}", Nut::get_type_string(nut_type));

        // lambda expression for std::optional::or_else
        auto func_or_else = [nut_type]()
            { return std::optional<Nut> { Nut::get_nut(nut_type) }; };

        // display protein per ounce (ppo)
        auto ppo = get_test_nut(nut_type)
                   .or_else(func_or_else)
                   .and_then(protein_per_gram)
                   .transform(protein_per_ounce);

        if (ppo)
            std::println("protein: {:.4f} g per ounce", ppo.value());
        else
            std::println("ppo has no value");
    }
#else
    std::println("Example Ch05_04_ex5() "
        "requires std::optional monadic operations (C++23)");
#endif
}

void Ch05_04_ex()
{
    std::println("\n----- Ch05_04_ex1() -----");
    Ch05_04_ex1();

    std::println("\n----- Ch05_04_ex2() -----");
    Ch05_04_ex2();

    std::println("\n----- Ch05_04_ex3() -----");
    Ch05_04_ex3();

    std::println("\n----- Ch05_04_ex4() -----");
    Ch05_04_ex4();

    std::println("\n----- Ch05_04_ex4() -----");
    Ch05_04_ex4();
}
