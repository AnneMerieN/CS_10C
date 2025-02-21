#include <list>
#include <string>

// CODETURD: In header files, it is a BAD idea to say 'using namespace std'
// instead, we just list all the things we want to use
using std::list;
using std::string;

class WordLadder {

  private:
    list<string> dict;        

    bool checkValidity(const string & word); // helper function

  public:

    WordLadder(const string& filename);
    void outputLadder(const string &start, const string &end, const string &outputFile);
    int findLetterDifference(const string & word1, const string & word2); // helper function
    
};
