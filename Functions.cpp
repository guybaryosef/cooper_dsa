/*
 * Functions that are used in the project.
 */


#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <map>

#include "SimpleList.h"
#include "stack.h"
#include "queue.h" 

std::ifstream read_file();
std::ofstream write_file();
template<typename T> SimpleList<T>* findList(std::string name);
void executeInstructions(std::ifstream & input_file, std::ofstream & output_file);



/*
 * Opens a file to read in instructions from.
 * Will prompt for correct file name repeatedly until file opens successfully.
 */
std::ifstream read_file() {
    std::string input;
    std::cout << "Please enter a file to read in from: " << std::endl;
    std::cin >> input;
    std::ifstream input_file(input);
    return input_file;
}

/*
 * Opens a file for writing to(will overwrite previous data). 
 * If the inputted file does not exist, it will create a new file with the inputted name.
 */
std::ofstream write_file() {
    std::string output;
    std::cout << "Please enter a file to write out to: " << std::endl;
    std::cin >> output;
    std::ofstream output_file(output);
    return output_file;
}

/*
 * Searches for a SimpleList with a given name from the list of the corresponding type.
 * If the looked for list exists, a pointer to it is returned, otherwise a nullptr is returned.
 */
template <typename T>
SimpleList<T>* findList(std::list<SimpleList<T> *> curlist, std::string name) {
    for (typename std::list<SimpleList<T> *>::iterator it = curlist.begin() ; it != curlist.end() ; ++it)
        if (*it.getName() == name)
            return it;
    return nullptr;
}

/*
 * Executes all the instructions from the input file and writing the results in the output file.
 */
void executeInstructions(std::ifstream & input_file, std::ofstream & output_file) {
    std::list<SimpleList<int> *> listSLi;     // all integer stacks and queues
    std::list<SimpleList<double> *> listSLd;  // all double stacks and queues
    std::list<SimpleList<std::string> *> listSLs;  // all string stacks and queues
    
    std::map<char, std::string> types;
    types['d'] = "double";
    types['i'] = "int";
    types['s'] = "std::string";

    std::string buffer;
    while ( std::getline(input_file, buffer) ) {
        output_file << "PROCESSING COMMAND: " << buffer << std::endl;
        
        size_t space1 = buffer.find(' ');
        size_t space2 = buffer.find(' ', space1 + 1);
        std::string command = buffer.substr(0, space1);
        std::string name = buffer.substr(space1 + 1, space2 - space1);
        
        if (name[0] == 'd') 
            SimpleList *currentList = findList<double> (listSLd, name);
        else if (name[0] == 'i')
            SimpleList *currentList = findList<int> (listSLi, name);
        else
            SimpleList *currentList = findList<std::string> (listSLs, name);
        
        if (command == "pop") {
            if (currentList == nullptr)
                output_file << "ERROR: This name does not exist!" << std::endl;
            else
                output_file << "Value popped: " << currentList.pop() << std::endl;
        }
        else {
            std::string value = buffer.substr(space2 + 1);
            if (command == "create") {
                if (currentList == nullptr)
                    for the int kind...
                    SimpleList< type > *pSLi;
                    pSLi = new Stack<int>(listName);
                    listSLi.push_front(pSLi);
                else
                    output_file << "ERROR: This name already exists!" << std::endl;
            }
            else {  //command is a 'push'
                if (currentList == nullptr) 
                    output_file << "ERROR: This name does not exist!" << std::endl;
                else
                    continue;
                    //push value onto stack/queue
            }
        }
    }
}