#include <iostream>
#include "Heap.h"

using namespace std;


// Default constructor
Heap::Heap()
  : numItems(0) {}


// Destructor
Heap::~Heap() {
    // Deallocate individual PrintJob objects pointed to by arr
    for (int i = 0; i < numItems; ++i) {
        delete arr[i];
    }
}

// Copy constructor
Heap::Heap(const Heap& other) {
    // Copy numItems
    numItems = other.numItems;

    for (int i = 0; i < numItems; ++i) {
        arr[i] = new PrintJob(*other.arr[i]);
    }
}

// Copy assignment constructor
Heap& Heap::operator=(const Heap& other) {
    if (this != &other) {
        // Deallocate existing PrintJob objects
        for (int i = 0; i < numItems; ++i) {
            delete arr[i];
        }

        // Copy numItems
        numItems = other.numItems;

        // Deep copy of each PrintJob pointer in other.arr to arr
        for (int i = 0; i < numItems; ++i) {
            arr[i] = new PrintJob(*other.arr[i]);
        }
    }
    return *this;
}


// Function to add a job element at the back of the array
void Heap::enqueue(PrintJob* job) {
  if(numItems < MAX_HEAP_SIZE) {
    arr[numItems] = job;
    trickleUp(numItems);
    numItems++;
  }
}

// Function to remove element with highest priority
void Heap::dequeue() {
  if(numItems == 1) { // checks if the heap contains only one element
    arr[0] = 0; // if true, set first element in the array to 0
    numItems = 0; // update numItems to 0 since heap is now empty
    return;
  }
  if(numItems > 1) { // if more than one item in heap
    arr[0] = arr[numItems - 1]; // replace first element in array(root) with the last element in the array
    arr[numItems-1] = 0; // assign last element in array to 0 (effectively removed from heap)
    numItems--; // decrement size of heap
    trickleDown(0); // restore heap property starting from root
    
  }
}


// Function to return the highest priority element in the max heap
PrintJob* Heap::highest() {
	if(numItems == 0) { // check if heap is empty
        return 0; // return 0 (no elements in heap)
    }
    return arr[0]; // return root since root has highest priority
}


// Function to print the highest priority element, job number, and num of pages
void Heap::print() {
  if(numItems == 0) { // check if empty
    return;
  } else {
    cout << "Priority: " << highest()->getPriority();
    cout << ", Job Number: " << highest()->getJobNumber();
    cout << ", Number of Pages: " << highest()->getPages() << endl;

  }
  return;
}

// Helper function to maintain max heap property after removing the highest priority element
void Heap::trickleDown(int val) {
  for (int i = 0; i < numItems; ++i) { // iterate through heap
    if(arr[val]->getPriority() < arr[i]->getPriority()) { // compares priority of element at index val with the priority of the element at index i
      PrintJob* temp = arr[val]; // temp pointer to swap the two elements
      arr[val] = arr[i];
      arr[i] = temp;
    }
  }
}

// Function to ensure that the max heap property is maintained when a new element is added
void Heap::trickleUp(int val) {
  while (val >= 1 && arr[val]->getPriority() > arr[(val-2)/2]->getPriority()) { // as long we haven't reached root of heap and the priority of index val is greater than the priority of its parents element
    swap(arr[val], arr[(val-1)/2]); // swap element at index val and its parent
    val = (val-1)/2; // val index is updated to its parent index
  }
}


