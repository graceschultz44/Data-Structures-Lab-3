#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

// Including necessary header files
#include <iostream>         // Standard library for input/output streaming
#include <cstdio>           // Standard C library for input/output operations
#include <chrono>           // Standard library for dealing with time
#include "QueryProcessor.h" // Include the QueryProcessor header for processing search queries
#include "IndexHandler.h"   // Include the IndexHandler header for managing the index of documents
#include "DocumentParser.h" // Include the DocumentParser header for parsing and processing documents

// Class definition for UserInterface
class UserInterface
{
private:
    // Private member variables
    std::chrono::duration<double> elapsedTrain; // Variable to track time duration, possibly for performance measurement
    IndexHandler ih;                            // An instance of IndexHandler for handling indexing operations
    QueryProcessor qp;                          // An instance of QueryProcessor for processing user queries
    DocumentParser dp;                          // An instance of DocumentParser for parsing documents

public:
    // Public member function

    // Function to initiate and handle the initial user interaction
    void initialQuestion(); // Method to ask the initial question or provide options to the user
};
#endif
