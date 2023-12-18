#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "IndexHandler.h"
#include "DocumentParser.h"
using namespace std;

// Test suite for IndexHandler
TEST_CASE("IndexHandler Test", "[IndexHandler]")
{
    // Initialize DocumentParser for document parsing
    DocumentParser dp;

    // Parsing documents for testing
    dp.parseDocument("../sample_data/coll_1/news_0064567.json");
    IndexHandler ih = dp.getIndex(); // Getting the IndexHandler from DocumentParser

    // Test case to verify getWords functionality
    SECTION("getWords Test")
    {
        // Tests to verify the correct mapping of words to their counts and document paths
        // Each REQUIRE checks that the function returns the expected number of occurrences and paths
        // Test cases for different words and their expected occurrences
        map<string, int> result = ih.getWords("plan");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/coll_1/news_0064567.json"] == 2);

        map<string, int> result1 = ih.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/coll_1/news_0064567.json"] == 4);

        map<string, int> result2 = ih.getWords("interest");
        REQUIRE(result2.size() == 1);
        REQUIRE(result2["../sample_data/coll_1/news_0064567.json"] == 1);

        map<string, int> result3 = ih.getWords("prospect");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/coll_1/news_0064567.json"] == 3);

        map<string, int> result5 = ih.getWords("potato");
        REQUIRE(result5.size() == 0);

        map<string, int> result6 = ih.getWords("orange");
        REQUIRE(result6.size() == 0);
    }

    // Test case to verify getPeople functionality
    SECTION("getPeople Test")
    {
        // Tests to verify the correct mapping of people's names to their counts and document paths
        // Each REQUIRE checks that the function returns the expected number of occurrences and paths

        // Test cases for different names and their expected occurrences
        map<string, int> result4 = ih.getPeople("schweitzer");
        REQUIRE(result4.size() == 1);
        map<string, int> result5 = ih.getPeople("adam");
        REQUIRE(result5.size() == 0);
        map<string, int> result6 = ih.getPeople("george");
        REQUIRE(result6.size() == 0);
        map<string, int> result7 = ih.getPeople("sarah");
        REQUIRE(result7.size() == 0);
    }
    // Test case to verify getWordCount functionality
    SECTION("getWordCount Test")
    {
        // Test to verify the correct count of words in a specific document
        // REQUIRE checks that the function returns the expected word count for the document

        // Test case for a specific document and its expected word count
        REQUIRE(ih.getWordCount("../sample_data/coll_1/news_0064567.json") == 251);
    }

    // Test case to verify getOrgs functionality
    SECTION("getOrgs Test")
    {
        // Tests to verify the correct mapping of organizations' names to their counts and document paths
        // Each REQUIRE checks that the function returns the expected number of occurrences and paths

        // Test cases for different organizations and their expected occurrences
        map<string, int> result = ih.getOrgs("cnn");
        REQUIRE(result.size() == 0);
        map<string, int> result1 = ih.getOrgs("nbc");
        REQUIRE(result1.size() == 0);
        map<string, int> result2 = ih.getOrgs("abc");
        REQUIRE(result2.size() == 0);
        map<string, int> result3 = ih.getOrgs("reuters");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/coll_1/news_0064567.json"] == 1);
    }

    // Test case to verify persistence functionality
    SECTION("Persistance tests")
    {
        // Testing the persistence functionality of IndexHandler
        // This includes creating persistence, reading it back, and verifying the data

        ih.createPersistence(); // Creating persistence from the IndexHandler data

        IndexHandler index;
        index.readPersistence(); // Reading the persisted data into a new IndexHandler instance

        // Tests to verify the data integrity after reading from persistence
        // Test cases to verify the correct data is retrieved after persistence

        map<string, int> result = index.getWords("plan");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/coll_1/news_0064567.json"] == 2); // should be 2
        REQUIRE(result["../sample_data/coll_1/news_0064567.json"] == 2);
        map<string, int> result1 = index.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/coll_1/news_0064567.json"] == 4);
        map<string, int> result2 = index.getWords("interest");
        REQUIRE(result2.size() == 1);
        REQUIRE(result2["../sample_data/coll_1/news_0064567.json"] == 1);
        map<string, int> result3 = index.getWords("prospect");
        REQUIRE(result3.size() == 1);
        REQUIRE(result3["../sample_data/coll_1/news_0064567.json"] == 3);
        map<string, int> result5 = index.getWords("potato");
        REQUIRE(result5.size() == 0);
        map<string, int> result6 = index.getWords("orange");
        REQUIRE(result6.size() == 0);
        map<string, int> result10 = index.getPeople("schweitzer");
        REQUIRE(result10.size() == 1);
        map<string, int> result11 = index.getPeople("adam");
        REQUIRE(result11.size() == 0);
        map<string, int> result12 = index.getPeople("george");
        REQUIRE(result12.size() == 0);
        map<string, int> result13 = index.getPeople("sarah");
        REQUIRE(result13.size() == 0);

        REQUIRE(index.getWordCount("../sample_data/coll_1/news_0064567.json") == 251);

        map<string, int> result14 = index.getOrgs("cnn");
        REQUIRE(result14.size() == 0);
        map<string, int> result15 = index.getOrgs("nbc");
        REQUIRE(result15.size() == 0);
        map<string, int> result16 = index.getOrgs("abc");
        REQUIRE(result16.size() == 0);
        map<string, int> result17 = index.getOrgs("Reuters");
        REQUIRE(result17.size() == 0);

        REQUIRE(index.getDocSize() == 1);
    }

    // Test case to verify functionality with multiple documents
    SECTION("Multiple Doc Testing")
    {
        // Additional parsing of a document
        dp.parseDocument("../sample_data/coll_1/news_0064568.json");
        IndexHandler ih = dp.getIndex(); // Update IndexHandler with new data

        // Tests to verify the correct handling of multiple documents
        // Test cases for words present in multiple documents

        map<string, int> result1 = ih.getWords("german");
        REQUIRE(result1.size() == 1);
        REQUIRE(result1["../sample_data/coll_1/news_0064567.json"] == 4);

        map<string, int> result2 = ih.getWords("group");
        REQUIRE(result2.size() == 2);
        REQUIRE(result2["../sample_data/coll_1/news_0064567.json"] == 1);
        REQUIRE(result2["../sample_data/coll_1/news_0064568.json"] == 2);

        ih.createPersistence();

        IndexHandler index2;

        index2.readPersistence();

        map<string, int> result = ih.getWords("german");
        REQUIRE(result.size() == 1);
        REQUIRE(result["../sample_data/coll_1/news_0064567.json"] == 4);

        map<string, int> result3 = ih.getWords("group");
        REQUIRE(result3.size() == 2);
        REQUIRE(result3["../sample_data/coll_1/news_0064567.json"] == 1);
        REQUIRE(result3["../sample_data/coll_1/news_0064568.json"] == 2);
    }
}
