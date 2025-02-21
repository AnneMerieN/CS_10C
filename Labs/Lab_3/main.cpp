#include "WordLadder.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::runtime_error;

int main() {
  string dictFile, wordBegin, wordEnd, outFile;
  cout << "Enter the name of the dictionary file: ";
  cin >> dictFile;
  cout << endl;
  cout << "Enter the name of the output file: ";
  cin >> outFile;
  cout << endl;
  cout << "Enter the first word: ";
  cin >> wordBegin;
  cout << endl;

  if (not cin) {
    throw runtime_error("Cannot open file");
  }

  while (wordBegin.size() != 5) {
    cout << "Word must have exactly 5 characters." << endl
         << "Please reenter the first word: ";
    if (not (cin >> wordBegin)) {
      throw runtime_error("Could not read 5 character first word");
    }
    cout << endl;
  }
  cout << "Enter the last word: ";
  if (not (cin >> wordEnd)) {
      throw runtime_error("Could not read 5 character last word");
  }
  cout << endl;
  while (wordEnd.size() != 5) {
    cout << "Word must have exactly 5 characters." << endl
         << "Please reenter the last word: ";
    cin >> wordEnd;
    if (not (cin >> wordEnd)) {
      throw runtime_error("Could not read 5 character last word");
    }
    cout << endl;
  }
   
  WordLadder wl(dictFile);
	
  wl.outputLadder(wordBegin, wordEnd, outFile);
  return 0;
}

