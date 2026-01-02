// Team 13
// Ho Ian Zam and Tamera Onitsha
// CSC 255 Data Structures
// IQ
// Nov.8.2023

#ifndef __IQ_H
#define __IQ_H

#include <string>
#include "cil.h"

// test with
// g++ cil.cpp iq.cpp iqm.cpp -o iq
// ./iq > iqOutput.txt
//******************************************************************************

class iQ {
    private:
        cIntList *theList;
        int n; // tracks capacity of list

    public:
        // constructor that sets the listCapacity
        // and sets listCount, first, and last to 0
        iQ(int n = 100); 
        ~iQ(); // destructor

        // MODIFIERS
        bool enq(int value); // adds value to the end of an array
        bool deq(int &value); // deletes first index
        void clear(); // clears list

        // NON-MODIFIERS
        int count() const; // returns number of entriesx
        void printIt() const; // prints list one line at a time
};

#endif