#include <iostream>
#include <string>
using namespace std;
#include "IntList.h"

int main() {
    IntList list;
    cout << "Construct an IntList list" << endl;

    cout << "List is empty: " << list.empty() << endl;

    cout << "push_front 4, push_front 5, push_front 6" << endl;
    list.push_front(6);
    list.push_front(5);
    list.push_front(4);
    cout << "Printed list: " << list << endl;

    cout << "List is empty: " << list.empty() << endl;

    cout << "push_back 7, push_back 8, push_back 9, " << endl;
    list.push_back(9);
    list.push_back(8);
    list.push_back(7);
    cout << "Printed list: " << list << endl;

    cout << "pop_front" << endl;
    list.pop_front();
    cout << "print list: " << list << endl;
    cout << "pop_back" << endl;
    list.pop_back();
    cout << "print list: " << list << endl;
    cout << "print reverse: ";
    list.printReverse();
    
}