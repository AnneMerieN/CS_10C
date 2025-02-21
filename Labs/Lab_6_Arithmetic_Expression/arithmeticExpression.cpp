#include <iostream>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>
#include "arithmeticExpression.h"

using namespace std;

// Constructor to initialize the arithmetic expression with user input
arithmeticExpression::arithmeticExpression(const string &userInput) {
	root = 0;
	infixExpression = userInput;
}

// Function to print the infix expression starting from the root
void arithmeticExpression::infix() {
	infix(root);
}

// Helper functiont o recursively print the infix epxression
void arithmeticExpression::infix(TreeNode *curr) {
	if (curr == 0) {
		return;
	}
	if (priority(curr->data)) {
		cout << "(";
		infix(curr->left);
		cout << curr->data;
		infix(curr->right);
		cout << ")";
	}
	else {
		infix(curr->left);
		cout << curr->data;
		infix(curr->right);
	}
}

// Function to print the prefix expression starting from the root
void arithmeticExpression::prefix() {
	prefix(root);
}

// Helper function to recursively print the prefix expression
void arithmeticExpression::prefix(TreeNode *curr) {
	if (curr == 0) {
		return;
	}
	cout << curr->data;
	prefix(curr->left);
	prefix(curr->right);
}

// Function to print the postfix expression starting from the root
void arithmeticExpression::postfix() {
	postfix(root);
}

// Helper function to recursively print the postfix expression
void arithmeticExpression::postfix(TreeNode *curr) {
	if (curr == 0) {
		return;
	}

	postfix(curr->left);
	postfix(curr->right);
	cout << curr->data;
}

// Function to build the expression tree from infix expression
void arithmeticExpression::buildTree() {
	infixExpression = infix_to_postfix();
	stack <TreeNode*> s;

    // Iterate through each character in postfix expression
	for (unsigned i = 0; i < infixExpression.size(); ++i) {
		TreeNode *newNode = new TreeNode(infixExpression.at(i), 'a' + i);
		if (priority(infixExpression.at(i)) == 0) { // if true, push to stack
			s.push(newNode);
		}
		else if (priority(infixExpression.at(i)) > 0) { // if true, pop two nodes and create new sub-tree
			newNode->right = s.top();
			s.pop();
			newNode->left = s.top();
			s.pop();
			s.push(newNode);
			root = newNode; // update root
		}
	}
}

// Function to get the priority of an operator
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

// Method to convert infix expression to postfix expression
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        // If c is an operator
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}


// Function to visualize the expression tree and save it to a file
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();

    // Generate a JPG image from the dot file
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

// Helper function to recursively visualize the tree
void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *curr) {
    if (curr) {
    	outFS << curr->key << "[ label = " << "\"" << curr->data << "\"" << " ]" <<endl;
    if (curr->left) {
        outFS  << curr->key <<  "->" << curr->left->key << "[ label = " << "\"" << curr->left->data << "\"" << " ]" << endl;
        visualizeTree(outFS, curr->left);
    }
    if (curr->right) {
        outFS  << curr->key << " -> " << curr->right->key << "[ label =  " << "\"" << curr->right->data << "\"" << " ]" << endl;
        visualizeTree(outFS, curr->right);
    }
    outFS << endl;
    }
}