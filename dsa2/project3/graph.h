/*
 * DSA II Programming Assignment 3
 * By: Guy Bar Yosef
 * 
 * Graph class definition
 * 
 */


#include <list>
#include <vector>
#include <string>
#include <climits>

#include "hash.h"

#ifndef _GRAPH
#define _GRAPH


class Graph {

private:

    /* Node struct is defined here in order to include
        it in the Edge struct. The Node struct, which 
        also includes the Edge struct, is defined after */ 
    struct Node; 

    /*
     * Definition of a graph edge. 
     * The edges are both weighted and directed.
     */
    struct Edge {
        int cost;  /* edge cost */
        Node* destination;  /* edge destination */

        Edge(int c, Node*d) : 
            cost(c), destination(d) {}
    };


    /*
     * Definition of a graph node struct. 
     */
    struct Node {
        std::string name; /* node name */
        std::list<Edge> adjList; /* node adjacency list */

        /* dijkstra specific values */
        Node* pv;    /* previous node */
        int dv;      /* distance from path */
        bool known;   /* whether node is known or not */

        Node(std::string n) : 
            name(n), pv(nullptr), dv(INT_MAX), known(false) {}
    };


    std::list<Node> nodes;  /* list of nodes in graph */
    hashTable graphHTable; /* contains graph nodes */


    /*
     * inGraph - checks if the name n of a node is 
     * in the graph or not.
     * 
     * If it is, it returns a pointer to the node and
     * if not it returns a null pointer.
     */
    void * inGraph(const std::string &n) const;

public:
    /*
     * Graph - The graph class constructor. 
     * 
     * Declares the graph hashtable object that will keep
     * track of the nodes inserted into the graph.
     */
    Graph();


    /*
     * DijkstraAlgo - Implements the dijkstra algorithm.
     * 
     * Takes in the source node 'start', and returns a vector
     * of a vector of strings, each one containing the:
     * current node, its distance to the source, and the path
     * to get from the source to the current node. 
     * 
     * Note: The order that the vector of strings will be in
     * is the same as the order of nodes that were added to
     * the graph.
     */
    std::vector<std::vector<std::string>> DijkstraAlgo(const std::string &start) const;


    /*
     * addNodes - adds nodes to the graph.
     * 
     * Inputted with the nodes named 'n1' and 'n2', this function
     * does two jobs:
     *  1. Checks if the nodes are already part of the graph and if
     * not adds them to the graph.
     *  2. Adds an edge from node n1 to node n2 with weight w.
     * 
     * Note: Duplicate edges will get added, our implementation of 
     * dijkstra will not be bothered by them.
     */
    void addNodes(std::string &n1, std::string &n2, int w);
};


#endif