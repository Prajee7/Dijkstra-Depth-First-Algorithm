/**
 * |-------------------------------------------------------------|
 *  GraphM.h
 *  Prajeet Pounraj
 *  CSS 343 - Prof. Rahman
 *  May 5, 2023
 * |-------------------------------------------------------------|
 *  Description:
 *  This code implements Dijkstra's shortest path algorithm to find the lowest cost paths
 *  between nodes in a graph. The input data is read from a file, which specifies the number
 *  of nodes and their descriptions, as well as the edges connecting the nodes. The output
 *  includes the cost and path from every node to every other node, as well as the details
 *  of a specific path. The code can handle multiple graphs with up to 100 nodes each.
 * |-------------------------------------------------------------|
 *  Assume:
 *  This code assumes that the input data is correctly formatted and valid. Do not
 *  need to test for incorrect
*/
#ifndef DIJKSTRAS_GRAPHM_H
#define DIJKSTRAS_GRAPHM_H

#include "nodedata.h"
#include <iostream>
#include <climits>

using namespace std;

const int MAXNODES = 100;
const int highInt = INT_MAX;

class GraphM {
    private:

        struct TableType {
            bool visited; // whether node has been visited
            int dist; // shortest distance from source known so far
            int path; // previous node in path of min dist
        };

        NodeData data[MAXNODES]; // data for graph nodes
        int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
        int size; // number of nodes in the graph
        TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path  

        // recursive method that helps display() method.
        void displayPath(int firstNode, int endNode) const;

        // recursive method that helps display() and displayAll() methods to output
        // node names and path.
        void displayNames(int firstnode, int endNode) const;

    public:
        // default constructor
        GraphM();
        // destructor
        ~GraphM();

        // Builds up graph node information and adjacency matrix of edges between 
        // each node reading from a data file.
        void buildGraph(ifstream& inFile);

        // Find the shortest path between every node to every other node in the
        // graph, i.e., TableType T is updated with shortest path information.
        void findShortestPath();

        // Insert an edge into graph between two given nodes.
        bool insertEdge(int firstNode, int endNode, int edges);

        // Remove an edge between two given node.
        bool removeEdge(int firstNode, int endNode);

        // Display the cost and path from every node to every other node.
        void displayAll() const;

        // Will output one path in detail.
        void display(int firstNode, int endNode) const;
};



#endif // DIJKSTRAS_GRAPHM_H