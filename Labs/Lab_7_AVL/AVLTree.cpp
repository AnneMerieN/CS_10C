#include "AVLTree.h" 

using namespace std;


// Constructor
AVLTree::AVLTree() {
    root = 0;
}

// Function to insert a string in the AVL tree
void AVLTree::insert(const string &str) {
    Node *newNode = new Node(str); 
    insert(root,newNode);
} 

// Recursive insert helper function
void AVLTree::insert(Node *curr, Node *newNode) {
   if (!root) {
      root = newNode; 
      root->parent = 0;
      return;
   }
   curr = root;
   while (curr) { 
      if (newNode->data == curr->data) {
          curr->count++; 
          curr = 0;
      } 
      else if (newNode->data < curr->data) {
         if (curr->left == 0) {
            curr->left = newNode;
            newNode->parent = curr;
            curr = 0;
         }
         else
            curr = curr->left;
      }
      else {
         if (curr->right == 0) {
            curr->right = newNode;
            newNode->parent = curr;
            curr = 0;
         }
         else
            curr = curr->right;
      }
   }

  newNode = newNode->parent;
  while (newNode) { 
      rotate(newNode); 
      newNode = newNode->parent; 
      
  }
}

// Function to print the balance factors of all nodes in the AVL tree
void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root); 
    cout << endl;
} 

// Recursive helper function to print the balance factors of nodes in the AVL tree
void AVLTree::printBalanceFactors(Node *curr) const {
    if(curr) {
        printBalanceFactors(curr->left); 
        cout << curr->data << "(" << balanceFactor(curr) << "), "; 
        printBalanceFactors(curr->right); 
    }
}

// Function to calculate the balance factor of a node
int AVLTree::balanceFactor(Node *curr) const {
    return height(curr->left) - height(curr->right);
}

// Function to calculate the height of a node
int AVLTree::height(Node *curr) const { 
    if (curr){
        int finalHeight = 0;
        height(0,finalHeight,curr); 
        return finalHeight - 1;
    }
    return -1;
} 

// Function to calculate the height of a node
void AVLTree::height(int heightCounter, int &finalHeight, Node *curr) const {
    if(curr) {
        heightCounter++; 
        if(heightCounter > finalHeight){
            finalHeight = heightCounter;
        }
        //recursively traverse tree
        height(heightCounter,finalHeight,curr->left);
        height(heightCounter,finalHeight,curr->right); 
    }
}

// Function to perform rotitions for balancing the AVL tree
void AVLTree::rotate(Node *curr) { 
    if(balanceFactor(curr) == 2) {
        if(balanceFactor(curr->left) == -1) {
            rotateLeft(curr->left);
        } 
        rotateRight(curr);
    }
    else if(balanceFactor(curr) == -2) {
        if(balanceFactor(curr->right) == 1) { 
            rotateRight(curr->right); 
        } 
        rotateLeft(curr);
    }
}

// Function to perform a right rotation around a node
void AVLTree::rotateRight(Node *curr) {
    Node *temp = curr->left->right;
    if(curr->parent) {
        replaceChild(curr->parent,curr,curr->left);
    } 
    else {
        root = curr->left; 
        root->parent = 0;
    }
    setChild(curr->left,"right",curr); 
    setChild(curr,"left",temp);
}  

// Function to perform a left rotation around a node
void AVLTree::rotateLeft(Node *curr) {
    Node *temp = curr->right->left;
    if(curr->parent) { 
        replaceChild(curr->parent,curr,curr->right);
    } 
    else {
        root = curr->right; 
        root->parent = 0;
    }
    setChild(curr->right,"left",curr); 
    setChild(curr,"right",temp);
} 


// Function to set a specified child of a parent node
void AVLTree::setChild(Node *parent, string whichChild, Node *child) {
    if(whichChild == "left") {
        parent->left = child;
    } 
    else {
        parent->right = child;
    } 
    if(child) {
        child->parent = parent;
    }
}

// Function to replace a specified child of a parent node
void AVLTree::replaceChild(Node *parent, Node *curr,Node *newChild) {
    if(parent->left == curr) {
        setChild(parent,"left",newChild);
    } 
    else if(parent->right == curr) {
        setChild(parent,"right",newChild);
    }
}

// Function to visualize the AVL tree and save it to a file
void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

// Recursive helper function to visualize the AVL tree
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}