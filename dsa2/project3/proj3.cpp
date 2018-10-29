/*
 * DSA II Programming Assignment 3
 * By: Guy Bar Yosef
 * 
 * Main function
 * 
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>


#include "heap.h"
#include "hash.h"
#include "graph.h"


void readFromFile(Graph & graph);
void implementDijkstra(Graph &graph, std::vector<std::vector<std::string>> &ans);
void outputToFile(std::vector<std::vector<string>> &output);


int main() {
    Graph graph;
    readFromFile(graph);

    std::vector<std::vector<string>> output;
    implementDijkstra(graph, output);
    

    outputToFile(output);
    return 0;
}


/*
 * OuputToFile - outputs the dijkstra algorithm's output
 * to a file.
 * 
 * This function queries a user for an output file and 
 * writes the graph class's dijkstra algorithm method' 
 * output to it.
 */
void outputToFile(std::vector<std::vector<string>> &output) {

    /* get and open output file */
    std::ofstream file;
    do {
        std::cout << "Enter name of output file: ";

        std::string out;
        std::cin >> out;

        file.open(out);

        if (!file)
            std::cerr << "Invalid output file name." << std::endl;

    } while (!file);

    /* write inputted 'output' std::vector to output file */
    for (auto line : output)
        file << line[0] << ": " << line[1] << " " << line[2] << std::endl;

    file.close();
}


/*
 * implementDijkstra - implements the dijkstra algorithm.
 * 
 * Given a graph referece, this function repeatedly queries 
 * a user for a valid starting vertex and once it has recieved
 * one it calls the dijkstra algorithm that is a graph class method.
 * This function outputs to stdout the time in seconds the
 * algorithm took to run and returns a std::vector of std::vector of strings, 
 * the output of the graph class method. 
 */
void implementDijkstra(Graph &graph, std::vector<std::vector<std::string>> &ans) {
    
    std::string source;
    double time;
    do {
        std::cout << "Enter a valid vertex id for the starting vertex: ";
        std::cin >> source;

        try {
            ans = graph.DijkstraAlgo(source, time);
        }
        catch(const char *exception) {
            std::cerr << exception << std::endl;
        }
    } while (ans.empty());

    std::cout << std::fixed << std::setprecision(2) <<
        "Total time (in seconds) to apply Dijkstra's algorithm: " << time << std::endl;
}


/*
 * readFromFile - reads in a graph from a file.
 * 
 * This function repeatedly queries 
 * a user for a valid input file and once recieved will open
 * the file and populates the inputted graph with the contents
 * of the file.
 * 
 * Note: the contents of the input file are assumed to be of 3
 * string lines, with only white space inbetween each string. The
 * 3 strings are: node1, node2, and the weight of the edge from 
 * node1 to node2. 
 */
void readFromFile(Graph &graph) {

    /* get and open the input file */    
    std::ifstream input;
    do {
        std::cout << "Enter name of a graph file: ";

        std::string in;
        std::cin >> in;

        input.open(in);
        if (!input) 
            std::cerr << "Invalid file." << std::endl;
    } while (!input);

    /* read in and populate graph from input file */
    std::string buf;
    std::string node1, node2, weight;

    
    while (getline(input, buf) ) {
        std::stringstream tmp;
        tmp << buf;
        tmp >> node1 >> node2 >> weight;

        graph.addNodes(node1, node2, stoi(weight));
    }

    input.close();
}
