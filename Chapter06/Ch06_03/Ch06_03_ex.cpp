//-----------------------------------------------------------------------------
// Ch06_03_ex.cpp
//-----------------------------------------------------------------------------

#include <memory>
#include "Ch06_03.h"
#include "Book.h"

void Ch06_03_ex1()
{
    // create std::shared_ptr
    std::shared_ptr<Book> book1 = std::make_shared<Book>("Albert Einstein",
        "The Meaning of Relativity", 1923, 3);

    std::println("\nInitial values:");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);

    // create std::weak_ptr
    std::weak_ptr book1_wp(book1);

    // using lock() - converts std::weak_ptr to std::shared_ptr
    std::shared_ptr<Book> book1_wp_locked = book1_wp.lock();

    if (!book1_wp_locked)
    {
        // lock() fails if std::weak_ptr object is empty
        std::println("lock failed!");
        return;
    }

    std::println("\nAfter lock()");
    std::println("book1_wp_locked (use_count: {}):\n  {}",
        book1_wp_locked.use_count(), *book1_wp_locked);

    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);

    // using reset()
    book1_wp_locked.reset();
    std::println("\nAfter reset()");
    std::println("book1 (use_count: {}): {}", book1.use_count(), *book1);
}

struct S2;

struct S1
{
    S1()  {std::println("S1 ctor");}
    ~S1() {std::println("S1 dtor");}

    std::shared_ptr<S2> S2_sp {};
};

struct S2
{
    S2()  {std::println("S2 ctor");}
    ~S2() {std::println("S2 dtor");}

    std::shared_ptr<S1> S1_sp {};
    std::weak_ptr<S1> S1_wp {};
};

void Ch06_03_ex2()
{
    // cyclic shared_ptrs - destructors not executed
    std::shared_ptr<S1> s1_sp {std::make_shared<S1>()};
    std::shared_ptr<S2> s2_sp {std::make_shared<S2>()};

    s1_sp->S2_sp = s2_sp;
    s2_sp->S1_sp = s1_sp;
}

void Ch06_03_ex3()
{
    // cyclic shared_ptr/weak_ptr - destructors executed
    std::shared_ptr<S1> s1_sp {std::make_shared<S1>()};
    std::shared_ptr<S2> s2_sp {std::make_shared<S2>()};

    s1_sp->S2_sp = s2_sp;
    s2_sp->S1_wp = s1_sp;
}

void Ch06_03_ex()
{
    std::println("\n----- Ch06_03_ex1() -----");
    Ch06_03_ex1();

    std::println("\n----- Ch06_03_ex2() -----");
    Ch06_03_ex2();

    std::println("\n----- Ch06_03_ex2() -----");
    Ch06_03_ex3();
}
