#pragma once

#include <string>

using std::string;

class Node {

  friend class Tree;

private:
  string small;
  string large;
  int numData;

  Node* parent;
  Node* left;
  Node* middle;
  Node* right;

public:
  Node();
  explicit Node(const string& key);

};
