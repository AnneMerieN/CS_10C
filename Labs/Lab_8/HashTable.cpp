#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>


#include "HashTable.h"
#include "WordEntry.h"

using namespace std;

// Constructor
HashTable::HashTable (int s) {
  size = s;
  hashTable = new list<WordEntry>[size];
}

// Copy Constructor //
HashTable::HashTable(const HashTable &other) {
    size = other.size;
    hashTable = new list<WordEntry>[size];
    for (int i = 0; i < size; ++i) {
        hashTable[i] = other.hashTable[i];
    }
}

// Copy Assignment Operator //
HashTable &HashTable::operator=(const HashTable &other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    delete[] hashTable; // Free the existing resource

    size = other.size;
    hashTable = new list<WordEntry>[size];
    for (int i = 0; i < size; ++i) {
        hashTable[i] = other.hashTable[i];
    }

    return *this;
}

// Destructor //
HashTable::~HashTable() {
    delete[] hashTable;
}

int HashTable::computeHash(const string &s) const {
  return s.size() % size;
}


void HashTable::put(const string &s, int score) {
  if(contains(s)) { // checks if hash table already contains 's'
    for(list<WordEntry>::iterator it=hashTable[computeHash(s)].begin(); it != hashTable[computeHash(s)].end(); ++it) { // iterates over the list of 'WordEntry' objects in the bucker where the string 's' should be located
	 		if(it->getWord() == s) { // checks if current object matches the string 's'
	 			it->addNewAppearance(score); // call function to update the score associated with this word
	 		}
	 	}
	 }
	 else { // does not contain string 's'
	 	WordEntry newEntry(s, score);
	 	hashTable[computeHash(s)].push_front(newEntry); // inserts the new object at the front of the list in the appropriate bucket adding the new word and its score to the hash table
	 }
  }

// Function to retrieve the average score for the given string 's'
double HashTable::getAverage(const string &s) const {
  if(contains(s)) {
		for(list<WordEntry>::iterator it=hashTable[computeHash(s)].begin(); it != hashTable[computeHash(s)].end(); ++it) {
			if(it->getWord() == s) {
				return it->getAverage();
			}
		}
	}
  return 2.0;
}

// Function to check if the hash table contains the given string 's'
bool HashTable::contains(const string &s) const {
  for(list<WordEntry>::iterator it=hashTable[computeHash(s)].begin(); it != hashTable[computeHash(s)].end(); ++it) {
		if(it->getWord() == s) {
			return true;
		}
	}
  return false;
}

