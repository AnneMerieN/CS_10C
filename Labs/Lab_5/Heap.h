#pragma once
#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE]; // Notice this is an array of PrintJob pointers
  int numItems;  // current number of items in heap

public:
  /* Initializes an empty heap.*/
  Heap();
  
  ~Heap();
  Heap(const Heap& other);
  Heap& operator=(const Heap& other);

  /* Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void enqueue(PrintJob* job);

  /* Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void dequeue();

  /* Returns the node with highest priority.*/
  PrintJob* highest();

  /* Prints the PrintJob with highest priority in the following format:
     Priority: priority, Job Number: jobNum, Number of Pages: numPages
     (Add a new line at the end.) */
  void print();

private:
  /* This function is called by dequeue function
     to move the new root down the heap to the 
     appropriate location. */
  void trickleDown(int);
  
  void trickleUp(int);
  
  
};
