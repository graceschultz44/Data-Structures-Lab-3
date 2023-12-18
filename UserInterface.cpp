#include "UserInterface.h"

// Function to handle the initial question and options for the user interface
void UserInterface::initialQuestion()
{
    std::cout << "Hello! Welcome to our search engine" << std::endl;

    // Continuous loop to keep the program running until the user decides to quit
    while (true)
    {
        // Displaying options to the user
        std::cout << "Please enter a number 1-6 of the options below to continue" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "1) Create an index from a directory with documents" << std::endl;
        std::cout << "2) Write an index to the file" << std::endl;
        std::cout << "3) Read an index from the file" << std::endl;
        std::cout << "4) Enter a query" << std::endl;
        std::cout << "5) See statistics" << std::endl;
        std::cout << "6) Quit" << std::endl;

        // Receiving user input
        std::string answer;
        std::getline(std::cin, answer);

        // Validating and handling user input
        // Invalid input case
        if (!(answer == "1" || answer == "2" || answer == "3" || answer == "4" || answer == "5" || answer == "6"))
        {
            std::cout << "Error! This is an invalid answer. Please select numbers 1 through 6." << std::endl;
            std::getline(std::cin, answer);
        }
        // Option 1: Create index from directory
        else if (answer == "1")
        {
            // Code to create index from a specified directory
            std::cout << "Please enter a directory filepath" << std::endl;
            std::string answer2;
            std::getline(std::cin, answer2);

            auto startTrain = std::chrono::high_resolution_clock::now(); // Start timing the operation
            std::cout << "Reading files..." << std::endl;
            dp.traverseSubdirectory(answer2); // Traverse the directory and index documents
            ih = dp.getIndex();               // Update the index handler with the new index
            std::cout << "Done!" << std::endl;
            auto finishTrain = std::chrono::high_resolution_clock::now(); // End timing the operation
            elapsedTrain = finishTrain - startTrain;                      // Calculate the time taken
        }
        // Option 2: Write index to file
        else if (answer == "2")
        {
            std::cout << "Generating persistence, this may take a moment..." << std::endl;
            auto startTrain = std::chrono::high_resolution_clock::now(); // Start timing the operation
            ih = dp.getIndex();                                          // Retrieve the current index
            ih.createPersistence();                                      // Create a persistent representation of the index
            std::cout << "Persistence was created!" << std::endl;
            auto finishTrain = std::chrono::high_resolution_clock::now(); // End timing the operation
            elapsedTrain = finishTrain - startTrain;                      // Calculate the time taken
        }
        // Option 3: Read index from file
        else if (answer == "3")
        {
            std::cout << "Reading persistence..." << std::endl;
            auto startTrain = std::chrono::high_resolution_clock::now(); // Start timing the operation
            ih.readPersistence();                                        // Read the index from persistence
            dp.setIndex(ih);                                             // Set the index for the document parser
            std::cout << "Persistence has been read!" << std::endl;
            auto finishTrain = std::chrono::high_resolution_clock::now(); // End timing the operation
            elapsedTrain = finishTrain - startTrain;                      // Calculate the time taken
        }
        // Option 4: Enter and process a search query
        else if (answer == "4")
        {
            qp.setIndexHandler(ih); // Set the IndexHandler in QueryProcessor to the current IndexHandler
            std::cout << "Please enter a query" << std::endl;
            std::string answer3;
            std::getline(std::cin, answer3); // Get the user's query as input

            auto startTrain = std::chrono::high_resolution_clock::now();         // Start timing the query processing
            std::map<std::string, int> relevantDocs = qp.parsingAnswer(answer3); // Process the query and get relevant documents

            // Display the relevant documents if there are any
            if (qp.getPrintVectorSize() >= 1)
            {
                int count = 1;
                std::cout << "Here are the most relevant documents" << std::endl;
                for (const auto &item : qp.getPrintVector())
                {
                    std::cout << count << ". ";
                    dp.printInfo(item); // Print information for each relevant document
                    std::cout << std::endl;
                    ++count;
                }
            }

            // Ask the user if they want to see the full content of any document
            std::string yesOrNo;
            std::cout << "Would you like to see the contents of a file listed above?" << std::endl;
            std::getline(std::cin, yesOrNo);

            // Process the user's response
            for (size_t i = 0; i < yesOrNo.length(); i++)
            {
                tolower(yesOrNo.at(i));
            }
            if (yesOrNo == "yes")
            {
                std::cout << "Please enter in the number of the corresponding document that you would like to see." << std::endl;
                std::string number;
                std::getline(std::cin, number);
                int num = stoi(number);                 // Convert the string to a number
                dp.printDocument(qp.getPrint(num - 1)); // Print the selected document
            }
            qp.clearPrintVector(); // Clear the vector for the next query
            auto finishTrain = std::chrono::high_resolution_clock::now();
            elapsedTrain = finishTrain - startTrain; // Calculate the time taken for the query processing
        }
        // Option 5: Display statistics
        else if (answer == "5")
        {
            std::cout << "Here are some of our runtime statistics:" << std::endl;
            std::cout << "Runtime: " << elapsedTrain.count() << " seconds." << std::endl;          // Display the elapsed time for the last operation
            std::cout << "Total articles: " << ih.getDocSize() << std::endl;                       // Display the total number of articles in the index
            std::cout << "Total number of unique words indexed: " << ih.returnSize() << std::endl; // Display the number of unique words indexed
        }
        // Option 6: Quit the program
        else if (answer == "6")
        {
            std::cout << "Thank you for using our search engine." << std::endl;
            break; // Break the loop to exit the program
        }
    }
}
