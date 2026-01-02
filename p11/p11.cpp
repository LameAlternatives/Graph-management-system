// Team 13
// Ho Ian Zam and Tamaranlayif Onitsha
// CSC 255 Data Structures
// P11
// Nov.27.2023
// Creates a graph management and analysis system
// with breadth-first search
// and dijkstra's algorithm
// and checks if it is cyclic based on if it is directed or not

//******************************************************************************
// connects this file with the header

#include "p11.h"
using namespace std;

//******************************************************************************
// Constructor
// The section below was written by Ian

Graph::Graph(int n, bool directed) {
    vCount = 0;
    eCount = 0;

    // establishes variables in construction
    this->n = n;
    this->directed = directed;

    // sets up 2D array by making a smaller array correspond to a larger array
    // list contains vIDs and weights
    a = new int *[n];
    int *b = new int[n * n];

    for (int i = 0; i < n; i++) {
        a[i] = &(b[i * n]);
    }

    // sets up array that contains labels
    labels = new intList[n];

    // lists to record traversed nodes and their distance values
    set = new int[n];
    lambda = new int[n];

    // creates integer queue for breadth first search
    q = new iQ[n];

    // clear a
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
}

//******************************************************************************
// destructor
// The section below was written by Ian

Graph::~Graph() {
    vCount = 0;
    eCount = 0;

    delete[] a;
    delete[] labels;
    delete[] q;
    delete[] set;
    delete[] lambda;
}

//******************************************************************************
// return index (vid) of label
// The section below was written by Ian

int Graph::labelToVid(int label) const {
    // go through list a and get the index
    return labels->getIndex(label);
}

//******************************************************************************
// return label of vid
// The section below was written by Ian

int Graph::vidToLabel(int vid) const {
    int key;
    // puts label into key
    labels->readAt(vid,key);
    return key;
}

//******************************************************************************
// create a vertex
// The section below was written by Ian

bool Graph::createV(int label) {
    bool re = false;

    // if there is space
    if (vCount < n) {
        // if label is not already in the list
        if (!isV(label)) {
            // add label
            re = true;
            vCount++;
            labels->add(label);
        }
    }

    return re;
}

//******************************************************************************
// add edge by adding weight
// The section below was written by Ian

bool Graph::addEdge(int uLabel, int vLabel, int weight) {
    bool re = false;

    // if there are no edges between the two
    if (!isEdge(uLabel, vLabel)) {
        // if a valid weight is given
        if (weight > 0) {
            // Count to track how many things need to be created
            int createCount = 0;

            // if uLabel isn't a vertex, createCount++
            if (!isV(uLabel)) {
                createCount++;
            }

            // if vLabel isn't a vertex, createCount++
            if (!isV(vLabel)) {
                createCount++;
            }
            // if there is enough space for new vertices
            if ((n - vCount) >= createCount++) {
                // confirmed true
                re = true;

                // if uLabel isn't a vertex, make it
                createV(uLabel);
            
                // if vLabel isn't a vertex, make it
                createV(vLabel);

                // sets up coordinates
                int sVid = labelToVid(uLabel);
                int dVid = labelToVid(vLabel);
                eCount++;

                // add the weight to the coordinates
                // if it's an undirected graph 
                // and it is on the wrong half of the graph, put it in place
                if (!directed && (dVid < sVid)) {
                    a[dVid][sVid] = weight;

                // if its a directed graph or the values are in the right place
                } else {
                    a[sVid][dVid] = weight;
                }
            }
        }
    }

    return re;
}

//******************************************************************************
// deletes edge by setting weight to 0
// The section below was written by Ian

bool Graph::deleteEdge(int uLabel, int vLabel, int &weight) {
    bool re = false;
    weight = -1;

    // if there are no edges between the two
    if (isEdge(uLabel, vLabel)) {
        // confirmed true
        re = true;

        // sets up coordinates
        int sVid = labelToVid(uLabel);
        int dVid = labelToVid(vLabel);

        // pass on the deleted weight
        weight = a[sVid][dVid];

        // delete edge by making it 0
        // if it's an undirected graph 
        // and it is on the wrong half of the graph, put it in place
        if (!directed && (dVid < sVid)) {
            a[dVid][sVid] = 0;

        // if its a directed graph or the values are in the right place
        } else {
            a[sVid][dVid] = 0;
        }
    }

    return re;
}

