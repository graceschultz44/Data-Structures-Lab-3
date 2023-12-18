#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Hash.h"

// Test suite for the 'clear' function of the Hash class
TEST_CASE("clear", "[DSHash]")
{
    // Test with string-to-string hash map
    Hash<std::string, std::string> test1;
    test1.insert("HELLO!", "hi");
    test1.insert("HI", "hi");
    test1.insert("hola", "hi");
    // Testing find function and checking the size of results
    std::map<std::string, int> results = test1.find("hola");
    results = test1.find("HI");
    results = test1.find("HELLO!");
    REQUIRE(results.size() == 1); // Confirming the size of the results
    results.clear();              // Clear the results
    test1.clear();                // Clear the hash map
    REQUIRE(results.size() == 0); // Checking the results are now empty

    // Test with int-to-int hash map
    Hash<int, int> test2;
    test2.insert(4, 200);
    test2.insert(50, 200);
    test2.insert(600, 200);
    // Testing find function and checking the size of results
    std::map<int, int> results2 = test2.find(4);
    results2 = test2.find(50);
    results2 = test2.find(600);
    REQUIRE(results2.size() == 1); // Confirming the size of the results
    results2.clear();              // Clear the results
    test1.clear();                 // Clear the hash map (intended to be test2.clear()?)
    REQUIRE(results.size() == 0);  // Checking the results are now empty
}

// Test suite for the 'clone' function of the Hash class
TEST_CASE("clone", "[DSHash]")
{
    // Testing clone functionality with string-to-int hash map
    Hash<std::string, int> test1;
    test1.insert("HELLOOOOO", 0);
    test1.insert("hii", 1000);
    test1.insert("hola", 1);
    Hash<std::string, int> test2;
    test2.clone(test1);                          // Cloning test1 into test2
    REQUIRE(test1.getSize() == test2.getSize()); // Checking if the size of both hash maps is the same

    // Testing clone functionality with char-to-int hash map
    Hash<char, int> test3;
    test3.insert('!', 1);
    test3.insert('+', 1000000);
    test3.insert('@', 100);
    Hash<char, int> test4;
    test4.clone(test3);                          // Cloning test3 into test4
    REQUIRE(test4.getSize() == test3.getSize()); // Checking if the size of both hash maps is the same
}

// Test suite for the 'insert' function of the Hash class
TEST_CASE("insert", "[DSHash]")
{
    // Testing insert functionality with string-to-int hash map
    Hash<std::string, int> test1;
    // Inserting various key-value pairs
    test1.insert("HELLOOOOO", 0);
    test1.insert("hii", 1000);
    test1.insert("grace", 10);
    test1.insert("hii!!", 1000000);
    test1.insert("HELLO", 5500924);
    test1.insert("haha", 8);
    test1.insert("data", 90024);
    test1.insert("structures", 1);
    test1.insert("class", 789);
    test1.insert("lol", 10000);

    // Checking the size of the hash map after insertions
    REQUIRE(test1.getSize() == 10);

    // Testing insert functionality with char-to-int hash map
    Hash<char, int> test2;
    // Inserting various key-value pairs
    test2.insert('A', 0);
    test2.insert('=', 10);
    test2.insert('#', 9087);
    test2.insert('%', 6793);
    test2.insert('J', 234);
    test2.insert('*', 37840);

    // Checking the size of the hash map after insertions
    REQUIRE(test2.getSize() == 6);
}

// Test suite for the 'get size' function of the Hash class
TEST_CASE("get size", "[DSHash]")
{
    // Testing get size functionality with string-to-int hash map
    Hash<std::string, int> test1;
    // Inserting various key-value pairs
    test1.insert("HELLOOOOO", 0);
    test1.insert("hii", 1000);
    test1.insert("grace", 10);
    test1.insert("hii!!", 1000000);
    test1.insert("HELLO", 5500924);
    test1.insert("haha", 8);
    test1.insert("data", 90024);
    test1.insert("structures", 1);
    test1.insert("class", 789);
    test1.insert("lol", 10000);

    // Checking the size of the hash map after insertions
    REQUIRE(test1.getSize() == 10);
    test1.clear();                 // Clearing the hash map
    REQUIRE(test1.getSize() == 0); // Checking the size is now 0

    // Testing get size functionality with char-to-int hash map
    Hash<char, int> test2;
    // Inserting various key-value pairs

    test2.insert('!', 1);
    test2.insert('+', 1000000);
    test2.insert('@', 100);
    REQUIRE(test2.getSize() == 3);
    test2.insert('A', 0);
    test2.insert('=', 10);
    test2.insert('#', 9087);
    test2.insert('%', 6793);
    test2.insert('J', 234);
    test2.insert('*', 37840);

    // Checking the size of the hash map after insertions and clear operation
    REQUIRE(test2.getSize() == 9);
    test2.clear();                 // Clearing the hash map
    REQUIRE(test2.getSize() == 0); // Checking the size is now 0
}
