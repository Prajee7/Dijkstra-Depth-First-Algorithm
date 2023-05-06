/**
 * |-------------------------------------------------------------|
 *  Graphl.h
 *  Prajeet Pounraj
 *  CSS 343 - Prof. Rahman
 *  May 5, 2023
 * |-------------------------------------------------------------|
 *  Description:
 *  This program is designed to display information about a graph and implement
 *  a depth-first search algorithm. The input data for the program is contained
 *  in a text file, which begins with the number of nodes in the graph, followed
 *  by a description of each node, and then a list of edges connecting the nodes.
 *  Each edge is represented by two integers indicating the nodes it connects. The
 *  input file may contain multiple graphs, each with at most 100 nodes.
 * |-------------------------------------------------------------|
 *  Assume:
 *  The program assumes that the input data file is correctly formatted and contains
 *  valid data.
*/

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H


#include "nodedata.h"
#include <iostream>
#include <climits>

using namespace std;

int const MAXNODES = 100;  

class GraphL {
    private:
        int size;
        
        struct EdgeNode; // forward reference for the compiler
        struct GraphNode { // structs used for simplicity, use classes if desired
            EdgeNode* edgeHead; // head of the list of edges
            NodeData* data; // data information about each node
            bool visited;
        };

        struct EdgeNode {
            int adjGraphNode; // subscript of the adjacent graph node
            EdgeNode* nextEdge;
        };

        GraphNode gNode[MAXNODES];

        // deletes the object. 
        void makeEmpty();
        
        // private recursive function that that helps depthFirstSearch method.
        void depthFirstSearchHelper(int i);  



    public:
        // constructor
        GraphL();
        // destructor
        ~GraphL();

        // builds up graph node information and adjacency list of edges between each
        // node reading from a data file
        void buildGraph(ifstream& inFile);
        // Makes a depth-first search and displays each node in depth-first order.
        void depthFirstSearch();
        // Displays each node information and edge in the graph.
        void displayGraph();    
};
#endif // DEPTHFIRSTSEARCH_H
