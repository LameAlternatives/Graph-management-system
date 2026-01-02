#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "p11.h"

using namespace std;


int main(int argc, char *argv[]) {
    int action, unode, vnode, weight;
    int mytable[40];
    int mytable2[40];
    int count = 0;
    int count2 = 0;
    int i, j, label;
    bool doit;
    bool rc;
    int distance;
    int tf;

    if ((argc < 2) || (sscanf(argv[1], "%d", &tf) != 1) || ((tf != 0) && (tf != 1))) {
	cerr << "Run " << argv[0] << " with a parameter of 0 for false, 1 for true.\n";
	exit(1);
    }

    Graph myGraph(40, (bool)tf);

    while (cin >> action >> unode >> vnode >> weight) {
	rc = false;
	if (vnode >= 0) {
	    // this is an edge record
	    if (action == 0) {
		rc = myGraph.addEdge(unode, vnode, weight);
		cout << "addEdge(" << unode << "," << vnode << "," << weight << ") returned: " << (rc?"True":"False") << endl;
	    } else {
		rc = myGraph.deleteEdge(unode, vnode, weight);
		cout << "deleteEdge(" << unode << "," << vnode << ") returned: " << (rc?"True":"False");
		cout << " with edge weight of " << weight << endl;
	    }
	} else {
	    // this is a node creation
	    if (action == 0) {
		rc = myGraph.createV(unode);
		cout << "createV(" << unode << ") returned: " << (rc?"True":"False") << endl;
	    }
	}
	if (rc) {
	    for (i = 0; i < count; i++) {
		if (mytable[i] == unode) {
		    break;
		}
	    }
	    if (i == count) {
		mytable[count++] = unode;
	    }
	    if (vnode >= 0) {
		for (i = 0; i < count; i++) {
		    if (mytable[i] == vnode) {
			break;
		    }
		}
		if (i == count) {
		    mytable[count++] = vnode;
		}
	    }
	}
    }
    myGraph.printIt();
    myGraph.printPaths();
    cout << "*** start of bfPrint() output\n";
    for (i = 0; i < count; i++) {
	label = mytable[i];
	doit = true;
	for (j = 0; j < count2; j++ ) {
	    if (label == mytable2[j]) {
		doit = false;
		break;
	    }
	}

	if (doit) {
	    mytable2[count2++] = label;
	    cout << "   Printing from " << label << endl;
	    myGraph.bfPrint(label);
	}
    }
    cout << "*** end of bfPrint() output\n";
    cout << "*** start of minPath output\n";
    count2 = 0;
    for (i = 0; i < count; i++) {
	label = mytable[i];
	doit = true;
	for (j = 0; j < count2; j++ ) {
	    if (label == mytable2[j]) {
		doit = false;
		break;
	    }
	}

	if (doit) {
	    mytable2[count2++] = label;
	    cout << "   MinPaths for " << label << endl;
	    for (j = 0; j < count; j++) {
		myGraph.dijkstra(label, mytable[j], distance);
		cout << "      to " << mytable[j] << ": " << distance << endl;
	    }
	}
    }
    cout << "*** end of minPath() output\n";
    cout << "*** start of isCyclic output\n";
    cout << "    The graph is " << (myGraph.isCyclic()?"cyclic":"acyclic") << endl;
    cout << "*** end of isCyclic output\n";
}
