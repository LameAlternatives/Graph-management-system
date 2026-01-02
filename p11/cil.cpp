// Team 13
// Ho Ian Zam and Tamera Onitsha
// CSC 255 Data Structures
// P3 (IntList)
// Nov.8.2023
// Creates a circular Int list that wraps around itself

//******************************************************************************
// connects this file with the header

#include "cil.h"
#include <iostream>
using namespace std;

//******************************************************************************
// constructor
// The section below was written by Ian

cIntList::cIntList(int listCapacity) {
    listCount = 0;
    this->listCapacity = listCapacity;
    a = new int[listCapacity];
    // establish the first and last
    first = 0;
    last = 0;
}

//******************************************************************************
// destructor
// The section below was written by Ian

cIntList::~cIntList() {
    if (a){
        // destructs list
        delete [] a;
        a = NULL;
    }
}

//******************************************************************************
// increments the passed value, wrapping its value to 0 if necessary

void cIntList::incVal(int &value) {
    value = (value + 1) % listCapacity;

}

//******************************************************************************
// decrements the passed value, wrapping its value to capacity - 1 if necessary

void cIntList::decVal(int &value) {
    value = (value + listCapacity - 1) % listCapacity;
}

//******************************************************************************
// adds value to the end of the list
// done by making the value after last the new last and adding value there
// The section below was written by Ian

bool cIntList::add(int value) {
    bool re = false;

    // checks if list is functional
    if(listCount < listCapacity) {
        // if listCount is 0, then don't increment
        if (listCount) {
            incVal(last);
        }

        a[last] = value;
        re = true;
        listCount++;
    }

    return re;
}

//******************************************************************************
// deletes at first value
// The section below was written by Ian

bool cIntList::deleteFirst(int &value) {
    bool re = false;

    // checks if list exists
    if (listCount > 0) {
        value = a[first];

        // if first and last are in the same position
        if (first != last) {
            incVal(first);
        }

        re = true;
        listCount--;
    }

    return re;
}

//******************************************************************************
// clears the list
// The section below was written by Ian

void cIntList::clear() {
    // reset everything to zero
    listCount = 0;
    first = 0;
    last = 0;
}

//******************************************************************************
// returns number of entries on the list
// The section below was written by Ian

int cIntList::count() const {
    return listCount;
}

//******************************************************************************
// reads at a specific spot
// written by Ian

bool cIntList::readAt(int index, int &key) const {
    bool isRead = false;

    // checks if index is valid
    if (index < listCount && index >= 0) {
        key = a[index];
        isRead = true;
    }
    
    return isRead;
}

//******************************************************************************
// prints the list, one value per line
// The section below was written by Ian

void cIntList::printIt() const {
    for (int i = 0; i < listCount; i++) {
            // added to account for changed first and last
            int physical = (first + i) % listCapacity;
            cout <<  "Queue item " << i << " = " << a[physical] << endl;
    }
}