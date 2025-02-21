#pragma once

#include "Node.h"

using std::string;

class Tree {
private:
  Node* root;

public:
  Tree();
  ~Tree();
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;
  
  void insert( const string & );
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove( const string & );
  Node* search( const string & );

private:

  bool noChildren(Node* curr) const;
  void insert(Node* curr, const string& word);
  void addData(Node* addHere, const string& word);
  void preOrder(const Node* curr) const;
  void inOrder(const Node* curr) const;
  void postOrder(const Node* curr) const;
  void fix(Node* emptyNode);
  bool hasTwoChildSibling(Node* sibling) const;
  Node* search(Node* curr, const string& word);
  void deleteNodeLeaf(Node* node);
  void deleteNodeOneChild(Node* node);
  Node* findSuccessor(Node* node);
  void swapData(Node* node1, Node* node2);
  bool hasOneChild(Node* node) const;
  bool hasTwoChildren(Node* node) const;
  void deleteSubtree(Node* node);
  void split(Node* node);

};
