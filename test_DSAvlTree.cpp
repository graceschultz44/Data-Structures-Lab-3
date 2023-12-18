#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "DSAvlTree.h"

// Test suite for 'contains' function of the DSAvlTree class
TEST_CASE("contains", "[DSAvlTree]")
{
    // Testing with a string-to-string AVL tree
    DSAvlTree<std::string, std::string> test1;
    test1.insert("HELLO!", "hi");
    test1.insert("HI", "hi");
    test1.insert("hola", "hi");
    // Check if the tree contains specific elements and validate the results
    std::map<std::string, int> results = test1.contains("hola");
    REQUIRE(results.size() == 1); // Ensure the size of results is correct
    std::map<std::string, int>::iterator it = results.find("hola");
    REQUIRE(it == results.end()); // Check if 'hola' is not found in the results
    it = results.find("hi");
    REQUIRE(it != results.end()); // Check if 'hi' is found in the results

    // Testing with an int-to-int AVL tree
    DSAvlTree<int, int> test2;
    test2.insert(4, 200);
    test2.insert(50, 200);
    test2.insert(600, 200);
    // Check if the tree contains specific elements and validate the results
    std::map<int, int> results2 = test2.contains(4);
    REQUIRE(results2.size() == 1); // Ensure the size of results is correct
    std::map<int, int>::iterator it1 = results2.find(4);
    REQUIRE(it1 == results2.end()); // Check if '4' is not found in the results
    REQUIRE(results2[200] == 1);    // Check if '200' is found in the results
}

// Test suite for 'isEmpty' function of the DSAvlTree class
TEST_CASE("isEmpty", "[DSAvlTree]")
{
    // Testing with a string-to-int AVL tree
    DSAvlTree<std::string, int> test1;
    REQUIRE(test1.isEmpty() == true); // Check if the tree is initially empty
    test1.insert("HELLO!", 4);
    test1.insert("HI", 4);
    test1.insert("hola", 4);
    REQUIRE(test1.isEmpty() == false); // Check if the tree is not empty after insertions

    // Testing with a char-to-string AVL tree
    DSAvlTree<char, std::string> test2;
    REQUIRE(test2.isEmpty() == true); // Check if the tree is initially empty
    test2.insert('!', "HI!");
    test2.insert('H', "HI!");
    test2.insert('I', "HI!");
    REQUIRE(test2.isEmpty() == false); // Check if the tree is not empty after insertions
}

// Test suite for 'makeEmpty' function of the DSAvlTree class
TEST_CASE("makeEmpty", "[DSAvlTree]")
{
    // Testing with a string-to-int AVL tree
    DSAvlTree<std::string, int> test1;
    // insertions
    test1.insert("HELLO!", 5);
    test1.insert("HI", 5);
    test1.insert("hola", 5);
    test1.insert("haha", 6);
    test1.insert("lol", 6);
    test1.makeEmpty();
    REQUIRE(test1.isEmpty() == true); // Check if the tree is empty after calling makeEmpty

    // Testing with a char-to-int AVL tree
    DSAvlTree<char, int> test2;
    // insertions
    test2.insert('c', 0);
    test2.insert('=', 100000000);
    test2.insert('!', 1000000);
    test2.insert('-', 8402489);
    test2.insert('@', 1);
    test2.makeEmpty();
    REQUIRE(test2.isEmpty() == true); // Check if the tree is empty after calling makeEmpty
}

// Test suite for 'insert' function of the DSAvlTree class
TEST_CASE("insert", "[DSAvlTree]")
{
    DSAvlTree<std::string, std::string> test1;
    // insertions
    test1.insert("HELLO!", "hi");
    test1.insert("HI", "hi");
    test1.insert("hola", "hi");
    // make sure it contains the things that were inserted
    std::map<std::string, int> results = test1.contains("hola");
    REQUIRE(results.size() == 1);
    std::map<std::string, int>::iterator it = results.find("hola");
    REQUIRE(it == results.end());
    it = results.find("hi");
    REQUIRE(it != results.end());

    DSAvlTree<int, int> test2;
    // insertions
    test2.insert(4, 200);
    test2.insert(50, 200);
    test2.insert(600, 200);
    // make sure it contains the things that were inserted
    std::map<int, int> results2 = test2.contains(4);
    REQUIRE(results2.size() == 1);
    std::map<int, int>::iterator it1 = results2.find(4);
    REQUIRE(it1 == results2.end());
    REQUIRE(results2[200] == 1);
}

// Test suite for 'remove' function of the DSAvlTree class
TEST_CASE("remove", "[DSAvlTree]")
{
    DSAvlTree<std::string, std::string> test1;
    // insertions
    test1.insert("HELLO!", "hi");
    test1.insert("HI", "hi");
    test1.insert("hola", "hi");
    // make sure it contains the things that were inserted
    std::map<std::string, int> results = test1.contains("hola");
    REQUIRE(results.size() == 1);
    // make sure find works
    std::map<std::string, int>::iterator it = results.find("hola");
    REQUIRE(it == results.end());
    it = results.find("hi");
    REQUIRE(it != results.end());
    test1.remove("hola");
    results.erase("hola");

    DSAvlTree<int, int> test2;
    // insertions
    test2.insert(4, 200);
    test2.insert(50, 200);
    test2.insert(600, 200);
    // make sure it contains the things that were inserted
    std::map<int, int> results2 = test2.contains(4);
    REQUIRE(results2.size() == 1);
    // make sure find works
    std::map<int, int>::iterator it1 = results2.find(4);
    REQUIRE(it1 == results2.end());
    REQUIRE(results2[200] == 1);
    test2.remove(4);
    results2.erase(4);
}

// Test suite for the copy constructor of the DSAvlTree class

TEST_CASE("Copy Constructor", "[DSAvlTree]")
{
    // Testing the copy constructor with string-to-string AVL tree
    DSAvlTree<std::string, std::string> test1;
    // insertions
    test1.insert("HELLO!", "hi");
    test1.insert("HI", "hi");
    test1.insert("hola", "hi");
    // make sure everything added is in there
    std::map<std::string, int> results = test1.contains("hola");
    REQUIRE(results.size() == 1);
    std::map<std::string, int>::iterator it = results.find("hola");
    REQUIRE(it == results.end());
    it = results.find("hi");
    REQUIRE(it != results.end());
    // make sure everything copied
    DSAvlTree<std::string, std::string> copyTree(test1);
    std::map<std::string, int> results1 = copyTree.contains("hola");
    REQUIRE(results1.size() == 1);
    std::map<std::string, int>::iterator it1 = results1.find("hola");
    REQUIRE(it1 == results1.end());
    it1 = results1.find("hi");
    REQUIRE(it1 != results1.end());
}

// Test suite for the assignment operator of the DSAvlTree class
TEST_CASE("Assignment Operator", "[DSAvlTree]")
{
    // Testing the assignment operator functionality
    DSAvlTree<std::string, int> original;
    // insertions
    original.insert("HELLO!", 4);
    original.insert("HI", 4);
    original.insert("hola", 4);

    DSAvlTree<std::string, int> copy;
    copy.insert("bye", 10);

    copy = original; // Using the assignment operator

    // Check if elements from original are now in copy
    REQUIRE(copy.contains("HELLO!").size() == 1);
    REQUIRE(copy.contains("HI").size() == 1);
    REQUIRE(copy.contains("hola").size() == 1);

    copy.remove("HELLO!"); // Remove an element from the copy

    // Check if the removal in the copy does not affect the original
    REQUIRE(original.contains("HELLO!").size() == 1);
    REQUIRE(copy.contains("HELLO!").size() == 0);
}
