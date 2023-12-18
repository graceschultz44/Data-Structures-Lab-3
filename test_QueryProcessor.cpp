#define CATCH_CONFIG_MAIN    // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"         // Include the Catch2 header for unit testing
#include <iostream>          // Standard library for input/output streaming
#include <cassert>           // Standard library for assertions
#include <iomanip>           // Standard library for input/output formatting
#include "QueryProcessor.h"  // Include QueryProcessor header for testing
#include "IndexHandler.h"    // Include IndexHandler header for testing
#include "DocumentParser.h"  // Include DocumentParser header for testing
#include "porter2_stemmer.h" // Include Porter2 Stemmer header for testing

// Test case for the query processor functionality
TEST_CASE("query processor", "[QueryProcessor.h]")
{
    // Create instances of DocumentParser, IndexHandler, and QueryProcessor for the test
    DocumentParser dp;
    IndexHandler ih;
    QueryProcessor qp;

    // Parse sample documents using DocumentParser
    dp.parseDocument("../sample_data/coll_1/news_0064567.json");
    dp.parseDocument("../sample_data/coll_1/news_0064568.json");
    dp.parseDocument("../sample_data/coll_1/news_0064569.json");
    dp.parseDocument("../sample_data/coll_2/news_0064571.json");

    // Retrieve the index from DocumentParser and perform persistence operations
    ih = dp.getIndex();     // Get the index from the DocumentParser
    ih.createPersistence(); // Create a persistent representation of the index
    ih.readPersistence();   // Read the index from persistence
    ih = dp.getIndex();     // Update the IndexHandler with the latest index

    // Set the IndexHandler in QueryProcessor
    qp.setIndexHandler(ih);

    // Test 1: Query processing for a specific query string
    std::map<std::string, int> relevantDocs = qp.parsingAnswer("common PERSON:schweitzer");
    REQUIRE(relevantDocs.size() == 1); // Check if the result size is as expected
    relevantDocs.clear();

    // Test 2: Query processing for another query string
    relevantDocs = qp.parsingAnswer("PERIOD PERSON:strax PERSON:ab");
    REQUIRE(relevantDocs.size() == 1); // Check if the result size is as expected
    relevantDocs.clear();

    // Test 3: Query processing for a different query string
    relevantDocs = qp.parsingAnswer("stocks ORGS:carrefour PERSON:jerome powell");
    REQUIRE(relevantDocs.size() == 1); // Check if the result size is as expected
    relevantDocs.clear();
}
