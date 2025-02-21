#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	HashTable(int size);
	bool contains(const string& word) const;
	double getAverage(const string& word) const;
	void put(const string& word , int score);
 
 private:
	int computeHash(const string &) const;
};
