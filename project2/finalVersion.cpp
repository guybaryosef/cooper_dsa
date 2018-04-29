// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <array>
#include <iterator>

//global vars used for everything
list<Data *>::iterator it;
int bufcount, buf1count, curval;
int i,j;
array<int, 65536> counterArr;
array<int, 65536> counterArr1;

// global vars used for field 1
Data *cur1;
list<Data *>::iterator it1;
list<Data *>::iterator it2;
int val1;

// global vars used for field 2 
array< array< Data *, 60>, 65536> arr2;
array< array< Data *, 60>, 65536> arr3;

// global vars used for field 3
array<int, 127> counterBuf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
array< array<Data *, 15000> , 127> buf;

// global vars used for field 4
array< array< Data *, 500>, 65536> arr;
array< array< Data *, 500>, 65536> arr1;
string val4;


void sortDataList(list<Data *> &l, int field) {
  
  if (field == 1) {
    /* An implementation of insertion sort, because this data is already
       mostly sorted. */

    it1 = l.begin();
    for(it = ++it1 ; it != l.end(); ++it) {
      cur1 = *it;
      val1 = cur1->val1;
      it2 = it;

      while( (*(--it2))->val1 > val1) {
        if (it2 == l.begin()) {
          it1 = it2;
          ++it1;
          *it1 = *it2;
          --it2;
          break;
        }
        else {
          it1 = it2;
          ++it1;
          *it1 = *it2;
        }
      }
      ++it2;
      if (it != it2)
        *it2 = cur1;
    } 
  }
  else if (field == 2) {  
    /* An implementation of radix sort */

    for (i = 0 ; i < 65536 ; ++i) {
      counterArr[i] = 0;
      counterArr1[i] = 0;
    }

    for (it = l.begin(); it != l.end() ; ++it) {
      curval = (*it)->val2 & 0xFFFF ;
      arr2[curval][counterArr[curval]] = *it;
      ++counterArr[curval];
    }

    for (i = 0 ; i < 65536 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = arr2[i][j]->val2 >> 16;
        arr3[curval][counterArr1[curval]] = arr2[i][j];
        ++counterArr1[curval];
      }
    }

    for (i = 0, it = l.begin() ; i < 65536 ; ++i ) {
      bufcount = counterArr1[i];
      for (j = 0 ; j < bufcount ; ++j, ++it)
        *it = arr3[i][j];
    }
  }
  else if (field == 3) {
    /* An implementation of counting sort */
    
    for (it = l.begin(); it != l.end() ; ++it) {
      curval = (*it)->val3;
      buf[curval][counterArr[curval]] = *it;
      ++counterArr[curval];
    }

    for (i = 33, it = l.begin() ; i < 127 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j, ++it)
        *it = buf[i][j];
    }   
  }

  // field equals 4
  else {
    /* An implementation of radix sort */

    for (i = 8481 ; i < 32639 ; ++i) {
      counterArr[i] = 0;
      counterArr1[i] = 0;
    }

    for (it = l.begin(); it != l.end() ; ++it) {
      curval = ((*it)->val4[4] << 8) | (*it)->val4[5];
      arr1[curval][counterArr1[curval]] = *it;
      ++counterArr1[curval];
    }

    for (i = 8481 ; i < 32639 ; ++i ) {
      buf1count = counterArr1[i];
      for (j = 0 ; j < buf1count ; ++j) {
        curval = (arr1[i][j]->val4[2] << 8) | arr1[i][j]->val4[3];
        arr[curval][counterArr[curval]] = arr1[i][j];
        ++counterArr[curval];
      }
      counterArr1[i] = 0;
    }

    for (i = 8481 ; i < 32639 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = (arr[i][j]->val4[0] << 8) | arr[i][j]->val4[1];
        arr1[curval][counterArr1[curval]] = arr[i][j];
        ++counterArr1[curval];
      }
    }

    for (i = 8481, it = l.begin() ; i < 32639 ; ++i ) {
      buf1count = counterArr1[i];
      for (j = 0 ; j < buf1count ; ++j, ++it)
        *it = arr1[i][j];
    }
  }
}
