# cmake_minimum_required(VERSION 3.15)
# project(FinalProjExamples)

# # filesystem.h require C++17
# set(CMAKE_CXX_STANDARD 17)

# file(COPY sample_data/ DESTINATION sample_data/)

# # show compiler output and enable warnings
# set(CMAKE_VERBOSE_MAKEFILE ON)
# add_compile_options(-Wall -Wextra -pedantic)

# add_executable(rapidJSONExample rapidJSONExample.cpp)
# add_executable(supersearch main.cpp)

# # this makes sure we also link rapidjson
# target_include_directories(rapidJSONExample PRIVATE rapidjson/)

# set(CMAKE_VERBOSE_MAKEFILE OFF)

# # testing with the single_include versions of Catch2 V2 (in directory catch2)
# include(CTest)
# add_executable(test_DSAvlTree test_DSAvlTree.cpp)
# add_test(NAME TestAvlTree COMMAND test_DSAvlTree)
# include(CTest)
# add_executable(test_DSHash test_DSHash.cpp)
# add_test(NAME TestHash COMMAND test_DSHash)

# #add a testDocumentParser
# include(CTest)
# add_executable(testDocumentParser testDocumentParser.cpp DocumentParser.cpp porter2_stemmer.cpp IndexHandler.cpp)
# add_test(NAME testDocumentParser COMMAND testDocumentParser)

# include(CTest)
# add_executable(mainTest main.cpp DocumentParser.cpp porter2_stemmer.cpp IndexHandler.cpp UserInterface.cpp QueryProcessor.cpp)
# add_test(NAME mainTest COMMAND mainTest)


cmake_minimum_required(VERSION 3.15)
project(FinalProjExamples)

# Set C++17 as the standard for the project
set(CMAKE_CXX_STANDARD 17)

# Copy sample data if necessary
file(COPY sample_data/ DESTINATION sample_data/)

# Enable verbose output and add compiler warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

# Create the rapidJSONExample executable
add_executable(rapidJSONExample rapidJSONExample.cpp)

# Create the supersearch executable with all necessary source files
add_executable(supersearch main.cpp UserInterface.cpp DocumentParser.cpp QueryProcessor.cpp IndexHandler.cpp SearchEngine.cpp porter2_stemmer.cpp)

# If you have other dependencies like headers, libraries, etc., link them here
# For example: target_link_libraries(supersearch some_library)

# Include directories if there are any
# For example: target_include_directories(supersearch PRIVATE some/include/path)

# Testing setup with Catch2
include(CTest)

# Define tests - Ensure test source files are correctly listed
add_executable(test_DSAvlTree test_DSAvlTree.cpp)
add_test(NAME TestAvlTree COMMAND test_DSAvlTree)

add_executable(test_IndexHandler test_IndexHandler.cpp IndexHandler.cpp porter2_stemmer.cpp DocumentParser.cpp)
add_test(NAME TestIndexHandler COMMAND test_IndexHandler)

add_executable(test_DSHash test_DSHash.cpp)
add_test(NAME TestHash COMMAND test_DSHash)

add_executable(testDocumentParser testDocumentParser.cpp DocumentParser.cpp porter2_stemmer.cpp IndexHandler.cpp)
add_test(NAME testDocumentParser COMMAND testDocumentParser)

add_executable(test_QueryProcessor test_QueryProcessor.cpp QueryProcessor.cpp IndexHandler.cpp porter2_stemmer.cpp DocumentParser.cpp)
add_test(NAME TestQueryProcessor COMMAND test_QueryProcessor)

# Add more tests as needed
