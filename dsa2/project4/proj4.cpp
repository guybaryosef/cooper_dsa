/*
 * DSA II Programming Assignment 4
 * By: Guy Bar Yosef
 * 
 * Dynamic Programming Assignment

debug: proj4_test.cpp
	$(CC) proj4_test.cpp -g -o debug_dp_project
 */


#include <iostream>
#include <fstream>


#define MAX_STR_LEN 1000


/* matrix declared as global so as not to to overflow the stack */
int dpMat[MAX_STR_LEN+2][MAX_STR_LEN+2];


void preprocess(std::ifstream &input, std::ofstream &output);
void runDP(const std::string &a, const std::string &b, 
                const std::string &c, std::string &response);
void cleanMatrix();

int main() {
    
    std::ifstream input;
    std::ofstream output;
    preprocess(input, output);

    /* run through inputs, solving the dp question */
    std::string str1, str2, merged, response;
    while (input.good()) {
        merged.erase(); response.erase();

        input >> str1 >> str2 >> merged;
        if (!str1.empty() && !str2.empty() && !merged.empty())
            runDP(str1, str2, merged, response);
        output << response << std::endl;
    }
    return 0;
}


/*
 * preprocess - Handles I/O for getting and opening the
 * input and output files of the program.
 */
void preprocess(std::ifstream &input, std::ofstream &output) {
    /* get and open input file */
    std::cout << "Enter name of input file: ";
    
    std::string input_file_name;
    std::cin >> input_file_name;

    input.open(input_file_name);
    while (input.fail()) {
        std::cout << "Invalid file name." << std::endl;
        std::cout << "Please enter the name of a valid input file: " << std::endl;
    
        std::cin >> input_file_name;
        input.open(input_file_name);
    }

    /* get and open output file */
    std::cout << "Enter name of output file: ";
    
    std::string output_file_name;
    std::cin >> output_file_name;

    output.open(output_file_name);
    while (output.fail()) {
        std::cout << "Invalid file name." << std::endl;
        std::cout << "Please enter the name of a valid output file: " << std::endl;
    
        std::cin >> output_file_name;
        output.open(output_file_name);
    }
}


/*
 * cleanMatrix - Sets all the components of the
 * global variable dpMat to zero. 
 */
void clearMatrix() {
    for (int i = 0 ; i < MAX_STR_LEN + 1 ; ++i)
        for (int j = 0 ; j < MAX_STR_LEN + 1 ; ++j)
            dpMat[i][j] = -1;
}


/*
 * runDP - Executes the dynamic programming algorithm
 * to solve the problem.
 */
void runDP(const std::string &a, const std::string &b, 
                const std::string &c, std::string &response) {

    if (a.length() + b.length() != c.length()) {
        response = "*** NOT A MERGE ***";
        return;
    }
    
    clearMatrix();

    if (a[0] == c[0])
        dpMat[0][1] = 0;
    if (b[0] == c[0])
        dpMat[1][0] = 0;
    
    int i,j;
    for (i = 0 ; i < b.length()+1 ; ++i) {
        for (j = 0 ; j < a.length()+1 ; ++j) {
            if (dpMat[i][j] == -1)
                continue;
            else {
                if (c[dpMat[i][j] + 1] == a[j])
                    dpMat[i][j+1] = dpMat[i][j] + 1;
                if (c[dpMat[i][j] + 1] == b[i])
                    dpMat[i+1][j] = dpMat[i][j] + 1;
            }
        }
    }

    if (dpMat[b.length()][a.length()] == -1)
        response = "*** NOT A MERGE ***";
    else {
        response = c;
        int cur_len = c.length() - 2;
        --i; --j;

        while (cur_len >= 0) {
            if ( i > 0 && dpMat[i-1][j] == cur_len)
                --i;
            else {
                response[cur_len+1] = toupper(response[cur_len+1]);
                --j;
            }
            --cur_len;
        }

        if (dpMat[i][j] == cur_len + 1) /* for the first letter */
            response[cur_len+1] = toupper(response[cur_len+1]);
    }
}
