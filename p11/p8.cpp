// Team 13
// Ho Ian Zam and Tamaranlayif Onitsha
// CSC 255 Data Structures
// P8
// Oct.25.2023
// implements heap sorting as well as quadratic sorting on a integer list

//******************************************************************************
// connects this file with the header

#include "p8.h"
using namespace std;

//******************************************************************************
// constructor
// written by Ian

intList::intList(int listCapacity) {
    listCount = 0;
    this->listCapacity = listCapacity;
    a = new int[listCapacity];
}

//******************************************************************************
// destructor
// written by Ian

intList::~intList() {
    if (a){
        delete [] a;
    }
}

//******************************************************************************
// sorts heap in ascending order
// by Ian

void intList::heapSort() {
    // form the heap
    buildHeap();

    // go through the heap and organize values in ascending order
    // heapify guarantees that the largest value will be on top
    // swapping it with the last value on the list ensures it's at the end
    // reducing the heap size ensures that the loop can't change it's position
    while (--heapSize) {
        swap(a[0], a[heapSize]);
        heapify(0);
    }
}

//******************************************************************************
// restructures an array into a heap
// by Ian

void intList::buildHeap() {
    // set size of superimposed heap
    heapSize = listCount;

    // find the parent of the last index
    // heapSize / 2 - 1 beacuse we need to find the parent of the last leaf
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        heapify(i);
    }
}

//******************************************************************************
// perform heap heapify operation, moves value down list until it 
// is at the appropriate location
// by Tamera

void intList::heapify(int index) {
    // create variables
    int lChild = left(index);
    int rChild = right(index);
    int largest = index;

    // if the left child is greater than the current largest variable
    if (lChild < heapSize && a[lChild] > a[largest]) {
        // the left child is the largest variable
        largest = lChild;
    } 

    // if the right child is greater than the current largest variable
    if (rChild < heapSize && a[rChild] > a[largest]) {
        // the right child is the largest variable
        largest = rChild;
    }

    // grab the largest and recurse if the largest isn't the original index
    if (largest != index) {     
        swap(a[index], a[largest]);
        heapify(largest);
      }
}

//******************************************************************************
// find the left child of the given index
// by Tamera

int intList::left(int index) const {
     return (2 * index + 1);
}

//******************************************************************************
// find the right child of the given index
// by Tamera

int intList::right(int index) const {
    return (2 * index + 2);
}

//******************************************************************************
// inserts integer at the beginning of the list
// written by Ian

bool intList::insert(int key) {
    bool isInserted = false;

    if (listCount < listCapacity) {
        listCount++;

        // moves list items to the right
        for (int i = listCount - 1; i > 0; i--) {
            a[i] = a[i - 1];
        }

        // add to the front of the list
        a[0] = key;
        isInserted = true;
    }

    return isInserted;
}

//******************************************************************************
// adds integer to the end of the list
// written by Ian

bool intList::add(int key) {
    bool isInserted = false;

    if (listCount < listCapacity) {
        listCount++;
        // add to the end of the list
        a[listCount - 1] = key;
        isInserted = true;
    }

    return isInserted;
}

//******************************************************************************
// inserts integer at a given index
// written by Ian

bool intList::insertAt(int index, int key) {
    bool isInserted = false;

    // checks if input is valid
    if (index >= 0 && index <= listCount && listCount < listCapacity) {
        listCount++;

        // moves list items to the right
        for (int i = listCount - 1; i > index; i--) {
            a[i] = a[i - 1];
        }

        a[index] = key;
        isInserted = true;
    }

    return isInserted;
}

//******************************************************************************
// delete integer at a given index
// written by Ian

bool intList::deleteAt(int index, int &key) {
    bool isDeleted = false;

    // checks if index is valid
    if (index < listCount && index >= 0) {
        key = a[index];

        // shifts list from right to left
        for (int i = index; i < listCount; i++) {
            a[i] = a[i + 1];
        }

        listCount --;
        isDeleted = true;
    }

    return isDeleted;
}

//******************************************************************************
// clears the list
// written by Ian

void intList::clear() {
    listCount = 0;
}

//******************************************************************************
// swaps values on a list
// written by Ian

void intList::swap(int &x, int &y) {
    // create a temporary value to help swap
    int tmp = x;
    x = y;
    y = tmp;
}

//******************************************************************************
// bubbles up values by swapping them with the next integer if it is larger
// written by Ian

void intList::bubbleSort() {
    // travel through list
    for (int i = 0; i < listCount; i++) {
        // during each trip, bubble up a value until it reaches the right spot
        // listCount - i to reduce the amount of time the end is looked at
        // this works because the end should be the first place to be sorted
        for (int j = 1; j < listCount - i; j++) {
            if (a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
            }
        }
    }
}

//******************************************************************************
// selects the smallest value and puts it near the front
// repeats the process until it is sorted
// written by Ian

void intList::selectionSort() {
    // travel through the list
    for (int i = 0; i < listCount - 1; i++) {
        // set minimum index
        int minIndex = i;

        // travel through the list to find the smallest value
        for (int j = i + 1; j < listCount; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        // put the value down on i
        swap(a[i], a[minIndex]);
    }
}

//******************************************************************************
// inserts a stored value to it's appropriate place
// written by Ian

void intList::insertionSort() {
    // goes through the whole list
    for (int i = 0; i < listCount - 1; i++) {
        // moves the metaphorical barrier that contains sorted data
        for (int j = i + 1; j > 0; j--) {
            // compares and swaps data when necessary
            if (a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);

            } else {
                break;
            }
        }
    }
}

//******************************************************************************
// checks if the list is sorted
// written by Ian

bool intList::isSorted() const {
    bool re = true;

    for (int i = 0; i < listCount - 1; i++) {
        // if the list isn't in ascending order, call false
        if (a[i] > a[i + 1]) {
            cout << "The value at index [" << i << "] isn't sorted!" << endl;
            re = false;
            break;
        }
    }

    return re;
}

//******************************************************************************
// prints out the list
// written by Ian

void intList::printIt(int n) const {
    cout << "printIt with list size: " << listCount << " capacity = " \
        << listCount << endl;

    // print the first n entries
    for (int i = 0; i < listCount && i < n; i++) {
        cout << "At pos " << i << " there is " << a[i] << endl;
    } 

    // if n < listCount print the last value on the list
    if (n < listCount) {
        cout << "At pos " << listCount - 1 << " there is " \
            << a[listCount - 1] << endl;

    }
}

//******************************************************************************
// returns the index where a integer is found
// written by Ian

int intList::getIndex(int key) const {
    int indexAt = -1;

    // travel through the list
    for (int i = 0; i < listCount; i++) {
        if (key == a[i]) {
            indexAt = i;
            break;
        }
    }

    return indexAt;
}

//******************************************************************************
// reads at a specific spot
// written by Ian

bool intList::readAt(int index, int &key) const {
    bool isRead = false;

    // checks if index is valid
    if (index < listCount && index >= 0) {
        key = a[index];
        isRead = true;
    }
    
    return isRead;
}

//******************************************************************************
// returns number of entries on the list
// written by Ian

int intList::count() const {
    return listCount;
}

//******************************************************************************
// returns the capacity of the whole list
// written by Ian

int intList::capacity() {
    return listCapacity;
}