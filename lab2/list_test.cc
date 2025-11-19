#include <sstream>

#include "catch.hpp"
#include "list.h"
#include "list.h"

// Komplettering: Er kod kompilerar med varningar. 
// Komplettering: Det saknas test för självtilldelning för 
//  tilldelningsoperatorn.

// Kommentar: Använd gärna era sections mer uppdelat för att tydligare kunna 
//    organisera vad ni testar var. Ex. 
//    TEST_CASE("remove")
//        SECTION("remove front ok")
//        SECTION("remove back ok")
//        SECTION("remove middle ok")
//        SECTION("remove bad index")
//    Det blir lättare att få en överblick då. 
//    Och att förstå varför vissa operationer ska lyckas, medan andra ska kasta fel.

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE("Create an empty list")
{
    SECTION("Testing init")
    {
        List l{};

        CHECK(l.is_empty());
        CHECK(l.size() == 0);
    }
}

TEST_CASE("Insert items")
{
    SECTION("Default sorted insert")
    {
        List l{};

        l.insert(1);

        CHECK_FALSE(l.is_empty());
        CHECK_FALSE(l.size() == 0);

        l.insert(2);
        l.insert(3);

        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 2);
        CHECK(l.find_at(2) == 3);
        CHECK(l.size() == 3);
    }

    SECTION("Unsorted insert")
    {
        List l{};

        l.insert(10);
        l.insert(5);
        l.insert(3);
        l.insert(15);
        l.insert(1);
        l.insert(999);

        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 3);
        CHECK(l.find_at(2) == 5);
        CHECK(l.find_at(3) == 10);
        CHECK(l.find_at(4) == 15);
        CHECK(l.find_at(5) == 999);
    }
}

TEST_CASE("Find items")
{
    SECTION("Find items by index")
    {
        List l{};

        l.insert(1);
        l.insert(2);
        l.insert(3);

        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 2);
        CHECK(l.find_at(2) == 3);
        CHECK_THROWS(l.find_at(999));
    }

    SECTION("Find items by value")
    {
        List l{};

        l.insert(1);
        l.insert(2);
        l.insert(3);

        CHECK(l.find(1) == 0);
        CHECK(l.find(2) == 1);
        CHECK(l.find(3) == 2);
        CHECK(l.find(3) == l.size() - 1);
        CHECK_THROWS(l.find(999));
    }
}

TEST_CASE("Remove items")
{
    SECTION("Remove items by value")
    {
        List l{};

        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.insert(4);

        CHECK_THROWS(l.remove(999));

        l.remove(2);
        CHECK(l.size() == 3);
        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 3);
        CHECK(l.find_at(2) == 4);

        l.remove(4);
        CHECK(l.size() == 2);
        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 3);

        l.remove(1);
        CHECK(l.size() == 1);
        CHECK(l.find_at(0) == 3);

        l.remove(3);
        CHECK(l.is_empty());
        CHECK_THROWS(l.remove(0));
    }
}

TEST_CASE("Print out items list")
{
    SECTION("to_string")
    {
        List l {};
        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.insert(4);
        l.insert(5);

        CHECK(l.to_string() == "1 -> 2 -> 3 -> 4 -> 5");
    }

    SECTION("Default print")
    {
        std::ostringstream stream1;
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);
        stream1 << l1;
        CHECK(stream1.str() == "1 -> 2 -> 3");
    }
    SECTION("Empty list print")
    {
        std::ostringstream stream2;
        List l2{};
        stream2 << l2;
        CHECK(stream2.str() == "");
    }
}

TEST_CASE("Constructors and operators")
{
    SECTION("Copy_constructor")
    {
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);

        List l2 {l1};

        l2.remove(1);
        l2.remove(2);

        CHECK_FALSE(l1.size() == l2.size());

        CHECK(l2.find_at(0) == 3);
        CHECK(l2.size() == 1);
    }
    SECTION("Copy_assignment_operator")
    {
        List l1{};

        l1.insert(1);
        l1.insert(2);
        l1.insert(3);

        List l2 {};

        l2.insert(8);
        l2.insert(9);

        l2 = l1;

        CHECK(l1.size() == l2.size());

        CHECK(l2.find_at(0) == 1);
        CHECK(l2.size() == 3);

        CHECK_THROWS(l2.remove(8));

        l2.remove(3);

        CHECK_FALSE(l1.size() == l2.size());
    }

    SECTION("Moving_constructor")
    {
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);

        List l2 = std::move(l1);

        l2.remove(1);
        l2.remove(2);

        CHECK(l2.find_at(0) == 3);
        CHECK(l2.size() == 1);
    }

    SECTION("Moving_assignment_operator")
    {
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);

        List l2 {};

        l2.insert(8);
        l2.insert(9);

        l2 = std::move(l1);

        CHECK(l2.size() == 3);

        l2.remove(1);
        l2.remove(2);

        CHECK(l2.find_at(0) == 3);
        CHECK(l2.size() == 1);
    }

    SECTION("Moving_assignment_operator on the same list")
    {
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);

        l1 = std::move(l1);

        CHECK(l1.size() == 3);
        CHECK(l1.find_at(0) == 1);
    }
}
