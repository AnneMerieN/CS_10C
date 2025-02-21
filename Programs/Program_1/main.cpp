#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

// Function to create a new node with given payload
Node* newNode(string payload) {
    Node* temp = new Node; // allocate memory for a new node
    temp->next = temp; // initialize the next pointer to itself (circular list)
    temp->payload = payload; // set the payload of the node
    return temp;
    
}

// function to load the initial game state (circular linked list of players)
Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;
   
    for (int i = 0; i < n; ++i) { // iterate through the vector of names
        name = names.at(i); // get the name at index i
        if (head == nullptr) { // if head is null initialize head specically
            head = newNode(name); // initialize head specially
            prev = head;
        } else { // otherwise, add a new node with the name after the previous node
            prev->next = newNode(name);
            prev = prev->next;
        }
    }
   // make the list circular by connecting the last node to the head
    if (prev != nullptr) {
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
            prev = curr;
            curr = curr->next;
        }

         prev->next = curr->next; // delete kth node
         delete curr;
         curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

