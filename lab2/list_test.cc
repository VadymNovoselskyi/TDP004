#include "list.h"
#include "catch.hpp"

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "Create an empty list" ) 
{
    List l{};

    CHECK( l.is_empty() );
    CHECK( l.size() == 0 );
}

TEST_CASE( "Insert an item in an empty list" ) 
{
    List l{};

    l.insert(5);
  
    CHECK_FALSE( l.is_empty() );
    CHECK_FALSE( l.size() == 0 );
  
}
