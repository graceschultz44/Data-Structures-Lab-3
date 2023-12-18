#include <iostream>
#include "SearchEngine.h" //include the search engine
using namespace std;

int main(int argc, char **argv)
{
    SearchEngine se;      // create an instances of search engine
    se.input(argc, argv); // pass in argc and argv
}
