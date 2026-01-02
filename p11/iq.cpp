// Team 13
// Ho Ian Zam and Tamera Onitsha
// CSC 255 Data Structures
// IQ
// Nov.8.2023
// Makes an int Queue

//******************************************************************************
// connects this file with the header

#include "iq.h"
#include <iostream>
using namespace std;

//******************************************************************************
// constructor
// The section below was written by Ian

iQ::iQ(int n) {
    theList = new cIntList(n);
}

//******************************************************************************
// destructor
// The section below was written by Ian

iQ::~iQ() {
    if (theList) {
        delete theList;
    }
}

//******************************************************************************
// adds value to the end of the list
// done by making the value after last the new last and adding value there
// The section below was written by Ian

bool iQ::enq(int value) {
    return theList->add(value);
}

//******************************************************************************
// deletes at first value
// The section below was written by Ian

bool iQ::deq(int &value) {   
    return theList->deleteFirst(value);
}

//******************************************************************************
// clears the list
// The section below was written by Ian

void iQ::clear() {
    theList->clear();
}

//******************************************************************************
// returns number of entries on the list
// The section below was written by Ian

int iQ::count() const {
    return theList->count();
}

//******************************************************************************
// prints the list, one value per line
// The section below was written by Ian

void iQ::printIt() const {
    theList->printIt();
}

