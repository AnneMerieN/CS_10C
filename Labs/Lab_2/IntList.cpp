#include <iostream>
#include "IntList.h"
using namespace std;

// Default Constructor
IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    dummyHead->next = dummyTail;
    dummyHead->prev = nullptr;
    dummyTail->next = nullptr;
    dummyTail->prev = dummyHead;
}

// Destructor
IntList::~IntList() {
    IntNode* newNode = dummyHead; // newNode points to dummyHead
    while(newNode != nullptr) { // true until there are no more nodes in the list
        IntNode* temp = newNode; // create a temp node that points to the currentNode to store the pointer of the node being deleted
        newNode = newNode->next; // move to the next node
        delete temp; // deallocates the memory pointed to by temp
    }
}

// Function to add a node to the front of a linked list
void IntList::push_front(int value) {
    IntNode* newNode = new IntNode(value); // make a new node and initialize it with value
    newNode->prev = dummyHead; // newNode's prev pointer points to dummyHead
    newNode->next = dummyHead->next; // newNode's next pointer points to the first real node in the list
    if (dummyHead->next != nullptr) { // as long as the node after dummyHead (the first real node) isn't nullptr
        dummyHead->next->prev = newNode; // the prev pointer of the node after dummy head points to the new node
    }
    dummyHead->next = newNode;
}
// Function to remove the first element (the one after the dummy head)
void IntList::pop_front() {
    if (dummyHead->next == dummyTail) { // checks if list is empty (only contains dummy nodes)
        return;
    } else {
        IntNode* temp = dummyTail->prev; // 'temp' points to the node before dummyTail or the last node in the list
        dummyTail->prev = temp->prev; // 'prev' pointer of 'dummyTail' points to the node before 'temp'
        temp->prev->next = dummyTail; // the 'next' pointer of the 'prev' node before temp points to dummyTail
        delete temp; // deletes the node pointed to by 'temp'
    }
}

// function to insert a new node at the end of a linked list
void IntList::push_back(int value) {
    IntNode* newNode = new IntNode(value);
    IntNode* prevNode = dummyTail->prev; // prevNode points to the real last node in the list
    prevNode->next = newNode; // the next pointer of the last node points to the new node
    newNode->next = dummyTail; // newNode is now the last real node in the list and it points to dummyTail
    dummyTail->prev = newNode; // make prev pointer of dummyTail point to the new Node
    newNode->prev = prevNode; // make the prev pointer of the newNode point to prevNode which was the old last node
}

// function to remove the last node in a list
void IntList::pop_back() {
    if (empty()) { // checks if list is empty
        return;
    }
    else {
        IntNode* temp = dummyTail->prev; // temp points to the last actual node in the list
        dummyTail->prev = temp->prev; // the last actual node points to the node before temp so that temp is unlinked from the list
        temp->prev->next = dummyTail; // next pointer of the node before temp points to dummyTail
        delete temp; // deallocate memory occupied by temp
    }
}

// function to check if list is empty
bool IntList::empty() const {
    if (dummyHead->next == dummyTail) { // if node after dummy head points to dummyTail, the list is empty
        return true;
    }
    return false;
}
ostream & operator<<(ostream &out, const IntList &rhs) {
    IntNode* currNode = rhs.dummyHead->next; // currNode points to the first actual node in the list
    while (currNode != rhs.dummyTail) { // iterates through the list while currNode does not point to dummyTail
        if (currNode == rhs.dummyTail->prev) { // checks if currNode is the node just ebfore the dummy tail node
            out << currNode->data; // if currNode is the last node before the dummyTail node, print its data to the output stream
        }
        else { // if not the last node before the dummy tail node
            out << currNode->data << " "; // print out the data followed by a space
        }
        currNode = currNode->next; // move to the next node
    }
    return out;
}

// function to print the linked list in reverse
void IntList::printReverse() const {
    if (empty()) {
        return;
    }

    // for loop that iterates backwards through the list starting from the end until newNode reaches dummyHead
    for (IntNode* newNode = dummyTail->prev; newNode != dummyHead; newNode = newNode->prev) {
        if (newNode->prev == dummyHead) { // checks if the node before newNode is dummyHead (if true then newNode is the second-to-last node in the list)
            cout << newNode->data;
        }
        else { // otherwise we print the node's data followed by a space
            cout << newNode->data << " ";
        }
    }
}

// function that iterates through the linked list from the beginning and prints the data of the nodes
void IntList::printAll() const {
    for(IntNode* newNode = dummyHead; newNode != nullptr; newNode=newNode->next) {
        cout << newNode->data << " ";
    }
}