#ifndef INDEX_HANDLER_H
#define INDEX_HANDLER_H

// Including necessary header files
#include "Hash.h"      // Include custom Hash table implementation
#include "DSAvlTree.h" // Include custom AVL Tree implementation
#include <algorithm>   // Standard library for various algorithms
#include <string>      // Standard library for string handling
#include <map>         // Standard library for map data structure
#include <vector>      // Standard library for vector data structure

// Class definition for IndexHandler
class IndexHandler
{
private:
    // AVL Tree to store words. Maps string to string.
    DSAvlTree<std::string, std::string> words;

    // Hash tables for people and organizations. Maps string to string.
    Hash<std::string, std::string> people;
    Hash<std::string, std::string> orgs;

    // Vector to store document strings
    std::vector<std::string> docs;

    // Map to store word count. Maps string to an integer.
    std::map<std::string, int> wordCount;

public:
    // Public member functions to interact with the IndexHandler

    // Retrieves a map of words given a string
    std::map<std::string, int> getWords(std::string);

    // Retrieves a map of people given a string
    std::map<std::string, int> getPeople(std::string);

    // Retrieves a map of organizations given a string
    std::map<std::string, int> getOrgs(std::string);

    // Returns the count of a specific word
    int getWordCount(std::string);

    // Adds words to the words AVL tree
    void addWords(std::string, std::string);

    // Adds people to the people hash table
    void addPeople(std::string, std::string);

    // Adds organizations to the orgs hash table
    void addOrgs(std::string, std::string);

    // Adds a document to the docs vector
    void addDocument(std::string);

    // Add word count in the wordCount map
    void addWordCount(std::string, int);

    // Returns the size of the documents vector
    int getDocSize();

    // Function to create persistence
    void createPersistence();

    // Function to read from persistence
    void readPersistence();

    // Returns the size of words tree
    int returnSize();
};

#endif
