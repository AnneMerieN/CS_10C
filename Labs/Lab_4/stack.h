#ifndef STACK_H
#define STACK_H

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
class stack {
    
    private:
        T data[MAX_SIZE]; // initialize array 'data' with 'MAX_SIZE'
        int size;

    public:
        stack() {
            size = 0; // initialize stack empty
        }

        // Function to add a new element to the top of the stack
        void push(T val) {
            if (size == MAX_SIZE) { // check if stack is full
                throw overflow_error("Called push on full stack.");
            }
            for(int i = size; i > 0; --i) { // shift all existing elements up by 1 in the array to make room to make space for the new element
                data[i] = data[i-1];
            }
            data[0] = val;
            size = size + 1;
        }

        // Function to remove the top element from the stack
        void pop() {
            if (empty()) { // check if empty
                throw out_of_range("Called pop on empty stack.");
            }
            for (int i = 0; i < size; ++i) { // shifts all elements one position down in the array
                data[i] = data[i+1];
            }
            size = size - 1; // updates size of stack to account for removal of element
        }

        // Function to remove the last two elements in stack
        void pop_two() {
            if(empty()) {
                throw out_of_range("Called popo_two on empty stack.");
            } else if (size == 1) {
                throw out_of_range("Called pop_two on a stack of size 1.");
            }
            size = size - 2;
        }

        // Function to return top item on stack
        T top() const {
            if (empty()) {
                throw overflow_error("Called top on empty stack.");
            } else{
            
                return data[0];
            } // return first element
        }

        // Function to check if stack is empty
        bool empty() const {
            return (size == 0);
        }

        
};

#endif