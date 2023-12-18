#include "DocumentParser.h"
using namespace rapidjson;
using namespace std;

// list of stopwords found from https://gist.github.com/sebleier/554280 NLTK list of english stopwords
set<string> stopWords = {"able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after",
                         "afterwards", "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows", "almost",
                         "alone", "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst",
                         "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything",
                         "anyway", "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "aren't", "around",
                         "as", "a's", "aside", "ask", "asking", "associated", "at", "available", "away", "awfully",
                         "back", "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming", "been",
                         "before", "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best",
                         "better", "between", "beyond", "both", "brief", "but", "by", "came", "can", "cannot",
                         "cant", "can't", "caption", "cause", "causes", "certain", "certainly", "changes", "clearly", "c'mon",
                         "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider", "considering", "contain",
                         "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently", "dare", "daren't",
                         "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does", "doesn't",
                         "doing", "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight",
                         "eighty", "either", "else", "elsewhere", "end", "ending", "enough", "entirely", "especially", "et",
                         "etc", "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex",
                         "exactly", "example", "except", "fairly", "far", "farther", "few", "fewer", "fifth", "first",
                         "five", "followed", "following", "follows", "for", "forever", "former", "formerly", "forth", "forward",
                         "found", "four", "from", "further", "furthermore", "get", "gets", "getting", "given", "gives",
                         "go", "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half",
                         "happens", "hardly", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll",
                         "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "here's", "hereupon",
                         "hers", "herself", "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how",
                         "howbeit", "however", "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate",
                         "in", "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated", "indicates", "inner", "inside",
                         "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its",
                         "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known",
                         "knows", "last", "lately", "later", "latter", "latterly", "least", "less", "lest", "let",
                         "let's", "like", "liked", "likely", "likewise", "little", "look", "looking", "looks", "low",
                         "lower", "ltd", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't",
                         "me", "mean", "meantime", "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss",
                         "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my",
                         "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needn't", "needs",
                         "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no",
                         "nobody", "non", "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing",
                         "notwithstanding", "novel", "now", "nowhere", "obviously", "of", "off", "often", "oh", "ok",
                         "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite",
                         "or", "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out",
                         "outside", "over", "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed",
                         "please", "plus", "possible", "presumably", "probably", "provided", "provides", "que", "quite", "qv",
                         "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards",
                         "relatively", "respectively", "right", "round", "said", "same", "saw", "say", "saying", "says",
                         "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self",
                         "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "shan't", "she",
                         "she'd", "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some", "somebody",
                         "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry",
                         "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "take", "taken",
                         "taking", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll",
                         "thats", "that's", "that've", "the", "their", "theirs", "them", "themselves", "then", "thence",
                         "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's",
                         "thereupon", "there've", "these", "they", "they'd", "they'll", "they're", "they've", "thing", "things",
                         "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three", "through",
                         "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards",
                         "tried", "tries", "truly", "try", "trying", "t's", "twice", "two", "un", "under",
                         "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon",
                         "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value",
                         "various", "versus", "very", "via", "viz", "vs", "want", "wants", "was", "wasn't",
                         "way", "we", "we'd", "welcome", "well", "we'll", "went", "were", "we're", "weren't",
                         "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence", "whenever", "where",
                         "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever", "whether", "which", "whichever",
                         "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever",
                         "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder",
                         "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your", "you're",
                         "yours", "yourself", "yourselves", "you've", "zero"};

// Sets the IndexHandler instance for this DocumentParser
void DocumentParser::setIndex(IndexHandler index)
{
    ih = index; // Assigns the provided IndexHandler to the local instance
}

// Returns the IndexHandler instance used by this DocumentParser
IndexHandler DocumentParser::getIndex()
{
    return ih; // Returns the current IndexHandler instance
}

// Prints basic information extracted from the JSON content of a document
void DocumentParser::printInfo(const string &jsonContent)
{
    // Variables to store extracted information
    string title, publication, datePublished, finalInfoString;

    // Open the JSON file
    ifstream ifs(jsonContent);
    if (!ifs.is_open())
    {
        cerr << "Could not open file for reading: " << jsonContent << endl;
        return;
    }

    // Parse the JSON document
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    if (d.HasParseError())
    {
        cerr << "JSON parse error: " << d.GetParseError() << endl;
        return;
    }

    // Extract and process relevant information from the JSON document
    // Extract title
    if (d.HasMember("title") && d["title"].IsString())
    {
        title = d["title"].GetString();
    }
    // Extract publication site
    if (d.HasMember("thread") && d["thread"].IsObject())
    {
        if (d["thread"].HasMember("site") && d["thread"]["site"].IsString())
        {
            publication = d["thread"]["site"].GetString();
        }
    }
    // Extract date published and format it
    if (d.HasMember("published") && d["published"].IsString())
    {
        datePublished = d["published"].GetString();
        datePublished = datePublished.substr(0, 10); // Extracting only the date part
    }

    // Combine extracted information into a single string and print
    finalInfoString = "Title: " + title + ", Publication: " + publication + ", Date Published: " + datePublished;
    cout << finalInfoString << endl;
}

