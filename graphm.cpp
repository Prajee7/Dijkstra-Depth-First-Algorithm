/**
 * |-------------------------------------------------------------|
 *  GraphM.cpp
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
 *  need to test for incorrect inputs.
*/

#include "graphm.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * Defualt Constructor
 * Intializes private variables. (Nodes, Visited, Distance, Path, Table and ...)
*/ 
GraphM::GraphM() {
    size = 0;
    for (int i = 0; i < MAXNODES; ++i) {
        for (int j = 0; j < MAXNODES; ++j) {
            C[i][j] = highInt;
            T[i][j].visited = false;
            T[i][j].dist = highInt;
            T[i][j].path = 0;
        }
    }
}

/**
 * Destructor
 * Clears all data, and helps fix memory issues.
*/ 
GraphM::~GraphM() {

}

/**
 * Builds up graph node information and adjacency matrix of edges between 
 * each node reading from a data file.
*/
void GraphM::buildGraph(ifstream& file) {
    // read the number of nodes
    file >> size;
    // cout << size << endl;

    if (size < 0 || size > MAXNODES) {
        return; // invalid number of nodes in the file.
    }

    // read the node data
    string nodeData;
    getline(file, nodeData); // discard the newline after size

    for (int i = 1; i <= size; ++i) {
        getline(file, nodeData);
        data[i] = NodeData(nodeData);
    }

    // initialize the cost array to highInt
    for (int i = 1  ; i <= size; ++i) { 
        for (int j = 1; j <= size; ++j) { 
            C[i][j] = highInt;
        }
    }

    // read the nodes and costs
    int firstNode, endNode, cost;
    while (file >> firstNode >> endNode >> cost) {
        if (firstNode == 0 && endNode == 0 && cost == 0) {
            break; // end of cost list
        }
        if (firstNode < 1 || firstNode > size || endNode < 1 || endNode > size) {
            return; // invalid node index
        }

        C[firstNode][endNode] = cost;
    }
}

/**
 * Find the shortest path between every node to every other node in the graph
 * using Dijkstra's Algorithm
*/
void GraphM::findShortestPath() {
    // Iterate over every node in the graph as a source node
    for (int sourceNode = 0; sourceNode <= size; sourceNode++) {
        // Initialize the distance of the source node to itself to 0
        T[sourceNode][sourceNode].dist = 0;
        int v = -1;
        int minDist = highInt;

        // Select the unvisited node with the minimum distance from the source node
        for (int i = 0; i <= size; i++) {
            v = -1;
            minDist = highInt;
            for (int j = 0; j <= size; j++) {
                if (!(T[sourceNode][j].visited) && T[sourceNode][j].dist < minDist) {
                    v = j;
                    minDist = T[sourceNode][j].dist;
                }
            }

            // If all nodes have been visited, break out of the loop
            if (v == -1) {
                break;
            } else {
                T[sourceNode][v].visited = true;
            }

            // If all nodes have been visited, break out of the loop
            for (int w = 0; w <= size; w++) {
                if (C[v][w] != highInt && !T[sourceNode][w].visited) {
                    int newDist = T[sourceNode][v].dist + C[v][w];
                    if (newDist < T[sourceNode][w].dist) {
                        T[sourceNode][w].dist = newDist;
                        T[sourceNode][w].path = v;
                    }
                }
            }
        }
    }
}

/**
 * Insert an edge into graph between two given nodes and return true if task completed 
 * otherwise false.
*/
bool GraphM::insertEdge(int firstNode, int endNode, int edges) {
     // Check for invalid input
    if (firstNode <= 0 || firstNode > MAXNODES || endNode <= 0 || endNode > MAXNODES || edges < 0) {
        return false;
    }

    // Check that edge is not being inserted to the same node
    if (firstNode == endNode) {
        return false;
    }

    // Insert edge and return true if successful
    C[firstNode][endNode] = edges;
    findShortestPath();

    return true;
}

/**
 *  Remove an edge between two given node.
*/
bool GraphM::removeEdge(int firstNode, int endNode) {
    // Check if the nodes are within the valid range
     if ((firstNode > 0 && firstNode < highInt) && (endNode > 0 && endNode < highInt)) {

        // Check if there is an edge between the nodes
        if (C[firstNode][endNode] != highInt) {
            C[firstNode][endNode] = highInt;
            findShortestPath(); // Recalculate the shortest paths in the graph using Dijkstra's Algorithm
            return true;
        }
    }
    return false;
}
/**
 * Display the shortest path and distance between every pair of nodes using Dijkstra's algorithm 
*/
void GraphM::displayAll() const {
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node" << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;
    // Loop through each node in the graph
    for(int i = 1; i <= size; i++) {
        cout << data[i] << endl;

        // Loop through each pair of nodes in the graph
        for(int j = 1; j <= size; j++) {
            if(i != j) { // Skip if the pair of nodes are the same

                cout << setw(27) << i << setw(10) << j;
                if(T[i][j].dist >= INT_MAX) { // checks if the distance between the nodes is infinity.
                    cout << setw(12) << "----" << endl;
                } else { // Print the shortest distance between the nodes and the path to get there.

                    cout << setw(12) << T[i][j].dist << setw(10);
                    displayPath(i, j);
                    cout << endl;
                }
            }
        }
    }
}

/**
 * A private recursive method that prints out the path between 2 node.
 */
void GraphM::displayPath(int firstNode, int endNode) const {
    // get the next node in the path
    int i = T[firstNode][endNode].path;
    if(i > 0) { 
        // recursively display the path from the starting node to the next node.
        displayPath(firstNode, i);
        cout << endNode << " ";
    }
    // if the next node is the starting node, output the starting node
    if (firstNode == endNode) {
        cout << endNode << " ";
    }
}

/**
 * Will output one path in detail using a private recursive function.
 * Finds the distance and paths between 2 nodes
 */
void GraphM::display(int firstNode, int endNode) const {
    // Output the node numbers and distance
    cout << setw(7) << firstNode << setw(7) << endNode;
    if(T[firstNode][endNode].dist != INT_MAX) {
        cout << setw(12) << T[firstNode][endNode].dist;
    } else {
        cout << setw(15) << "----";
    }
    // Output the path using the private recursive function displayPath()
    cout << setw(15);
    displayPath(firstNode, endNode);
    cout << endl;
    // Output the path using the private recursive function displayNames()
    displayNames(firstNode, endNode);
    cout << endl;
}

/**
 * Recursive method that helps display() and displayAll() methods to output
 * node names and path.
 */
void GraphM::displayNames(int firstNode, int endNode) const {
    // Get the path to the ending node from the starting node
    int i = T[firstNode][endNode].path;
    // print the path from the starting node to the node that precedes the ending node
    if(i > 0) {
        displayNames(firstNode, i);
        cout << data[endNode] << endl;
    } 
    // If the starting node is the same as the ending node, just print the name of the node
    if (firstNode == endNode) {
        cout << data[endNode] << endl;
    }
    cout << endl;
}



