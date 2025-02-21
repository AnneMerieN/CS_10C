#include <iostream>
#include "Heap.h"

bool testPassed() {
  Heap heap;
  PrintJob* pj;
  heap.enqueue ( new PrintJob ( 1, 2, 3 ) );
  if ( ( pj = heap.highest ( ) ) == NULL ){
    std::cout << "Highest returns nothing when the heap is not empty." << std::endl;
    return false;
  }
  else if ( !(pj->getPriority ( ) == 1 && pj->getJobNumber ( ) == 2 && pj->getPages ( ) == 3) ){
    std::cout << "Highest item does not match with expected highest node in the heap after one enqueue operation." << std::endl;
    return false;
  }
  heap.enqueue ( new PrintJob ( 2, 3, 4 ) );
  heap.enqueue ( new PrintJob ( 3, 4, 5 ) );
  heap.enqueue ( new PrintJob ( 4, 5, 6 ) );
  heap.enqueue ( new PrintJob ( 5, 6, 7 ) );
  heap.enqueue ( new PrintJob ( 6, 7, 8 ) );
  heap.enqueue ( new PrintJob ( 7, 8, 9 ) );
  heap.enqueue ( new PrintJob ( 8, 9, 10 ) );
  heap.enqueue ( new PrintJob ( 9, 10, 11 ) );
  heap.enqueue ( new PrintJob ( 10, 11, 12 ) );
  heap.enqueue ( new PrintJob ( 11, 12, 13 ) );
  if ( ( pj = heap.highest ( ) ) == nullptr ){
    std::cout << "Highest returns nothing when the heap is not empty." << std::endl;
    return false;
  }
  else if ( !(pj->getPriority ( ) == 10 && pj->getJobNumber ( ) == 11 && pj->getPages ( ) == 12) ){
    std::cout << "Highest item does not match with expected highest node in the heap after multiple enqueue operations." << std::endl;
    return false;
  }
   
  for ( int i = 10; i > 0 ; i-- ) {
    if ( ( pj = heap.highest ( )  ) != nullptr ) {
      if ( !(pj->getPriority ( ) == i && pj->getJobNumber ( ) == i+1 && pj->getPages ( ) == i+2)){
	std::cout << "Highest item does not match with expected highest node in the heap after multiple dequeue operations." << std::endl;
        return false;
      }
      heap.dequeue ( );
    }
  }
  return true;
}

int main() {
  return testPassed()?0:1;
}