// Parses a document from its JSON content and indexes its data
void DocumentParser::parseDocument(const string &jsonContent)
{
    // Variable declarations for parsing
    int wordCount = 0;
    string docPersons, org, title;

    // Open the JSON file
    ifstream ifs(jsonContent);
    if (!ifs.is_open())
    {
        cerr << "Could not open file for reading: " << jsonContent << endl;
        return;
    }

    // Parse the JSON document
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    if (d.HasParseError())
    {
        cerr << "JSON parse error: " << d.GetParseError() << endl;
        return;
    }

    // Parsing and processing logic for different parts of the JSON document
    // Extract title and add to IndexHandler
    if (d.HasMember("title") && d["title"].IsString())
    {
        title = d["title"].GetString();
        ih.addDocument(jsonContent); // Adding file path to IndexHandler
    }
    if (d.HasMember("entities") && d["entities"].IsObject()) // parse through and add all of the people in each doc
    {
        const rapidjson::Value &entities = d["entities"];
        if (entities.HasMember("persons") && entities["persons"].IsArray())
        {
            const rapidjson::Value &personsArray = entities["persons"];
            for (rapidjson::SizeType i = 0; i < personsArray.Size(); i++)
            {
                if (personsArray[i].IsObject())
                {
                    const rapidjson::Value &personObject = personsArray[i];
                    if (personObject.HasMember("name") && personObject["name"].IsString())
                    {
                        std::string allPeople;
                        allPeople = personObject["name"].GetString();
                        istringstream iss5(allPeople);

                        while (iss5 >> docPersons)
                        {
                            ih.addPeople(docPersons, jsonContent); // call index handler to add the people
                        }
                    }
                }
            }
        }
    }

    if (d.HasMember("entities") && d["entities"].IsObject())
    {
        const rapidjson::Value &entities = d["entities"];
        if (entities.HasMember("organizations") && entities["organizations"].IsArray()) // parse through and add all of the organizations
        {
            const rapidjson::Value &orgsArray = entities["organizations"];
            for (rapidjson::SizeType i = 0; i < orgsArray.Size(); i++)
            {
                if (orgsArray[i].IsObject())
                {
                    const rapidjson::Value &orgsObject = orgsArray[i];
                    if (orgsObject.HasMember("name") && orgsObject["name"].IsString())
                    {
                        std::string allOrgs;
                        allOrgs = orgsObject["name"].GetString();
                        istringstream iss6(allOrgs);

                        while (iss6 >> org)
                        {
                            ih.addOrgs(org, jsonContent); // add the organizations through indexHandler
                        }
                    }
                }
            }
        }
    }

    if (d.HasMember("text") && d["text"].IsString())
    {
        // Extract and process text content
        string text = d["text"].GetString();
        istringstream iss(text);
        string word;
        while (iss >> word)
        {
            // Word processing and stemming logic
            // Remove non-alphabetic characters, convert to lowercase, apply stemming
            word.erase(remove_if(word.begin(), word.end(), [](char c)
                                 { return !isalpha(c); }),
                       word.end());

            transform(word.begin(), word.end(), word.begin(), ::tolower);
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            // Check and index words not in stopWords
            if (stopWords.find(word) == stopWords.end())
            {
                ih.addWords(word, jsonContent);          // Add word to IndexHandler
                wordCount++;                             // Increment word count
                ih.addWordCount(jsonContent, wordCount); // Update word count in IndexHandler
            }
        }
    }
    else
    {
        cerr << "The JSON does not contain a 'text' attribute or it is not a string." << endl;
    }
    std::cout << endl;
    std::cout << "Document ID: " << jsonContent << " Word Count: " << wordCount << endl;
}

// Traverses a directory and processes each file within it
void DocumentParser::traverseSubdirectory(const string &directoryPath)
{
    // Open the directory
    DIR *dir = opendir(directoryPath.c_str()); // c_str so it can be passed to opendir
    if (dir == nullptr)
    {
        cerr << "Could not open directory: " << directoryPath << endl;
        return;
    }
    struct dirent *entry;
    vector<string> subdirectories;
    // Read the directory entries
    while ((entry = readdir(dir)) != nullptr)
    {
        // Exclude the current (.) and parent (..) directories
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            subdirectories.push_back(entry->d_name);
        }
    }
    // Close the directory
    closedir(dir);
    // Iterate over the subdirectories to read their contents
    for (const auto &subdir : subdirectories)
    {
        string subdirPath = directoryPath + "/" + subdir;
        DIR *subDir = opendir(subdirPath.c_str());
        if (subDir == nullptr)
        {
            cerr << "Could not open subdirectory: " << subdirPath << endl;
            continue;
        }

        std::cout << "Contents of subdirectory: " << subdir << endl;
        // Read the subdirectory entries
        while ((entry = readdir(subDir)) != nullptr)
        {
            string filePath = subdirPath + "/" + entry->d_name;
            parseDocument(filePath);
        }
        // Close the subdirectory
        closedir(subDir);
    }
}

void DocumentParser::printDocument(const string &jsonContent)
{
    int wordCount = 0; // declare all of the variables
    string docID;
    string docPersons;
    string org;
    string title;
    ifstream ifs(jsonContent);
    if (!ifs.is_open()) // make sure the file opens
    {
        cerr << "Could not open file for reading: " << jsonContent << endl;
        return;
    }
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw); // parse through the document
    if (d.HasParseError())
    {
        cerr << "JSON parse error: " << d.GetParseError() << endl;
        return;
    }
    if (d.HasMember("title") && d["title"].IsString()) // print out all of the information in the document
    {
        title = d["title"].GetString();
        std::cout << "Title: " << title << endl;
    }

    if (d.HasMember("persons") && d["persons"].IsString())
    {
        string allPeople = d["persons"].GetString();
        std::cout << "Persons: " << allPeople << endl;
    }
    if (d.HasMember("organizations") && d["organizations"].IsString())
    {
        string allOrgs = d["organizations"].GetString();
        std::cout << "Organizations: " << allOrgs << endl;
    }
    if (d.HasMember("text") && d["text"].IsString())
    {
        string text = d["text"].GetString();
        std::cout << "Text: " << text << endl;
    }
    else
    {
        cerr << "The JSON does not contain a 'text' attribute or it is not a string." << endl;
    }
    std::cout << endl;
}
