#include "IndexHandler.h"

// Returns a map of words that match the input word
std::map<std::string, int> IndexHandler::getWords(std::string word)
{
    return words.contains(word); // Checks if the word exists in the AVL tree and returns it
}

// Returns the count of occurrences of a specific word in the index
int IndexHandler::getWordCount(std::string title)
{
    return wordCount[title]; // Accesses the word count from the map using the provided title
}

// Returns a map of people that match the input person
std::map<std::string, int> IndexHandler::getPeople(std::string person)
{
    return people.find(person); // Searches for the person in the people hash table and returns it
}

// Returns a map of organizations that match the input organization
std::map<std::string, int> IndexHandler::getOrgs(std::string org)
{
    return orgs.find(org); // Searches for the organization in the orgs hash table and returns it
}

// Adds or updates the word count in the index
void IndexHandler::addWordCount(std::string title, int count)
{
    wordCount[title] = count; // Updates or inserts the word count into the map
}

// Adds a word and its associated filepath to the words AVL tree
void IndexHandler::addWords(std::string word, std::string filepath)
{
    words.insert(word, filepath); // Inserts a new word along with its filepath into the AVL tree
}

// Adds a person and their associated filepath to the people hash table
void IndexHandler::addPeople(std::string person, std::string filepath)
{
    people.insert(person, filepath); // Inserts a new person along with filepath into the hash table
}

// Adds an organization and its associated filepath to the orgs hash table
void IndexHandler::addOrgs(std::string org, std::string filepath)
{
    orgs.insert(org, filepath); // Inserts a new organization along with filepath into the hash table
}

// Adds a document's filepath to the document list
void IndexHandler::addDocument(std::string filepath)
{
    docs.push_back(filepath); // Appends the new document's filepath to the vector
}

// Returns the number of documents in the index
int IndexHandler::getDocSize()
{
    return docs.size(); // Returns the size of the documents vector
}

// Creates a persistent storage of the index data
void IndexHandler::createPersistence()
{
    // Open a file stream for writing
    std::ofstream output("persistence.txt");

    // Check if the file stream is open
    if (!output.is_open())
    {
        std::cerr << "Error! File could not be opened!" << std::endl;
        exit(-1); // Exit if file could not be opened
    }

    // Write words to the file, preceded by a comment for identification
    output << "//words" << std::endl;
    words.printTree(output); // Calls a method to write the AVL tree contents to the file

    // Write people to the file
    output << "//people" << std::endl;
    people.printHash(output); // Calls a method to write the people hash table contents to the file

    // Write organizations to the file
    output << "//orgs" << std::endl;
    orgs.printHash(output); // Calls a method to write the orgs hash table contents to the file

    // Write documents to the file
    output << "//docs" << std::endl;
    for (const auto &itr : docs)
    {
        output << itr << "$" << std::endl; // Write each document's path, ending with a '$' symbol
    }

    // Write word counts to the file
    output << "//wordCount" << std::endl;
    for (const auto &itr : wordCount)
    {
        output << itr.first << "^" << itr.second << "#" << std::endl; // Write each word count entry, formatted as 'word^count#'
    }
}

// Reads and populates the index data from persistent storage
void IndexHandler::readPersistence()
{
    // Open a file stream for reading
    std::ifstream input("persistence.txt");

    // Declare variables for parsing the file
    std::string buffer, answer, node, id, freq, title, count, path;

    // Check if the file stream is open
    if (!input.is_open())
    {
        std::cerr << "Error! File could not be opened!" << std::endl;
        exit(-1); // Exit if file could not be opened
    }

    // Read the file line by line
    while (getline(input, buffer))
    {
        int index = 0; // Variable to keep track of the parsing position

        // Iterate over characters in the line
        for (size_t i = 0; i < buffer.length(); i++)
        {
            if (buffer[i] == '/' && buffer[i + 1] == '/')
            {
                answer = buffer.substr(2, buffer.length()); // Extract the section identifier
                break;
            }
            else if (buffer[i] == ':')
            {
                node = buffer.substr(index, i - index); // Extract node value
                index = i + 1;
            }
            else if (buffer[i] == ',')
            {
                id = buffer.substr(index, i - index); // Extract ID value
                index = i + 1;
            }
            else if (buffer[i] == ';')
            {
                freq = buffer.substr(index, i - index); // Extract frequency
                index = i + 1;
                int num = stoi(freq); // Convert frequency to integer
                // Insert data into appropriate data structure based on section identifier
                if (answer == "words")
                    words.insert(node, id, num);
                else if (answer == "people")
                    people.insert(node, id, num);
                else if (answer == "orgs")
                    orgs.insert(node, id, num);
            }
            else if (buffer[i] == '^')
            {
                title = buffer.substr(index, i - index); // Extract title
                index = i + 1;
            }
            else if (buffer[i] == '$')
            {
                path = buffer.substr(index, i - index); // Extract file path
                docs.push_back(path);                   // Add file path to documents vector
            }
            else if (buffer[i] == '#')
            {
                count = buffer.substr(index, i - index); // Extract count
                index = i + 1;
                int num2 = stoi(count);  // Convert count to integer
                wordCount[title] = num2; // Add word count to wordCount map
            }
        }
    }
    input.close(); // Close the file stream
}

// Returns the size of the words AVL tree
int IndexHandler::returnSize()
{
    return words.getSize(); // Returns the size of the AVL tree containing words
}
