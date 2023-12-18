#include "QueryProcessor.h"

// Sets the IndexHandler object for the QueryProcessor
void QueryProcessor::setIndexHandler(IndexHandler i)
{
    indexObject = i; // Assign the passed IndexHandler object to indexObject
}

// Parses the query answer and processes it
std::map<std::string, int> QueryProcessor::parsingAnswer(std::string answer) // Parses the answer from the UI
{
    storage.clear(); // Clear any previous data in storage
    std::string temp;
    std::stringstream ss(answer);
    // Tokenizing the answer string by spaces and storing each token
    while (getline(ss, temp, ' '))
    {
        storage.push_back(temp);
    }
    // Dissect the parsed answer to find relevant documents
    return disectAnswer();
}

// Dissects the query, processes different types of search terms and computes the relevant documents
std::map<std::string, int> QueryProcessor::disectAnswer()
{
    // Loop through each term in the storage
    for (size_t i = 0; i < storage.size(); i++)
    {
        // Process organization names
        if (storage[i].length() > 4 && storage[i].substr(0, 4) == "ORG:")
        {
            // Extract and process organization term
            std::string term = storage[i].substr(4, storage[i].length() - 4);
            std::map<std::string, int> docs = indexObject.getOrgs(term);
            relDocs = intersection(relevantDocuments, docs);
        }
        // Process people names
        else if (storage[i].length() > 7 && storage[i].substr(0, 7) == "PERSON:")
        {
            // Extract and process person term
            std::string term = storage[i].substr(7, storage[i].length() - 7);
            std::map<std::string, int> docs = indexObject.getPeople(term);
            relDocs = intersection(relevantDocuments, docs);
        }
        // Process terms to be excluded (negation)
        else if (storage[i].substr(0, 1) == "-")
        {
            // Extract and process negated term
            std::string term = storage[i].substr(1, storage[i].length() - 1);
            Porter2Stemmer::trim(term);
            Porter2Stemmer::stem(term);
            std::map<std::string, int> docs = indexObject.getWords(term);
            relDocs = complement(relevantDocuments, docs);
        }
        // Process regular terms
        else
        {
            // Extract and process regular term
            std::string term = storage[i];
            Porter2Stemmer::trim(term);
            Porter2Stemmer::stem(term);
            if (i == 0)
            {
                relevantDocuments = indexObject.getWords(term);
                sendTo = relevantDocuments;
            }
            else
            {
                std::map<std::string, int> docs = indexObject.getWords(term);
                relDocs = intersection(relevantDocuments, docs);
            }
        }
    }
    // Calculate relevancy of documents
    Relevancy(sendTo);
    return relDocs;
}

// Computes the intersection of two document maps
std::map<std::string, int> QueryProcessor::intersection(std::map<std::string, int> relevantDocuments, std::map<std::string, int> docs) // documents in "A" and "B"
{
    // Logic to find the intersection (common documents) between relevantDocuments and docs
    std::map<std::string, int> finalVector;
    for (const auto &itr : relevantDocuments)
    {
        if (docs.find(itr.first) != docs.end())
        {
            finalVector.emplace(itr.first, itr.second);
        }
    }
    sendTo = finalVector;
    return finalVector;
}

// Computes the complement of two document maps
std::map<std::string, int> QueryProcessor::complement(std::map<std::string, int> relevantDocuments, std::map<std::string, int> docs) // documents in "A" and not "B"
{
    // Logic to find the complement (documents in relevantDocuments but not in docs)
    std::map<std::string, int> finalVector;
    for (const auto &itr : relevantDocuments)
    {
        if (docs.find(itr.first) == docs.end())
        {
            finalVector[itr.first] = itr.second;
        }
    }
    sendTo = finalVector;
    return finalVector;
}

// Calculate the relevancy of documents based on term frequency-inverse document frequency (tf-idf)
std::vector<std::string> QueryProcessor::Relevancy(std::map<std::string, int> sendTo)
{
    for (auto &itr : sendTo)
    {
        // Calculate tf-idf score for each document
        double wordCount = indexObject.getWordCount(itr.first);
        double tf = (double)(itr.second / wordCount);
        double idf = log2((double)(indexObject.getDocSize() / sendTo.size()));
        itr.second = tf * idf;
    }
    // Logic to populate printVector with the top 15 relevant documents (or less if fewer are available)
    if (sendTo.size() <= 15)
    {
        for (const auto &itr : sendTo)
        {
            printVector.push_back(itr.first);
        }
    }
    else
    {
        int index = 0;
        for (const auto &itr : sendTo)
        {
            if (index < 15)
            {
                printVector.push_back(itr.first);
                ++index;
            }
            else
                break;
        }
    }
    return printVector;
}
