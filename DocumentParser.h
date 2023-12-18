// Guard to prevent multiple inclusions of this header file
#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H

// Including necessary header files
#include "IndexHandler.h"             // Include the IndexHandler header for indexing functionality
#include "rapidjson/istreamwrapper.h" // Include RapidJSON's istreamwrapper for handling JSON streams
#include "rapidjson/document.h"       // Include RapidJSON's document header for parsing JSON documents
#include "porter2_stemmer.h"          // Include the Porter Stemmer header for word stemming functionality
#include <string>                     // Standard library for string handling
#include <vector>                     // Standard library for vector data structure
#include <map>                        // Standard library for map data structure
#include <iostream>                   // Standard library for input/output streaming
#include <fstream>                    // Standard library for file streaming
#include <sstream>                    // Standard library for string streaming
#include <iomanip>                    // Standard library for input/output formatting
#include <filesystem>                 // Standard library for filesystem operations
#include <dirent.h>                   // Include for directory traversing
#include <algorithm>                  // Standard library for various algorithms
#include <set>                        // Standard library for set data structure

// Class definition for DocumentParser
class DocumentParser
{
private:
    // Private member variables
    IndexHandler ih;                 // An instance of IndexHandler for handling indexing operations
    std::vector<std::string> titles; // A vector to store document titles

public:
    // Public member functions

    // Parses a JSON document and indexes its content
    void parseDocument(const std::string &jsonContent);

    // Prints the content of a JSON document
    void printDocument(const std::string &jsonContent);

    // Sets the index handler for the parser
    void setIndex(IndexHandler ih);

    // Retrieves the index handler used by the parser
    IndexHandler getIndex();

    // Traverses a given directory and processes subdirectories
    void traverseSubdirectory(const std::string &directoryPath);

    // Prints information extracted from a JSON document
    void printInfo(const std::string &jsonContent);

    // Retrieves the title of a document given its index
    std::string getTitle(int num) { return titles[num]; };
};

#endif
