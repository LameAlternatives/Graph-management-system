// Team 13
// Ho Ian Zam and Tamaranlayif Onitsha
// CSC 255 Data Structures
// P8.h
// Oct.25.2023

#ifndef __P8_H
#define __P8_H

#include <string>
#include <iostream>

// run with
// g++ -O2 p8.cpp p8m.cpp -o p8
// ./p8 10 > p8output.txt
// ./p8 30 >> p8output.txt
// ./p8 40000 >> p8output.txt
//******************************************************************************

class intList {
    private:
        int *a; // points to an integer list
        int listCapacity; // the capacity of the whole list
        int listCount; // the number of entries in the list
        int heapSize; // tracks the size of the heap

        // private methods
        void buildHeap(); // build a heap by heapifying the parents of leaves
        void swap(int &x, int &y); // swaps values on a list
        void heapify(int index); // performs heap heapify operation
        int left(int index) const; // returns the left child of the given index
        int right(int index) const; // returns right child of the given index

    public:
        intList(int listCapacity = 100); // constructor
        ~intList(); // destructor

        // MODIFIERS
        bool insert(int key); // inserts integer to the front of an array
        bool add(int key); // adds integer to the end of a list
        bool insertAt(int index, int key); // inserts integer at certain spot
        bool deleteAt(int index, int &key); // deletes integer at certain spot
        void clear(); // clears list
        void heapSort(); // sorts heap in ascending order

        // SORTERS
        void bubbleSort(); // perform quadratic bubbleSort
        void selectionSort(); // perform quadratic selectionSort
        void insertionSort(); // perform quadratic insertionSort
        bool isSorted() const; // check if list is sorted and report failure
        
        // NON-MODIFIERS
        void printIt(int n) const; // prints list one line at a time
        int getIndex(int key) const; // gets index of integer
        bool readAt(int index, int &key) const; // reads integer from line
        int count() const; // returns number of entries
        int capacity(); // return capacity of list
};

#endif