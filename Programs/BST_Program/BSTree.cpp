#include <iostream>
#include <string>
#include "BSTree.h"
#include "Node.h"

// Default constructor - initializes root to 0
BSTree::BSTree() {
	root = 0;
}

// Function to check if string is in tree
Node* BSTree::search(const string &data, Node* curr) const {
    if(curr != 0) {
        if(data == curr->dataString) { // check if the root's string is equal to the given string
            return curr;
        }
        else {
            if(data < curr->dataString) { // if 'data' is less than root string, recursively serch the left subtree
                return search(data, curr->left);
            }
            else { // if 'data' is greater than root string, recursively search the right substring
                return search(data, curr->right);
            }
        }
    }
    else { // if string is not in tree
        return 0;
    }
}

// Function to print tree in inOrder notation (left-subtree, root, right-subtree)
void BSTree::inOrder(Node *curr) const {
	if(curr != 0) {
		inOrder(curr->left); // recurse over left sub-tree
		cout << curr->dataString << '(' << curr->count << "), "; // print root string
		inOrder(curr->right); // recurse over right sub-tree
	}
}

// Function to print tree in postOrder notation (left subtree, right subtree, root)
void BSTree::postOrder(Node *curr) const {
	if(curr != 0) {
		postOrder(curr->left); // recurse over left subtree
		postOrder(curr->right); // print root
		cout << curr->dataString << '(' << curr->count << "), "; // recurse over right sub-tree
	}
}

// Function to print tree in preOrder notation (root, left subtree, right subtree)
void BSTree::preOrder(Node *curr) const {
	if(curr != 0) {
		cout << curr->dataString << '(' << curr->count << "), "; // print root
		preOrder(curr->left); // recurse over left subtree
		preOrder(curr->right); // recurse over right subtree
	}
}

// Function to remove a specified string
void BSTree::remove(Node *data) {
	Node *curr = data; // pointer that keeps track of the current node
	Node *succ = 0; // pointer that keeps track of the successor node

	if(curr->left == 0 && curr->right == 0) { // checks if the current node has no left child and no right child (leaf node) and it can be deleted
		if(curr->parent != 0) { // if the current node has a parent
			if(curr->parent->left == curr) {
				curr->parent->left = 0; // update parent's left child to null
			}
			else {
				curr->parent->right = 0; // update parent's right child to null
			}
		}
		else { // if current node is the root node
			root = 0; // set root to null
		}
		delete curr; // current node is deleted
	}
	else if(curr->left != 0) { // if the current node has a left child but no right child
		succ = curr->left; // find successor node in the left sub tree
		while(succ->right != 0) { // traverse to the rightmost node in the left subtree
			succ = succ->right;
		}
		*curr = *succ; // copy successor to current node
		remove(succ); // recursively remove the successor node from its original position
	}
	else { // if the current node has a right child but no left child
		succ = curr->right; // set successor to the right child of curr
		while(succ->left != 0) { // traverse to the leftmost node in the right subtree
			succ = succ->left;
		}
		*curr = *succ;
		remove(succ);
	}
}

void BSTree::insert(const string &data) {
	Node *curr = root;
	if(search(data)) { // checks if the data to be inserted already exists in the tree
		curr = search(data, root);
		curr->count = curr->count + 1; // if search(data) returns true, increment count by 1
	}
	else { // if the data is not found in the tree, create a new node with the node constructor
		Node *newNode = new Node(data);
		if(root == 0) { // if the tree is empty
			root = newNode; // set root to the new node
		}
		else { // if the tree is not empty
			while(1) { // traverse the tree starting from the root
				if(data < curr->dataString) { // compares data to be inserted with the data stored in the current node
					if(curr->left == 0) { 
						curr->left = newNode;
						newNode->parent = curr;

						return;
					}
					else {
						curr = curr->left;
					}
				}
				else {
					if(curr->right == 0) {
						curr->right = newNode;
						newNode->parent = curr;
						return;
					}
				else {
					curr = curr->right;
				}
				}
			}
		}
	}
}

// Overloaded version of the 'search' function
bool BSTree::search(const string& data) const {
	return search(data, root); // call original search function with two parameters
}

// Function to find the largest element in the tree
string BSTree::largest() const {
	Node* curr = root; // initializes curr to the root
	if(curr == 0) { // if the tree is empty
		return ""; // return an empty string
	}
	else { // if not empty
		while(1) { // traverse through the tree
			if(curr->right == 0) { // check if current node has a right child
				return curr->dataString; // if true, return the current node
			}
			else { // if the current node has a right child
				curr = curr->right; // update curr to point to the right child
			}
		}
	}
}

// Function to find the smallest element in a tree
string BSTree::smallest() const {
    Node* curr = root;
    
    if(curr == 0) {
        return "";
    }
    else {
        while(1) {
            if(curr->left == 0) {
                return curr->dataString;
            }
            else {
                curr = curr->left;
            }
        }
    }
}

// Function to calculate height of the subtree at a particular node in the BST
int BSTree::height(const string &data) const {
    if(!search(data)) {
        return -1;
    }
    Node *curr = search(data, root);
    Node *currLeft = curr;
    Node *currRight = curr;
    int leftCnt = 0;
    int rightCnt = 0;
    
    if(curr->left != 0) {
        currLeft = currLeft->left;
        leftCnt++;
        leftCnt = leftCnt + height(currLeft->dataString);
    }
    if(curr->right != 0) {
        currRight = currRight->right;
        rightCnt++;
        rightCnt = rightCnt + height(currRight->dataString);
    }
    if(leftCnt >= rightCnt) {
        return leftCnt;
    }
    else {
        return rightCnt;
    }
}

// Function to remove a node from a BST
void BSTree::remove(const string &data) {
    if(search(data)) {
        Node *curr = search(data, root);
        
        if(curr->count > 1) {
            curr->count = curr->count - 1;
        }
        else {
            remove(curr);
        }
    }
}

void BSTree::preOrder() const {
	preOrder(root);
	cout << endl;
}

void BSTree::inOrder() const {
	inOrder(root);
	cout << endl;
}

void BSTree::postOrder() const {
	postOrder(root);
	cout << endl;
}