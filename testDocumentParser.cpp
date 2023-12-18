#include <iostream>
#include <filesystem>
#include <string>
#include <iomanip>
#include <dirent.h>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "DocumentParser.h"
using namespace rapidjson;

//catch 2 tests for this are not feasible considering return types and complexity of functions
//testing test_IndexHandler.cpp requires doc parser to be working
//therefore cout tests 
int main()
{
 DocumentParser parser;
 
 //printInfo test
 std::cout << "Testing printInfo function";
 std::cout << "Expected print:" << std::endl;
 std::cout << "Title: German firms doing business in UK gloomy about Brexit - survey, Publication: reuters.com, Date Published: 2018-02-27" << std::endl << std::endl;
 std::cout << "Actual print:" << std::endl;
 parser.printInfo("../sample_data/coll_1/news_0064567.json");
 std::cout << std::endl << std::endl;

 //parseDocument test
 std::cout << "Testing parseDocument function";
 std::cout << "Expected print:" << std::endl;
 std::cout << "Document ID: ../sample_data/coll_1/news_0064567.json Word Count: 251" << std::endl << std::endl;
 std::cout << "Actual print:";
 parser.parseDocument("../sample_data/coll_1/news_0064567.json");
 std::cout << std::endl << std::endl;

 //printDocument test
 std::cout << "The following should print out the text from the json" << std::endl;
 std::cout << "Starting with:" << std::endl;
 std::cout << " Title: German firms doing business in UK gloomy about Brexit - survey" << std::endl;
 std::cout << "Text: BERLIN (Reuters) - German businesses that trade in Britain are pessimistic about their prospects there, and some are planning to move" << std::endl;
 std::cout << "Ending with:" <<std::endl;
 std::cout << "Writing by Paul Carrel; Editing by Hugh Lawson" << std::endl;
 std::cout << "Actual test" << std::endl;
 parser.printDocument("../sample_data/coll_1/news_0064567.json");
 std::cout << std::endl << std::endl;

}
