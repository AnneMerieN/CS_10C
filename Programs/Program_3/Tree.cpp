#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;


// Initialize an empty tree with a root set to null
Tree::Tree() {
  root = NULL;
}

// Destructor
Tree::~Tree() {
  deleteSubtree(root);
}

// Helper function to recursively delete a subtree rooted at the given node
void Tree::deleteSubtree(Node* node) {
    if (node != nullptr) {
        // Recursively delete the left subtree
        deleteSubtree(node->left);
        // Recursively delete the middle subtree
        deleteSubtree(node->middle);
        // Recursively delete the right subtree
        deleteSubtree(node->right);
        // Delete the current node
        delete node;
    }
}

// Function to check if a node has children (leaf or internal)
bool Tree::noChildren( Node* node ) const {
  return(node->left == nullptr && node->middle == nullptr && node->right == nullptr);

}

// Inserts a word into the tree, starting from the root
void Tree::insert( const string& word ) {
  if ( root == nullptr ) {
    root = new Node( word );
  } else {
    insert(root, word );
  }
}

// Recursive insert helper function
void Tree::insert( Node* curr, const string& word ) {
  // If the current node is a leaf node, insert the word here
  if (noChildren(curr)) {
    addData(curr, word);
  } else {
    // Find the appropriate child to descend to
    if (curr->numData == 1) {
      if (word < curr->small) {
        insert(curr->left, word);
      } else {
        insert(curr->middle, word);
      }
    } else { // curr->numData == 2
      if (word < curr->small) {
        insert(curr->left, word);
      } else if (word > curr->large) {
        insert(curr->right, word);
      } else {
        insert(curr->middle, word);
      }
    }

    // Fix any overflow issues if necessary
    if (curr->numData == 2) {
      split(curr);
    }
  }
}

// Splits a node if it has more than the allowed number of keys
void Tree::split(Node* node) {
    if (node->parent == nullptr) {
        // If the node is the root, create a new root
        Node* newRoot = new Node();
        newRoot->small = node->large;

        Node* newLeft = new Node();
        newLeft->small = node->small;
        newLeft->left = node->left;
        newLeft->right = node->middle;

        if (node->left != nullptr) {
            node->left->parent = newLeft;
        }
        if (node->middle != nullptr) {
            node->middle->parent = newLeft;
        }

        node->small = "";
        node->large = "";
        node->left = nullptr;
        node->middle = nullptr;

        node->parent = newRoot;
        newLeft->parent = newRoot;

        newRoot->left = newLeft;
        root = newRoot;
    } else {
        // If the node has a parent, split and redistribute keys
        Node* parent = node->parent;
        Node* newChild = new Node();

        if (node->large < parent->small) {
            newChild->small = parent->small;
            parent->small = node->large;
            newChild->left = node->right;
            node->right = nullptr;
        } else if (node->large > parent->large) {
            newChild->small = parent->large;
            parent->large = node->large;
            newChild->left = parent->right;
            parent->right = nullptr;
        } else {
            newChild->small = node->large;
            newChild->left = node->right;
            node->right = nullptr;
        }

        newChild->parent = parent;

        if (parent->left == node) {
            parent->right = parent->middle;
            parent->middle = newChild;
        } else if (parent->middle == node) {
            parent->right = parent->middle;
            parent->middle = newChild;
        } else { // parent->right == node
            parent->right = newChild;
        }

        // Update parent pointers of the new child's left subtree
        if (newChild->left != nullptr) {
            newChild->left->parent = newChild;
        }

        node->large = "";
        fix(parent); // Fix any underflow issues in the parent node
    }
}

// Adds data to a node with one key, placing the new word in the correct position
void Tree::addData( Node* addHere, const string& word ) {
  if (addHere->numData == 1) {
    // There is only one key, so we add the second key in the correct order
    if (word < addHere->small) {
      addHere->large = addHere->small;
      addHere->small = word;
    } else {
      addHere->large = word;
    }
    addHere->numData = 2;
  } else {
    throw runtime_error("Node already has two keys, splitting required");
  }
}

