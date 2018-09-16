/*
 * DSA II: Programming Assignment #1
 * By: Guy Bar Yosef
 * 
 * Spellchecker program, using the hashTable class.
 * 
 */

#include "hash.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<std::string> parseString(const std::string &input); /* parses string into valid words */


int main() {
    ////////////////////////// OPENING DICTIONARY FILE ///////////////////////////
    std::cout << "Enter name of dictionary: ";

    std::string dictStr;
    std::cin >> dictStr;

    std::ifstream dict(dictStr);
    if (!dict) {
        std::cerr << "Unable to open this dictionary. Please make sure you have inputted a valid dictionary file." << std:: endl;
        return -1;
    }

    ////////////////////// LOADING DICTIONARY & REPORTING TIME ///////////////////////
    clock_t t1 = clock();
    hashTable hTable(100000); /* initialize hashtable with a size of 100000 */

    std::string buf;
    while (getline(dict, buf)) {
        
        if (buf.length() > 20) /* skip words longer than 20 characters */
            continue;

        for (int i = 0 ; i < buf.length() ; ++i) /*convert all words to lowercase */
            buf[i] = tolower(buf[i]);
        
        hTable.insert(buf);
    }
    clock_t t2 = clock();

    double timeDiffInsert = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (int seconds) to load dictionary: " << timeDiffInsert << std::endl;

    dict.close();

    //////////////////////////// OPENING INPUT FILE ////////////////////////////
    std::cout << "Enter name of input file: ";

    std::string inputStr;
    std::cin >> inputStr;

    std::ifstream input(inputStr);
    if (!input) {
        std::cerr << "Unable to open input file. Please make sure you have inputted a valid input file." << std::endl;
        return -1;
    }

    //////////////////////////// OPENING OUTPUT FILE ////////////////////////////
    std::cout << "Enter name of output file: ";

    std::string outputStr;
    std::cin >> outputStr;

    std::ofstream output(outputStr);
    if (!output) {
        std::cerr << "Unable to open output file. Please make sure you have inputted a valid input file." << std::endl;
        return -1;
    }


    ////////////////////// CHECKING FILE & WRITING TO OUTPUT //////////////////////
    t1 = clock();

    int line = 1;
    while (getline(input, buf)) {

        for (int i = 0 ; i < buf.length() ; ++i) /*convert to lowercase the full sentence */
                buf[i] = tolower(buf[i]);

        std::vector<std::string> words = parseString(buf);
        for (auto word : words) {
            
            if (word.length() > 20)
                output << "Long word at line " << line << ", starts: " << word.substr(0, 20) << std::endl;
            else if (!hTable.contains(word)) 
                output << "Unknown word at line " << line << ": " << word << std::endl;
        }
        ++line;
    }
    t2 = clock();

    double timeDiffOut = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    std::cout << "Total time (int seconds) to check document: " << timeDiffOut << std::endl;

    return 0;
}


/*
 * Parses string and returns a vector of individual 'words'.
 * A word is defined as a sequence of valid characters, which are
 * letters, digits, dashes, and apostrophes.
 */
std::vector<std::string> parseString(const std::string &input) {
    std::vector<std::string> output;
    
    bool inWord = false;
    int beg = 0;
    for (int i = 0 ; i < input.length() ; ++i) {
        if (isalnum(input[i]) || input[i] == '-' || input[i] == '\'') {
            if (!inWord) {
                inWord = true;
                beg = i;
            }
        }
        else { 
            if (inWord) {
                inWord = false;
                output.push_back(input.substr(beg, i-beg));
            }
        }
    }
    if (inWord)
        output.push_back(input.substr(beg));

    return output;
}