//******************************************************************************
// clears graph
// The section below was written by Ian

void Graph::clear() {
    // clears all lists and labels
    labels->clear();

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            a[i][j] = 0;
        }
    }
    
    vCount = 0;
    eCount = 0;
}

//******************************************************************************
// determines if an edge exists
// The section below was written by Ian

bool Graph::isEdge(int uLabel, int vLabel) {
    bool re = false;

    // get coordinates
    int sVid = labelToVid(uLabel);
    int dVid = labelToVid(vLabel);

    if (sVid != -1 && dVid != -1) {
        // checks if spot is empty
        if (a[sVid][dVid] != 0) {
            re = true;
        // if undirected, also check the symmetric side
        } else if (!directed && a[dVid][sVid] != 0) {
            re = true;
        } 
    } 
    
    
    return re;
}

//******************************************************************************
// determines if V exists
// The section below was written by Ian

bool Graph::isV(int label) {
    bool re = false;

    // if label exists
    if (labels->getIndex(label) != -1) {
        re = true;
    }

    return re;
}

//******************************************************************************
// determines the amount of edges entering a label
// The section below was written by Ian

int Graph::inDegree(int label) {
    int degreeCount = -1;

    // if it is real
    int vid = labelToVid(label);
    if (vid >= 0 && directed) {
        degreeCount = 0;
        for (int i = 0; i < vCount; i++) {
            if (a[i][vid]) {
                degreeCount++;
            }
        }
    }
    return degreeCount; 
}

//******************************************************************************
// determine the amount of edges leaving a label
// The section below was written by Ian

int Graph::outDegree(int label) {
    int degreeCount = -1;

    // if it is real
    int vid = labelToVid(label);
    if (vid >= 0 && directed) {
        degreeCount = 0;
        for (int i = 0; i < vCount; i++) {
            if (a[vid][i]) {
                degreeCount++;
            }
        }
    }
    return degreeCount; 
}

//******************************************************************************
// checks the degree of labels in an undirected graph
// The section below was written by Ian

int Graph::degree(int label) {
    int degreeCount = -1;
      
    // mark unvisited areas
    bool *visited = new bool[vCount];
        
    for (int i = 0; i < vCount; i++) {
        visited[i] = false;
    }

    int vid = labelToVid(label);

    // if it is real
    if (vid >= 0 && !directed) {
        degreeCount = 0;

        for (int i = 0; i < vCount; i++) {
            // if row or column and not visited
            if ((a[i][vid] || a[vid][i]) && !visited[i]) {
                visited[i] = true;
                degreeCount++;
            }
        }
    }

    delete [] visited;

    return degreeCount; 
}

//******************************************************************************
// return graph size
// The section below was written by Ian

int Graph::sizeV() const {
    return n;
}

//******************************************************************************
// returns number of vertexes in graph
// The section below was written by Ian

int Graph::sizeUsedV() const {
    return vCount;
}

//******************************************************************************
// Return number of edges in graph
// The section below was written by Ian

int Graph::sizeE() const {
    return eCount;
}

//******************************************************************************
// prints out information
// The section below was given in the drop box

void Graph::printIt() {
    int r, c;
    int key = 0;

    cout << "Graph info:\n";
    cout << "  Graph size = " << n << endl;
    cout << "  vCount = " << vCount << endl;
    cout << "  eCount = " << eCount << endl;
    cout << "\nGraph contents:\n";
    for (r = 0; r < vCount; r++) {
        // pulls out the value and stores it in a key
        key = vidToLabel(r);

	    cout << "  Node(" << r << "," << key << "):";
	    for (c = 0; c < vCount; c++) {
	        cout << " " << setw(2) << a[r][c];
	    }
	    cout << endl;
    }

    cout << "Degree table (normal, in, out)\n";

    for (r = 0; r < vCount; r++) {
        // pulls out the value and stores it in a key
        key = vidToLabel(r);

	    cout << "  Node(" << r << "," << key << "):" << setw(6) << degree(key) 
            << "," << setw(3) << inDegree(key) 
            << "," << setw(3) << outDegree(key) << endl;
    }
}

