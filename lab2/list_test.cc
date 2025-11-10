#include <iostream>
#include <vector>
#include <sstream>

#include "catch.hpp"
#include "list.h"
#include "list.h"

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
        CHECK(l.find_at(2) == l.get_last());
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
    }

    SECTION("Remove items by index")
    {
        List l{};

        l.insert(1);
        l.insert(2);
        l.insert(3);
        l.insert(4);

        l.remove(1, false);
        CHECK(l.size() == 3);
        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 3);
        CHECK(l.find_at(2) == 4);

        l.remove(2, false);
        CHECK(l.size() == 2);
        CHECK(l.find_at(0) == 1);
        CHECK(l.find_at(1) == 3);

        l.remove(0, false);
        CHECK(l.size() == 1);
        CHECK(l.find_at(0) == 3);

        l.remove(0, false);
        CHECK(l.is_empty());
    }
}

TEST_CASE("Get items list")
{
    SECTION("Default get items list")
    {
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);
        std::vector<int> comp_values1 = {1, 2, 3};

        List l2{};
        std::vector<int> comp_values2 = {};

        CHECK(l1.get_values_vector() == comp_values1);
        CHECK(l2.get_values_vector() == comp_values2);
    }
}

TEST_CASE("Print out items list")
{
    SECTION("Default print")
    {
        std::ostringstream stream1;
        List l1{};
        l1.insert(1);
        l1.insert(2);
        l1.insert(3);
        stream1 << l1;
        CHECK(stream1.str() == "1 -> 2 -> 3");

        std::ostringstream stream2;
        List l2{};
        stream2 << l2;
        CHECK(stream2.str() == "");
    }
}
