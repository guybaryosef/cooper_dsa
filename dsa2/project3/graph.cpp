/*
 * DSA II Programming Assignment 3
 * By: Guy Bar Yosef
 * 
 * Graph class implementation
 * 
 */

#include <sys/times.h>
#include <climits>

#include "graph.h"
#include "heap.h"

/*
 * Graph - The graph class constructor. 
 * 
 * Declares the graph hashtable object that will keep
 * track of the nodes inserted into the graph.
 */
Graph::Graph() : 
    graphHTable(1) {}


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
std::vector<std::vector<std::string>> Graph::DijkstraAlgo
                    (const std::string &source, double &time) const {
    
    Node *src = (Node *)inGraph(source); /* source node */

    /* confirm valid source node */
    if (!src)
        throw "Invalid source.";

    clock_t beg_time = clock(); /* beginning time */
    
    /* initialize heap with max possible value (as it is non-resizable),
       yet there is no reason to add any values to it besides the source. */
    heap myHeap(nodes.size());
    src->dv = 0;  /* update source distance to 0 */
    myHeap.insert(source, 0, src); 

    /* go through each node in heap, in order of minimum distance */
    int cur_dist;
    Node *cur_pointer;
    while (myHeap.deleteMin( nullptr, &cur_dist, (void**) &cur_pointer) != 1) {

        cur_pointer->known = true; /* update known status of current node */

        /* go through current node's adjaceny list, updating its neighbors */
        for (auto &edge : cur_pointer->adjList) {

            if (edge.destination->dv == INT_MAX) /*if new edge, add it to heap */
                myHeap.insert(edge.destination->name, INT_MAX, edge.destination);
            
            /* if new shortest path found, update prev pointer and distances */
            if (!edge.destination->known && cur_dist + edge.cost < edge.destination->dv) {
                edge.destination->pv = cur_pointer;
                edge.destination->dv = cur_dist + edge.cost;
                myHeap.setKey(edge.destination->name, edge.destination->dv);
            }            
        }
    }

    vector<vector<std::string>> ans; /* our final answer */

    /* order ans in the same order as the list of graph nodes */    
    for (auto node : nodes) {
        if (node.dv == INT_MAX) {
            ans.push_back({node.name, "NO", "PATH"});
        }
        else{
            /* find the path to current node, with correct format */
            std::string cur_path; 
            Node *buf = &node;
            do {
                cur_path.insert(0, buf->name + ", ");
                buf = buf->pv;
            } while (buf);
            cur_path.insert(0, "[");
            cur_path.replace(cur_path.length()-2, 2, "]");
        
            ans.push_back( {node.name, to_string(node.dv), cur_path} );
        }
    }

    clock_t end_time = clock(); /* beginning time */
    time = ((double)(end_time - beg_time)) / CLOCKS_PER_SEC;

    return ans;
}


/*
 * inGraph - checks if the name n of a node is 
 * in the graph or not.
 * 
 * If it is, it returns a pointer to the node and
 * if not it returns a null pointer.
 */
void *Graph::inGraph(const std::string &n) const {
    return graphHTable.getPointer(n);
}


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
void Graph::addNodes(std::string &n1, std::string &n2, int w) {
    
    /* get/insert nodes from/into graph */
    if (!inGraph(n1)) {
        nodes.push_back(Node(n1));
        graphHTable.insert(n1, &nodes.back());
    }
    if (!inGraph(n2)) {
        nodes.push_back(Node(n2));
        graphHTable.insert(n2, &nodes.back());
    }

    /* add an edge fron n1 to node n2 */
    Node *cur_node = (Node *)inGraph(n1);
    cur_node->adjList.push_back(Edge(w, (Node *)inGraph(n2)));
}
