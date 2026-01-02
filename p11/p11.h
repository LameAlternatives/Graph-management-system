// Team 13
// Ho Ian Zam and Tamaranlayif Onitsha
// CSC 255 Data Structures
// P11.h
// Nov.27.2023

#ifndef __P11_H
#define __P11_H

#include <string>
#include <iostream>
#include "p8.h"
#include "iq.h"
#include <iomanip>

// run with 
// g++ p8.cpp cil.cpp iq.cpp p11.cpp p11m.cpp -o p11
// ./p11 0 < p11input1.txt > p11output1false.txt
// ./p11 0 < p11input2.txt > p11output2false.txt
// ./p11 1 < p11input1.txt > p11output1true.txt
// ./p11 1 < p11input2.txt > p11output2true.txt
//******************************************************************************

class Graph  {
    private:
        // VARIABLES
        int **a; // array for graph, size will be n*n
        intList *labels; // tracks number of nodes in the graph
        int n; // memorializes the dimensions of the graph matrix
        int vCount; // tracks the number of nodes in the graph
        int eCount; // tracks the number of edges in the graph
        bool directed; // remembers if a graph is directed or not
        iQ *q; // points to integer queue that uses a circular list
        // put distances in lambda from start node to all other nodes
        void dijkstra(int s); 
        // finds the shortest travel distance among the values in Y
        bool minLambdaY(int &minV); 

        int *lambda; // hold the distance between nodes during Dijkstra
        int *set; // record what path we have taken using x and y
        int const INFINITE = 1000000; // large number to represent infinity
        // X and Y are used with set to show what nodes we've 
        // travelled through and what path options we have
        int const X = 0; 
        int const Y = 1;

        // FUNCTIONS
        // returns the vertex index for the given label; 
        int labelToVid(int label) const; //returns -1 if no node has that label
        int vidToLabel(int vid) const;
        bool isCyclicDirected(); // checks if directed graph is cyclic
        bool isCyclicUndirected(); // checks if undirected graph is cyclic

    public:
        Graph(int n = 100, bool directed = true); // sets up empty graph
        ~Graph(); // deletes array "a" as the destructor

        // FUNCTIONS
        bool createV(int label); // creates a label as a vertex
        // adds an edge. If there are no vertices, make some if there is room
        bool addEdge(int uLabel, int vLabel, int weight);
        // delete edge by making it 0
        bool deleteEdge(int uLabel, int vLabel, int &weight); 
        void clear(); // clear graph

        // NON-MODIFIERS
        bool isEdge(int uLabel, int vLabel); // check if it is edge
        bool isV(int label); // check if it is vertex
        int inDegree(int label); // check how many edges fo in
        int outDegree(int label); // check how many edges go out
        int degree(int label); // check degrees for undirected graphs
        int sizeV() const; // return size of matrix
        int sizeUsedV() const; // return amount of labels
        int sizeE() const; // return amount of edges
        void printIt(); // prints out output
        void bfPrint(int label); // uses breath-first search to print data
        bool isPath(int ulabel, int vLabel);//uses BFS to find path in graph
        void printPaths(); // print paths
        // if start and destination labels are real, 
        //   return the shortest distance between the two
        bool dijkstra(int sLabel, int dLabel, int &distance);
        // calls isCyclic function based on undirected or directed
        bool isCyclic(); 
};

#endif