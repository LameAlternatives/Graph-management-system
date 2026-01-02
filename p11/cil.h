// Team 13
// Ho Ian Zam and Tamera Onitsha
// CSC 255 Data Structures
// P3 (IntList)
// Nov.8.2023

#ifndef __CIL_H
#define __CIL_H

#include <string>

// test with
// g++ cil.cpp iq.cpp iqm.cpp -o iq
// ./iq > iqOutput.txt
//******************************************************************************

class cIntList {
    private:
        int *a; // pointer to an array where values will be stored
        int listCapacity; // the capacity of the whole list
        int listCount; // the number of entries in the list
        int first; // tracks the first entry on the list
        int last; // tracks the last entry on the list

        // increments the passed value, wrapping its value to 0 if necessary
        void incVal(int &value); 
        // decrements the value, wrapping its value to capacity-1 if necessary
        void decVal(int &value); 

    public:
        // constructor that sets the listCapacity
        // and sets listCount, first, and last to 0
        cIntList(int capacity = 100); 
        ~cIntList(); // destructor

        // MODIFIERS
        bool add(int value); // adds value to the end of an array
        bool deleteFirst(int &value); // delete first value
        void clear(); // clears list

        // NON-MODIFIERS
        int count() const; // returns number of entries
        bool readAt(int index, int &key) const;
        void printIt() const;
};

#endif