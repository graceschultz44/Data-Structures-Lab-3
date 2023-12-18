#include "SearchEngine.h"
#include <iostream>
#include <cstdio>
#include <chrono>

// Function to process input commands for the search engine
void SearchEngine::input(int num, char **answer)
{
  // Check if the command is to create an index
  if (strcmp(answer[1], "index") == 0)
  {
    std::cout << "Reading files..." << std::endl;
    dp.traverseSubdirectory(answer[2]); // Traverse and parse documents in the specified directory
    ih = dp.getIndex();                 // Retrieve and set the index from DocumentParser
    std::cout << "Done!" << std::endl;
    std::cout << "Creating persistence, this may take a minute..." << std::endl;
    ih.createPersistence(); // Create persistent data for the index
    std::cout << "Persistence has been created!" << std::endl;
  }
  // Check if the command is to process a query
  else if (strcmp(answer[1], "query") == 0)
  {
    std::cout << "Reading persistence..." << std::endl;
    ih.readPersistence(); // Read the persistent data into the index
    std::cout << "Persistence has been read!" << std::endl;
    dp.setIndex(ih);        // Set the index for DocumentParser
    qp.setIndexHandler(ih); // Set the index for QueryProcessor

    // Combine the query parts into a single string
    std::string answer2 = answer[2];
    for (int i = 3; i < num; i++)
    {
      answer2 = answer2 + " " + answer[i];
    }

    // Process the query and retrieve relevant documents
    std::map<std::string, int> relevantDocs = qp.parsingAnswer(answer2);
    int count = 1;
    std::cout << "Here are the most relevant documents" << std::endl;
    // Print the information of relevant documents
    for (const auto &item : qp.getPrintVector())
    {
      std::cout << count << ". ";
      dp.printInfo(item); // Print document information
      std::cout << std::endl;
      ++count;
    }

    // Interact with the user to show document contents
    std::string yesOrNo;
    std::cout << "Would you like to see the contents of a file listed above?" << std::endl;
    std::getline(std::cin, yesOrNo);
    for (size_t i = 0; i < yesOrNo.length(); i++)
    {
      tolower(yesOrNo.at(i)); // Convert response to lowercase
    }
    if (yesOrNo == "yes")
    {
      std::cout << "Please enter in the number of the corresponding document that you would like to see." << std::endl;
      std::string number;
      std::getline(std::cin, number);         // Get the document number from user
      int num = stoi(number);                 // Convert input to an integer
      dp.printDocument(qp.getPrint(num - 1)); // Print the selected document
    }
    qp.clearPrintVector(); // Clear the vector for next query
  }
  // Check if the command is to interact through the user interface
  else if (strcmp(answer[1], "ui") == 0)
  {
    ih.readPersistence(); // Read the persistent data into the index
    ui.initialQuestion(); // Start the user interface interaction
  }
}
