/*
 * The functions used in project1.
 */

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include "SimpleList.hpp"
#include "QueueStack.hpp"

std::ifstream read_file();
std::ofstream write_file();
template<typename T> SimpleList<T>* findList(std::string name);
void executeInstructions(std::ifstream & input_file, std::ofstream & output_file);


/*
 * Opens a file to read in instructions from.
 */
std::ifstream read_file() {
    std::string input;
    std::cout << "Please enter a file to read in from: " << std::endl;
    std::cin >> input;
    std::ifstream input_file(input);
    return input_file;
}


/*
 * Opens a file to write into (will overwrite previous data). 
 * If the inputted file name does not exist, the function will create a new file with the inputted name.
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
SimpleList<T>* findList( std::list< SimpleList<T>* > & curlist, const std::string name) {
    for (typename std::list< SimpleList<T>* >::iterator it = curlist.begin() ; it != curlist.end() ; ++it)
        if ( ((*it)->getName()).substr(0, name.length()) == name) 
            return *it;
    return nullptr;
}


/*
 * Executes all the instructions from the input_file and writes all results to the output_file.
 */
void executeInstructions(std::ifstream & input_file, std::ofstream & output_file) {
    std::list< SimpleList<int>* >         listSLi;  // all integer stacks and queues
    std::list< SimpleList<double>* >      listSLd;  // all double stacks and queues
    std::list< SimpleList<std::string>* > listSLs;  // all string stacks and queues

    std::string buffer;
    while ( std::getline(input_file, buffer) ) {    // will go through input file line by line
        output_file << "PROCESSING COMMAND: " << buffer << std::endl;
        
        size_t space1 = buffer.find(' ');
        size_t space2 = buffer.find(' ', space1 + 1);
        std::string command = buffer.substr(0, space1);
        std::string name = buffer.substr(space1 + 1, space2 - space1);
        
        // if the command deals with a double data type
        if (name[0] == 'd')  {     
            // find if the given name of a Stack/Queue already exists.
            SimpleList<double>* currentList = findList<double> (listSLd, name);

            if (command == "pop") {
                if (currentList) {
                    double *value = currentList->pop();
                    if (value)
                        output_file << "Value popped: " << *value << std::endl;
                    else
                        output_file << "ERROR: This list is empty!" << std::endl;
                    delete(value);
                }
                else
                    output_file << "ERROR: This name does not exist!" << std::endl;
            }
            // if the command is either create or push
            else {
                std::string value = buffer.substr(space2 + 1);

                if (command == "create") {
                    if (currentList) 
                        output_file << "ERROR: This name already exists!" << std::endl;
                    else {
                        SimpleList< double >* newlist;
                        if (value == "stack")
                            newlist = new Stack<double>(name);
                        else
                            newlist = new Queue<double>(name);
                        listSLd.push_back(newlist);
                    }                       
                }
                //command is a 'push'
                else {  
                    if (currentList)
                        currentList->push( stod(value) );
                    else
                        output_file << "ERROR: This name does not exist!" << std::endl;
                }
            }
        }

        // integer data type
        else if (name[0] == 'i')   {  
            // find if the given name of a Stack/Queue already exists.
            SimpleList<int>* currentList = findList<int> (listSLi, name);

            if (command == "pop") {
                if (currentList) {
                    int *value = currentList->pop();
                    if (value)
                        output_file << "Value popped: " << *value << std::endl;
                    else
                        output_file << "ERROR: This list is empty!" << std::endl;
                    delete(value);
                }
                else 
                    output_file << "ERROR: This name does not exist!" << std::endl;
            }
            // if the command is either create or push
            else {
                std::string value = buffer.substr(space2 + 1);

                if (command == "create") {
                    if (currentList)
                        output_file << "ERROR: This name already exists!" << std::endl;
                    else {
                        SimpleList< int >* newlist;
                        if (value == "stack")
                            newlist = new Stack<int> (name);
                        else
                            newlist = new Queue<int> (name);
                        listSLi.push_back(newlist);
                    }
                }
                //command is a 'push'
                else {  
                    if (currentList)
                        currentList->push( stoi(value) );
                    else
                        output_file << "ERROR: This name does not exist!" << std::endl;
                }
            }
        }

        // string datatype
        else  {  
            // find if the given name of a Stack/Queue already exists.
            SimpleList<std::string>* currentList = findList<std::string> (listSLs, name);

            if (command == "pop") {
                if (currentList){
                    std::string *value = currentList->pop();
                    if (value)
                        output_file << "Value popped: " << *value << std::endl;
                    else
                        output_file << "ERROR: This list is empty!" << std::endl;
                    delete(value);
                }
                else
                    output_file << "ERROR: This name does not exist!" << std::endl;
            }
            // if the command is either create or push
            else {
                std::string value = buffer.substr(space2 + 1);

                if (command == "create") {
                    if (currentList) 
                        output_file << "ERROR: This name already exists!" << std::endl;
                    else {
                        SimpleList< std::string >* newlist;
                        if (value == "stack")
                            newlist = new Stack<std::string>(name);
                        else
                            newlist = new Queue<std::string>(name);
                        listSLs.push_back(newlist);
                    }
                }
                //command is a 'push'
                else {  
                    if (currentList)
                        currentList->push(value);
                    else
                        output_file << "ERROR: This name does not exist!" << std::endl;
                }     
            }
        }
    }
    // Free the allocated memories of all stacks and queues
    for (std::list< SimpleList<int>* >::iterator it = listSLi.begin() ; it != listSLi.end() ; ++it)
        delete(*it);
    for (std::list< SimpleList<double>* >::iterator it = listSLd.begin() ; it != listSLd.end() ; ++it)
        delete(*it);
    for (std::list< SimpleList<std::string>* >::iterator it = listSLs.begin() ; it != listSLs.end() ; ++it)
        delete(*it);
}