/**
 * |-------------------------------------------------------------|
 *  Graphl.cpp
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

#include "graphl.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
GraphL::GraphL() {
    size = 0;
    for(int i = 0; i < MAXNODES; ++i) {
        this->gNode[i].data = nullptr;
        this->gNode[i].edgeHead = nullptr;
        this->gNode[i].visited = false;
    }
}

// Destructor, clears memory
GraphL::~GraphL() {
    this->makeEmpty();
}

/**
 * Deletes the object and frees memory.
*/
void GraphL::makeEmpty() {
    for(int i = 1; i <= size; i++) {
        EdgeNode* curr = gNode[i].edgeHead;
        while(curr != nullptr) {
            EdgeNode* temp = curr;
            curr = curr->nextEdge;
            delete temp;
            temp = nullptr;
        }
        delete gNode[i].data;
        gNode[i].data = nullptr;
    }
    // cout << "MakeEmpty" << endl;
}

/**
 * Builds up graph node information and adjacency list of edges between each
 * node reading from a data file
*/
void GraphL::buildGraph(ifstream& inFile) {
    // read from data file
    inFile >> size;            // sets the size
    string name = "";      
    getline(inFile, name); 

    // sets the name into the array.
    for (int i = 1; i <= size; ++i) 
    {
        getline(inFile, name);
        NodeData* curr = new NodeData(name);
        gNode[i].data = curr;       
    }
    // cout << "BuildGrapgh1" << endl;
    int from, to;
    while (inFile >> from >> to)  {

        if (from == 0) break ;

        // If the edge head for "from" is not null, insert new node as head
        if (gNode[from].edgeHead != NULL)  {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;           
            node->nextEdge = gNode[from].edgeHead;  
            gNode[from].edgeHead = node;  
        } else  { // If the edge head for "from" is null, create new head node
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            
            gNode[from].edgeHead = node;   
            gNode[from].edgeHead->nextEdge  = NULL;
        } 
         // cout << "BuildGrapgh2" << endl;

    }

}

/**
 * Makes a depth-first search and displays each node in depth-first order.
*/
void GraphL::depthFirstSearch() {
    // Reset all nodes' visited status to false
    for (int i = 1; i <= size; i++) {
        gNode[i].visited = false;
    }
    // Call the recursive helper method on the first node
    depthFirstSearchHelper(1);
    cout << endl;

}  

/**
 * A private recursive method that helps depthFirstSearch() method.
*/
void GraphL:: depthFirstSearchHelper(int i) {
    // Mark the current node as visited
    gNode[i].visited = true;
    cout << i << " "; // Display the node
    EdgeNode* currEdge = gNode[i].edgeHead;
    while (currEdge != nullptr) {
        int adjNode = currEdge->adjGraphNode;
        // If the adjacent node hasn't been visited, visit it
        if (!gNode[adjNode].visited) {
            depthFirstSearchHelper(adjNode);
        }
        currEdge = currEdge->nextEdge;
    }
}

/**
 * Displays each node information and edge in the graph.
*/
void GraphL::displayGraph() {
    cout << "Graph:" << endl;

    for (int i = 1; i <= size; i++) {
        cout << "Node" << i << "\t\t" << *(gNode[i].data) << endl;

        EdgeNode* edge = gNode[i].edgeHead;

        while (edge != nullptr) {
            cout << "  edge  " << i << "  " << edge->adjGraphNode << endl;
            edge = edge->nextEdge;
        }
    }

    cout << endl << "Depth-first ordering: ";
    depthFirstSearch();
    cout << endl;
}

