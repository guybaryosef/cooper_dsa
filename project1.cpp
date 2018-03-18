/*
 *  Data Structure & Algorithms I
 *  Project 1
 *  Professor Carl Sable
 * 
 *  Made by: Guy Bar Yosef
 */

#include "Functions.cpp"

int main() {

    std::ifstream input_file = read_file();

    std::ofstream output_file = write_file();


    executeInstructions(input_file, output_file);
    return 0;
}