// Pre-order traversal of the tree
void Tree::preOrder() const {
  preOrder( root );
  cout << endl;
}

// Recursive helper function for preorder traversal
void Tree::preOrder( const Node* curr ) const {
  if (curr != nullptr) {
        cout << curr->small << ", ";
        preOrder(curr->left);
        if (curr->numData == 2) {
            cout << curr->large << ", ";
            preOrder(curr->middle);
        }
        preOrder(curr->right);
    }
}

// In-order traversal of tree
void Tree::inOrder() const {
  inOrder( root );
  cout << endl;
}

// Recursive helper fucntion for in-order traversal
void Tree::inOrder(const Node* curr) const {
   if (curr != nullptr) {
        inOrder(curr->left);
        cout << curr->small << ", ";
        inOrder(curr->middle);
        if (curr->numData == 2) {
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}

void Tree::postOrder() const {
  postOrder( root );
  cout << endl;
}

void Tree::postOrder(const Node* curr) const {
  if (curr != nullptr) {
        postOrder(curr->left);
        postOrder(curr->middle);
        postOrder(curr->right);
        cout << curr->small << ", ";
        if (curr->numData == 2) {
            cout << curr->large << ", ";
        }
    }

}

// Function to remove a specified word from tree
void Tree::remove(const string& word) {
  // Nothing to do in an empty tree, just return
  if ( !root )
    return;

  Node* nodeToRemove = search(word); // Find the node containing the key to remove
  if (nodeToRemove == nullptr) {
    return; // Key not found, nothing to remove
  }

  // Case 1: Node to remove is a leaf node
  if (noChildren(nodeToRemove)) {
    deleteNodeLeaf(nodeToRemove);
  }
  // Case 2: Node to remove has one child
  else if (hasOneChild(nodeToRemove)) {
    deleteNodeOneChild(nodeToRemove);
  }
  // Case 3: Node to remove has two children
  else {
    Node* successor = findSuccessor(nodeToRemove); // Find the successor node
    swapData(nodeToRemove, successor);             // Swap data with the successor
    // Now, remove the successor node (which will be a leaf node or a node with one child)
    if (noChildren(successor)) {
      deleteNodeLeaf(successor);
    } else {
      deleteNodeOneChild(successor);
    }
  }
}

// Deletes a leaf node
void Tree::deleteNodeLeaf(Node* node) {
  Node* parent = node->parent;
  if (parent == nullptr) {
    delete root;
    root = nullptr;
    return;
  }
  // Remove the leaf node from its parent
  if (parent->left == node) {
    delete node;
    parent->left = nullptr;
  } else if (parent->middle == node) {
    delete node;
    parent->middle = nullptr;
  } else {
    delete node;
    parent->right = nullptr;
  }

  // Fix any underflow issues in the tree
  fix(parent);
}

// Delete a node with one child
void Tree::deleteNodeOneChild(Node* node) {
  Node* parent = node->parent;
  Node* child = (node->left != nullptr) ? node->left : node->middle;
  if (parent == nullptr) {
    root = child;
    child->parent = nullptr;
    delete node;
    return;
  }

  // Attach the child node to the parent
  if (parent->left == node) {
    parent->left = child;
  } else if (parent->middle == node) {
    parent->middle = child;
  } else {
    parent->right = child;
  }
  child->parent = parent;

  delete node;

  // Fix any underflow issues in the tree
  fix(parent);
}

// Find successor node for a given node
Node* Tree::findSuccessor(Node* node) {
  Node* curr = node->middle;
  while (curr->left != nullptr) {
    curr = curr->left;
  }
  return curr;
}

// Swaps data between two nodes
void Tree::swapData(Node* node1, Node* node2) {
  // Swap data between node1 and node2
  swap(node1->small, node2->small);
  swap(node1->large, node2->large);
}

// Checks if a node has exactly one child
bool Tree::hasOneChild(Node* node) const {
  return ((node->left != nullptr && node->middle == nullptr && node->right == nullptr) ||
          (node->left == nullptr && node->middle != nullptr && node->right == nullptr) ||
          (node->left == nullptr && node->middle == nullptr && node->right != nullptr));
}

// Checks if a node has exactly two children
bool Tree::hasTwoChildren(Node* node) const {
  return (node->left != nullptr && node->middle != nullptr && node->right == nullptr);
}


// Fixes underflow issues by redistributing keys or merging nodes
void Tree::fix(Node* emptyNode) {
  // If the node is the root and it's empty, set the root to nullptr
  if (emptyNode == root) {
    if (root->numData == 0) {
      root = nullptr;
    }
    return;
  }

  Node* parent = emptyNode->parent;

  // Try to redistribute keys from siblings
  if (parent->left == emptyNode) {
    Node* sibling = parent->middle;
    if (sibling->numData == 2) {
      // Redistribution: move one key from sibling to emptyNode
      emptyNode->small = parent->small;
      parent->small = sibling->small;
      sibling->small = sibling->large;
      sibling->large = "";
      sibling->numData = 1;
      emptyNode->numData = 1;
      return;
    }
  } else if (parent->middle == emptyNode) {
    Node* sibling;
    if (parent->left->numData == 2) {
      sibling = parent->left;
      // Redistribution: move one key from sibling to emptyNode
      emptyNode->small = parent->small;
      parent->small = sibling->large;
      sibling->large = "";
      sibling->numData = 1;
      emptyNode->numData = 1;
      return;
    } else if (parent->right != nullptr && parent->right->numData == 2) {
      sibling = parent->right;
      // Redistribution: move one key from sibling to emptyNode
      emptyNode->small = parent->large;
      parent->large = sibling->small;
      sibling->small = sibling->large;
      sibling->large = "";
      sibling->numData = 1;
      emptyNode->numData = 1;
      return;
    }
  } else if (parent->right == emptyNode) {
    Node* sibling = parent->middle;
    if (sibling->numData == 2) {
      // Redistribution: move one key from sibling to emptyNode
      emptyNode->small = parent->large;
      parent->large = sibling->large;
      sibling->large = "";
      sibling->numData = 1;
      emptyNode->numData = 1;
      return;
    }
  }

  // If redistribution is not possible, perform a merge
  if (parent->left == emptyNode) {
    Node* sibling = parent->middle;
    emptyNode->small = parent->small;
    emptyNode->middle = sibling->left;
    emptyNode->large = sibling->small;
    emptyNode->right = sibling->middle;
    emptyNode->numData = 2;
    delete sibling;
    parent->middle = nullptr;
    parent->small = parent->large;
    parent->large = "";
    parent->numData = 1;
  } else if (parent->middle == emptyNode) {
    Node* sibling = parent->left;
    sibling->large = parent->small;
    sibling->right = emptyNode->middle;
    sibling->numData = 2;
    delete emptyNode;
    parent->middle = nullptr;
    parent->small = parent->large;
    parent->large = "";
    parent->numData = 1;
  } else if (parent->right == emptyNode) {
    Node* sibling = parent->middle;
    sibling->large = parent->large;
    sibling->right = emptyNode->middle;
    sibling->numData = 2;
    delete emptyNode;
    parent->right = nullptr;
    parent->large = "";
    parent->numData = 1;
  }

  // If the parent becomes empty after the merge, fix the parent recursively
  if (parent->numData == 0) {
    fix(parent);
  }
}

// Checks if a sibling node has two children
bool Tree::hasTwoChildSibling(Node* sib) const {
  if (sib == nullptr) {
    return false;
  }
  return(sib->left != nullptr && sib->middle != nullptr);
}

Node* Tree::search(const string& word) {
  return search(root, word);
}

// Searches for a node containing the given word
Node* Tree::search( Node* curr, const string& word ) {
  if (curr == nullptr) {
    return nullptr;
  }

  if (word == curr->small || (curr->numData == 2 && word == curr->large)) {
    return curr;
  }

  if (word < curr->small) {
    return search(curr->left, word);
  } else if (curr->numData == 1 || (curr->numData == 2 && word < curr->large)) {
    return search(curr->middle, word);
  } else {
    return search(curr->right, word);
  }
}

