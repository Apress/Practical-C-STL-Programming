//-----------------------------------------------------------------------------
// Ch06_02_ex.cpp
//-----------------------------------------------------------------------------

#include <memory>
#include "Ch06_02.h"
#include "Book.h"
#include "RN.h"

void Ch06_02_ex1()
{
    std::shared_ptr<Book> book1 = std::make_shared<Book>("Richard Feynman",
        "Quantum Electrodynamics", 1962, 12);
    std::shared_ptr<Book> book2 = std::make_shared<Book>("Stephen Hawking",
        "A Brief History of Time", 1988, 19);

    std::println("\nInitial values:");
    std::println("book1: {}", *book1);
    std::println("book2: {}", *book2);

    book1->sell(9);
    book2->sell(4);

    std::println("\nAfter sell operations:");
    std::println("book1: {}", *book1);
    std::println("book2: {}", *book2);
}

void Ch06_02_ex2()
{
    // shared_ptr<Book> passed by value
    auto buy_copies = [](std::shared_ptr<Book> book)
    {
        // RN::get_value<int> returns a random integer value (see RN.h)
        int num_copies = RN::get_value<int>() % 40 + 1;
        book->buy(num_copies);
        return num_copies;
    };

    auto book1 = std::make_shared<Book>("Marie Curie",
        "The Discovery of Radium", 1921, 5);
    std::println("\nInitial value:");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);

    // using copy constructor
    auto book2 = book1;
    std::println("\nAfter book2 asignment:");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
    std::println("book2 (use_count: {}): {}", book2.use_count(), *book2);

    // using buy_copies()
    int num_copies = buy_copies(book1);
    std::println("\nafter buy_copies() (num_copies = {:d})", num_copies);
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
    std::println("book2 (use_count: {}): {}", book2.use_count(), *book2);

    // using assignment operator
    std::shared_ptr<Book> book3 {};
    book3 = book2;
    num_copies = buy_copies(book3);
    std::println("\nafter buy_copies() (num_copies = {:d})", num_copies);
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
    std::println("book2 (use_count: {}): {}", book2.use_count(), *book2);
    std::println("book3 (use_count: {}): {}", book3.use_count(), *book3);
}

void Ch06_02_ex3()
{
    auto book1 = std::make_shared<Book>("Marie Curie",
        "The Discovery of Radium", 1921, 5);

    std::println("\nOuter scope");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);

    if (book1->YearPub() == 1921)
    {
        // make copies in new scope
        auto book2 = book1;
        auto book3 = book1;
        auto book4 = book1;

        std::println("\nInner scope");
        std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
    }

    std::println("\nOuter scope");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
}

void Ch06_02_ex()
{
    std::println("\n---- Ch06_02_ex1() ----");
    Ch06_02_ex1();

    std::println("\n---- Ch06_02_ex2() ----");
    Ch06_02_ex2();

    std::println("\n---- Ch06_02_ex3() ----");
    Ch06_02_ex3();
}
