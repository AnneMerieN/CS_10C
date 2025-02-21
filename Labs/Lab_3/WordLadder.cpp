#include "WordLadder.h"
#include <iostream>
#include <fstream> 
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

// Constructor
WordLadder::WordLadder(const string& filename) {
  ifstream inFS;
  inFS.open(filename); // open file
  if (!inFS.is_open()) { // check if file opened properly
    throw runtime_error("Error opening file"); // throw exception if can't open
  }

  string word; // variable to store each word from the file
  while (!inFS.eof()) { // loop to go to end of file
    getline(inFS, word); // reads word from file up to newline
    if (word.size() == 5) { // checks if size of word is 5
      dict.push_back(word); // if size is 5, push word onto list
    } else if (word.size() != 0) {
      throw runtime_error("Invalid string length.");
    }
  }
  inFS.close();

}

// Function to output word ladder from a start to an end word
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  ofstream outFS;
  outFS.open(outputFile);
  if (!outFS.is_open()) { // check if output file opened properly
    return;
  }
  if (!checkValidity(start) || !checkValidity(end)) { // if either start or end are invalid
    throw runtime_error("Incorrect input");
  }
  if (start == end) { // checks if start word is the same as end word
    outFS << end;
    outFS.close();
    return;
  }
  // Create stack and initialize it with end word
  stack<string> startLadder; 
  startLadder.push(end); 

  // Create queue and initialize it with ladder
  queue<stack<string>> ladderQueue; 
  ladderQueue.push(startLadder);

  while (!ladderQueue.empty()) { // while ladderQueue is not empty
    string topWord = ladderQueue.front().top(); // retrieves top word from the stack
        list<string>::iterator i;
        for (i = dict.begin(); i != dict.end(); ++i) { // iterate through 'dict' list
            if (findLetterDifference(*i, topWord) == 1) { // checks if the difference bttween the current word and the top word is only one letter
                stack<string> newLadder = ladderQueue.front(); // if true, a new ladder stack is created which is a copy of the current ladder with the the current word '*i' pushed onto it
                newLadder.push(*i);
                if (*i == start) { // if the current word is the start word, the ladder is written to the output file and the loop is exited
                    while (!newLadder.empty()) {
                        outFS << newLadder.top() << " ";
                        newLadder.pop();
                    }
                    break;
                } else { // otherwise the new ladder is added to ladderQueue and the current word is removed from the dict
                    ladderQueue.push(newLadder);
                    i = dict.erase(i);
                    --i;
                }
            }
        }
        if (*i == start) { // if current word is equal to start worrd
            break; // exit loop
        }
        ladderQueue.pop(); // pop off front ladder for the next iteration of the outer while loop
    }

    if (ladderQueue.empty()) { // checks if ladderQueue is empty
        outFS << "No Word Ladder Found.";
    } 
    outFS.close(); // close file
}

// Helper function to check the validity of a word by comparing it with words stored in the 'dict' list
bool WordLadder::checkValidity(const string & word) {
  list<string>::iterator i;
  for (i = dict.begin(); i != dict.end(); ++i) { // iterate over dict list
    if (word == *i) { // if current word is equal to the word pointed to by i
      return true;
    }
  }
  return false; // word is not valid
}

// Helper function to calculate the number of differing letters between two words
int WordLadder::findLetterDifference(const string & word1, const string & word2) {
  if (word1 == word2) { // checks if words are same
    return 0;
  } else {
      int difference = 0; // keep count of number of differing letters
      for (unsigned i = 0; i < 5; ++i) { // iterate over characters of the words
      if (word1.at(i) != word2.at(i)) { // compare each letter by index
        difference = difference + 1; // increment difference by 1
      }
    }
    return difference;
  }
}