//******************************************************************************
// returns the min between 2 numbers
// The section below was written by Ian

int min(int x, int y) {
    if (x > y) {
        x = y;
    }

    return x;
}

//******************************************************************************
// returns the max between 2 numbers
// The section below was written by Ian

int max(int x, int y) {
    if (x < y) {
        x = y;
    }

    return x;
} 

//******************************************************************************
// prints using breath-first search
// The section below was written by Ian

void Graph::bfPrint(int label) {

    if (isV(label)) {
        // get vid of label
        int vid = labelToVid(label);
        // used to store dequeued vid
        int wVid;
        int count = 1;

        // vreate visited list
        bool *visited = new bool[vCount];
        
        for (int i = 0; i < vCount; i++) {
            visited[i] = false;
        }

        q->clear();
        // enqueue starting label and mark as visited
        q->enq(vid);
        visited[vid] = true;;

        // print information
        cout << "       Item 0 is (" << vid \
                   << "," << label << ")" << endl;
        
        // while there are still items in the list to dequeue
        // the dequeued value is the value we have finished visiting
        while (q->deq(wVid)) {
            for (int i = 0; i < vCount; i++) {

                // check if we haven't visited yet
                if (!visited[i]) {

                    // if dequeued value shares an edge with another, 
                    // they are adjacent
                    if (isEdge(vidToLabel(wVid), vidToLabel(i))) {
                        // mark as visited and enqueue them so that 
                        // we check on it's neighbors next
                        visited[i] = true;
                        q->enq(i); 

                        // print data
                        cout << "       Item " << count << " is (" << i \
                            << "," << vidToLabel(i) << ")" << endl;
                        count++;
                    }
                }
            }
            
        }
        delete [] visited;
        
    }
}

//******************************************************************************
// checks if there is a path from two labels
// The section below was written by Ian

bool Graph::isPath(int uLabel, int vLabel) {
    bool re = false;

    if (isV(uLabel) && isV(vLabel)) {
        // get vids of labels
        int uVid = labelToVid(uLabel);
        int vVid = labelToVid(vLabel);
        // used to store dequeued variable
        int wVid;

        // array keeps track of visited places
        bool *visited = new bool[vCount];

        for (int i = 0; i < vCount; i++) {
            visited[i] = false;
        }

        q->clear();
        // enqueue start
        q->enq(uVid);
        
        // while there are still items in the list to dequeue
        // the dequeued value is the value we have finished visiting
        while (q->deq(wVid)) {
            for (int i = 0; i < vCount; i++) {

                // check if we haven't visited yet
                if (!visited[i]) {

                    // if dequeued value shares an edge with another, 
                    // they are adjacent
                    if (isEdge(vidToLabel(wVid), vidToLabel(i))) { 
                        visited[i] = true;
                        q->enq(i); 
                    }
                }
            }
        }

        // if we have visted the destination, return true
        re = visited[vVid];
        delete [] visited;
    }

    return re;
}

//******************************************************************************
// prints if there is a path from each node
// The section below was written by Ian

void Graph::printPaths() {
    int key1;
    int key2;

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            // get labels of vids
            key1 = vidToLabel(i);
            key2 = vidToLabel(j);

            // if there is a path, state it; if not, say it doesn't
            if (isPath(key1, key2) == true) {
                cout << key1 << " does have a path to " << key2 << endl;
            } else {
                cout << key1 << " does not have a path to " << key2 << endl;
            }
        }
    }
}


//******************************************************************************
// returns the shortest distance between two labels
// The section below was written by Ian

bool Graph::dijkstra(int sLabel, int dLabel, int &distance) {
    bool re = false;
    distance = -1;

    // vids of labels
    int sVid = labelToVid(sLabel);
    int dVid = labelToVid(dLabel);

    // checks if values are valid, if true, this is all true
    if (isV(sLabel) && isV(dLabel)) {
        re = true;

        // populate lambda
        dijkstra(sVid);

        // set appropriate distance
        distance = lambda[dVid];
        }
    
    return re;
}

