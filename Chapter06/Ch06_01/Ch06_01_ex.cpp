//-----------------------------------------------------------------------------
// Ch06_01_ex.cpp
//-----------------------------------------------------------------------------

#include <cstdint>
#include <memory>
#include <stdexcept>
#include "Ch06_01.h"
#include "Book.h"
#include "RN.h"

void Ch06_01_ex1()
{
    Book* book1 = new Book("Isaac Newton", "Principia", 1687, 5);
    Book* book2 = new Book("Charles Darwin", "On the Origin of Species", 1859, 4);

    // perform operations - exception unsafe
    std::println("\nInitial values:");
    std::println("book1: {}", *book1);
    std::println("book2: {}", *book2);

    book1->sell(2);
    book2->sell(3);

    std::println("\nAfter sell operations:");
    std::println("book1: {}", *book1);
    std::println("book2: {}", *book2);

    delete book1;
    delete book2;
}

void Ch06_01_ex2()
{
    Book* book1 = new Book("Marie Curie", "The Discovery of Radium", 1921, 2);
    Book* book2 = new Book("Albert Einstein", "The Meaning of Relativity", 1923, 3);

    std::println("\nInitial values:");
    std::println("book1: {}", *book1);
    std::println("book2: {}", *book2);

    try
    {
        book1->sell(1);
        book2->sell(5);

        std::println("\nAfter sell operations:");
        std::println("book1: {}", *book1);
        std::println("book2: {}", *book2);
    }

    catch (const std::exception& ex)
    {
        std::println("caught exception Ch06_01_ex2(): {:s}", ex.what());
    }

    delete book1;
    delete book2;
}

void Ch06_01_ex3()
{
    std::unique_ptr<Book> book1 = std::make_unique<Book>("Richard Feynman",
        "Quantum Electrodynamics", 1962, 12);
    std::unique_ptr<Book> book2 = std::make_unique<Book>("Stephen Hawking",
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

void Ch06_01_ex4()
{
    // std::unique_ptr<Book> passed by reference
    auto buy_copies = [](const std::unique_ptr<Book>& book)
    {
        // RN::get_value<int> returns a random integer value (see RN.h)
        int num_copies = RN::get_value<int>() % 20 + 1;
        book->buy(num_copies);
        return num_copies;
    };

    // pass std::unique_ptr<Book>& to another function
    std::unique_ptr<Book> book = std::make_unique<Book>("Isaac Newton",
        "Principia", 1687, 5);
    std::println("\nbook: {}", *book);
    int num_copies = buy_copies(book);
    std::println("num_copies: {:d}", num_copies);
    std::println("book: {}", *book);
}

void Ch06_01_ex5()
{
    auto buy_copies = [](Book& book)
    {
        int num_copies = RN::get_value<int>() % 20 + 1;
        book.buy(num_copies);
        return num_copies;
    };

    constexpr size_t num_books {2};
    std::unique_ptr<Book[]> books = std::make_unique<Book[]>(num_books);

    // manipulate element book[0]
    books[0].set("Isaac Newton", "Principia", 1687, 5);
    std::println("\nbooks[0]: {}", books[0]);
    int num_copies0 = buy_copies(books[0]);
    std::println("num_copies0: {:d}", num_copies0);
    std::println("books[0]: {}", books[0]);

    // manipulate element book[1]
    books[1].set("Charles Darwin", "On the Origin of Species", 1859, 4);
    std::println("\nbooks[1]: {}", books[1]);
    int num_copies1 = buy_copies(books[1]);
    std::println("num_copies1: {:d}", num_copies1);
    std::println("books[1]: {}", books[1]);
}

void Ch06_01_ex6()
{
    std::unique_ptr<Book> book1 = std::make_unique<Book>("Isaac Newton",
        "Principia", 1687, 5);
    std::println("book1: {}", *book1);

    // using std::move to transfer ownership
    std::unique_ptr<Book> book2 = std::move(book1);
    std::println("book2: {}", *book2);

//  std::unique_ptr<Book> book3 = book2;    // error - use of deleted copy ctor
//  book3 = book2;                          // error - use of deleted operator=
}

void Ch06_01_ex7()
{
    constexpr size_t n {10'000'000};

    // buff1 is value-initialized - all elements set to zero
    auto buff1 = std::make_unique<int[]>(n);

    // buff2 is uninitialized
    auto buff2 = std::make_unique_for_overwrite<int[]>(n);

    // fill buffers with random values
    RN::fill_buffer(buff1.get(), n);
    RN::fill_buffer(buff2.get(), n);

    // perform simulated calculation
    int sum1 {}, sum2 {};

    for (size_t i = 0; i < n; ++i)
    {
        sum1 += buff1[i];
        sum2 += buff2[i];
    }

    std::println("sum1: {:d}  sum2: {:d}", sum1, sum2);
}

void Ch06_01_ex()
{
    std::println("\n----- Ch06_01_ex1() -----");
    Ch06_01_ex1();

    std::println("\n----- Ch06_01_ex2() -----");
    Ch06_01_ex2();

    std::println("\n----- Ch06_01_ex3() -----");
    Ch06_01_ex3();

    std::println("\n----- Ch06_01_ex4() -----");
    Ch06_01_ex4();

    std::println("\n----- Ch06_01_ex5() -----");
    Ch06_01_ex5();

    std::println("\n----- Ch06_01_ex6() -----");
    Ch06_01_ex6();

    std::println("\n----- Ch06_01_ex7() -----");
    Ch06_01_ex7();
}
