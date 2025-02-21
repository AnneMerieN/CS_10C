#include <iostream>
#include "Heap.h"

bool testPassed() {
  Heap heap;
  if(heap.highest() != nullptr){
    std::cout << "Heap is not empty where it should be empty." << std::endl;
    return false;
  }
  heap.dequeue();
  if(heap.highest() != nullptr){
    std::cout << "Heap is not empty where it should be empty." << std::endl;
    return false;
  }
  return true;
}

int main() {
  return testPassed()?0:1;
}
