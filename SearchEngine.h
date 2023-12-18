#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

// Including necessary header files
#include "IndexHandler.h"   // Include the IndexHandler header for managing the index of documents
#include "DocumentParser.h" // Include the DocumentParser header for parsing and processing documents
#include "UserInterface.h"  // Include the UserInterface header for handling user interactions
#include "QueryProcessor.h" // Include the QueryProcessor header for processing search queries

// Class definition for SearchEngine
class SearchEngine
{
private:
    // Private member variables
    IndexHandler ih;   // An instance of IndexHandler for handling indexing operations
    DocumentParser dp; // An instance of DocumentParser for parsing documents
    UserInterface ui;  // An instance of UserInterface for managing user interactions
    QueryProcessor qp; // An instance of QueryProcessor for processing user queries

public:
    // Public member function

    // Function to handle input arguments and initialize the search engine
    void input(int, char **); // Takes command line arguments to initialize and run the search engine
};
#endif
