#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include "IndexHandler.h"
#include "porter2_stemmer.h"

// Class definition for QueryProcessor
class QueryProcessor
{
private:
    // Private member variables
    std::vector<std::string> storage;             // Stores query components during processing
    std::map<std::string, int> relevantDocuments; // Maps documents to their relevance scores
    std::map<std::string, int> relDocs;           // Another map for storing relevant documents
    std::map<std::string, int> sendTo;            // Used in processing the query to map documents
    IndexHandler indexObject;                     // IndexHandler instance for accessing the indexed data
    std::vector<std::string> printVector;         // Stores the results for printing

public:
    // Getter for the printVector
    std::vector<std::string> getPrintVector() { return printVector; };

    // Getter for the size of printVector
    int getPrintVectorSize() { return printVector.size(); };

    // Retrieves a specific item from printVector
    std::string getPrint(int num) { return printVector[num]; };

    // Clears the printVector
    void clearPrintVector() { printVector.clear(); };

    // Parses a query string and returns relevant documents
    std::map<std::string, int> parsingAnswer(std::string);

    // Dissects the answer to aid in query processing
    std::map<std::string, int> disectAnswer();

    // Calculates the intersection of two maps - useful in query logic
    std::map<std::string, int> intersection(std::map<std::string, int>, std::map<std::string, int>);

    // Calculates the complement of two maps - useful in query logic
    std::map<std::string, int> complement(std::map<std::string, int>, std::map<std::string, int>);

    // Sets the IndexHandler object for query processing
    void setIndexHandler(IndexHandler i);

    // Determines the relevancy of documents for the query
    std::vector<std::string> Relevancy(std::map<std::string, int>);

    // Implements quickSort algorithm for sorting documents based on relevancy
    void quickSort(std::map<std::string, int> &, int, int);

    // Helper function for quickSort to partition the map
    int partition(std::map<std::string, int>, int, int);
};
#endif