//******************************************************************************
// repopulates lambda with the updated distances
// The section below was written by Ian

void Graph::dijkstra(int s) {
    // min lambda value key
    int wVid;

    // set all vertex paths to be unused
    // and set all paths as unpassible until found otherwise
    for (int i = 0; i < vCount; i++) {
        set[i] = Y;
        lambda[i] = INFINITE;
    }

    // mark starting vertex
    set[s] = X;

    // goes through set and finds all numbers that haven't been traversed
    for (int i = 0; i < vCount; i++) {

        // checks if they are valid. If valid, put down weights
        if (set[i] == Y) {

            // if not visited and is edge, give it weight
            if (isEdge(vidToLabel(s), vidToLabel(i))) {

                // puts values in the appropriate spots in an undirected graph
                if (!directed && i < s) {
                    lambda[i] = a[i][s];

                } else {
                    lambda[i] = a[s][i];
                }
            } 
        }
    }

    // the distance to itself is 0
    lambda[s] = 0;

    // while there are places we haven't been to, find the shortest path
    while(minLambdaY(wVid)) {
        // mark as visited
        set[wVid] = X;
        
        // travel through list
        for (int i = 0; i < vCount; i++) {

            // if not visited and is an edge
            if (set[i] == Y) {

                // finds the shortest math between the current value
                // and the smallest lambda + the weight
                if (isEdge(vidToLabel(wVid), vidToLabel(i))) {

                    // if its in the wrong place
                    if (!directed && i < wVid) {
                        lambda[i] = min(lambda[i], (lambda[wVid] + a[i][wVid]));

                    } else {
                        lambda[i] = min(lambda[i], (lambda[wVid] + a[wVid][i]));
                    }
                } 
            }
        }
    }
}

//******************************************************************************
// finds the shortest travel distance among the values in Y
// The section below was written by Ian

bool Graph::minLambdaY(int &minV) {
    bool re = false;

    // finds the shortest path among the values in set Y
    int minVal = INFINITE;
    int minVid = -1;

    // goes through set and finds all numbers that haven't been traversed
    for (int i = 0; i < vCount; i++) {
        if (set[i] == Y) {
            // if a smaller value is found, make it the new min
            if (lambda[i] <= minVal) {
                
                minVal = lambda[i];
                minVid = i;
            }
        }
    }

    // validate search results
    if (minVid >= 0) {
        minV = minVid;
        re = true;
    }

    return re;
}

//******************************************************************************
// checks if a directed graph is cyclic
// The section below was written by Ian

bool Graph::isCyclicDirected() {
    bool re = false;
    int iLabel;

    if (vCount > 0) {
        // traverse list
        for (int i = 0; i < vCount; i++) {
            iLabel = vidToLabel(i);
            // if path to itself
            if (isPath(iLabel, iLabel)) {
                re = true;
                break;
            }
        }
    }
}

//******************************************************************************
// checks if a undirected graph is cyclic
// The section below was written by Ian

bool Graph::isCyclicUndirected() {
    bool re = false;
    int weight;
    int uVid;
    int vVid;

    // travel through the whole graph
    for (int u = 0; u < vCount; u++) {
        for (int v = 0; v < vCount; v++) {
            uVid = vidToLabel(u);
            vVid = vidToLabel(v);

            if (isEdge(uVid, vVid)) {
                // temporarily deletes path
                weight = a[u][v];
                a[u][v] = 0;

                // checks if there are other ways
                if (isPath(uVid,vVid)) {
                    re = true;
                }

                // restores path
                a[u][v] = weight;
            }
        }
    }   

    return re;
}

//******************************************************************************
// calls respective isCyclic functions based on directedness
// The section below was written by Ian

bool Graph::isCyclic() {
    bool re = false;

    // calls function based on directedness
    if (directed) {
        re = isCyclicDirected();

    } else {
        re = isCyclicUndirected();
    }

    return re;
}