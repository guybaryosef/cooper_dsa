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
#include <cmath>

#include <iterator>

//global vars used for everything
list<Data *>::iterator it;

// global vars used for field 1
Data *cur1;
list<Data *>::iterator it1;
list<Data *>::iterator it2;
int val1;

// global vars used for field 2
array< array< Data *, 15000>, 256> arr;
array< array< Data *, 15000>, 256> arr1;
array<int, 256> counterArr = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
array<int, 256> counterArr1 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


// global vars used for field 3 & 4
array<int, 127> counterBuf = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
array<int, 127> counterBuf1 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

array< array<Data *, 15000> , 127> buf;
array< array<Data *, 15000> , 127> buf1;
int bufcount, buf1count, curval;
int i,j;
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
      it1 = it;
      if (it1 != it2)
        *it2 = cur1;
    } 
  }
  else if (field == 2) {  
    for (it = l.begin(); it != l.end() ; ++it) {
      curval = (*it)->val2 & 0xFF ;
      arr[curval][counterArr[curval]] = *it;
      ++counterArr[curval];
    }

    for (i = 0 ; i < 256 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = (arr[i][j]->val2 >> 8 )& 0xFF;
        arr1[curval][counterArr1[curval]] = arr[i][j];
        ++counterArr1[curval];
      }
      counterArr[i] = 0;
    }

    for (i = 0 ; i < 256 ; ++i ) {
      buf1count = counterArr1[i];
      for (j = 0 ; j < buf1count ; ++j) {
        curval = (arr1[i][j]->val2 >> 16) & 0xFF;
        arr[curval][counterArr[curval]] = arr1[i][j];
        ++counterArr[curval];
      }
      counterArr1[i] = 0;
    }

    for (i = 0 ; i < 256 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = (arr[i][j]->val2 >> 24) & 0xFF;
        arr1[curval][counterArr1[curval]] = arr[i][j];
        ++counterArr1[curval];
      }
    }

    it = l.begin();
    for (i = 0 ; i < 256 ; ++i ) {
      buf1count = counterArr1[i];
      for (j = 0 ; j < buf1count ; ++j, ++it)
        *it = arr1[i][j];
    }
  }
  else if (field == 3) {
    /* An implementation of counting sort. Look at global vars prior
       to this function to find curval, bufcount, buf, it */
    
    for (it = l.begin(); it != l.end() ; ++it) {
      curval = (int)(*it)->val3;
      buf[curval][counterArr[curval]] = *it;
      ++counterArr[curval];
    }

    it = l.begin();
    for (i = 33 ; i < 127 ; ++i ) {
      bufcount = counterArr[i];
      for (j = 0 ; j < bufcount ; ++j, ++it)
        *it = buf[i][j];
    }   
  }

  // field equals 4
  else {
    for (it = l.begin(); it != l.end() ; ++it) {
      curval = (int)(*it)->val4[4];
      buf1[curval][counterBuf1[curval]] = *it;
      ++counterBuf1[curval];
    }

    for (i = 33 ; i < 127 ; ++i ) {
      buf1count = counterBuf1[i];
      for (j = 0 ; j < buf1count ; ++j) {
        curval = (int)buf1[i][j]->val4[3];
        buf[curval][counterBuf[curval]] = buf1[i][j];
        ++counterBuf[curval];
      }
      counterBuf1[i] = 0;
    }

    for (i = 33 ; i < 127 ; ++i ) {
      bufcount = counterBuf[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = (int)buf[i][j]->val4[2];
        buf1[curval][counterBuf1[curval]] = buf[i][j];
        ++counterBuf1[curval];
      }
      counterBuf[i] = 0;
    }

    for (i = 33 ; i < 127 ; ++i ) {
      buf1count = counterBuf1[i];
      for (j = 0 ; j < buf1count ; ++j) {
        curval = (int)buf1[i][j]->val4[1];
        buf[curval][counterBuf[curval]] = buf1[i][j];
        ++counterBuf[curval];
      }
      counterBuf1[i] = 0;
    }

    for (i = 33 ; i < 127 ; ++i ) {
      bufcount = counterBuf[i];
      for (j = 0 ; j < bufcount ; ++j) {
        curval = (int)buf[i][j]->val4[0];
        buf1[curval][counterBuf1[curval]] = buf[i][j];
        ++counterBuf1[curval];
      }
    }

    it = l.begin();
    for (i = 33 ; i < 127 ; ++i ) {
      buf1count = counterBuf1[i];
      for (j = 0 ; j < buf1count ; ++j, ++it)
        *it = buf1[i][j];
    }

    it1 = l.begin();
    for(it = ++it1 ; it != l.end(); ) {
      cur1 = *it;
      val4 = cur1->val4;
      it2 = it;

      if ((*(--it2))->val4 > val4) {
        do  {
          if (it2 == l.begin())
            break;
          --it2;
        } while ((*it2)->val4 > val4);

        it1 = it++;
        if (it2 != l.begin())
          ++it2;
        l.splice(it2, l, it1);
      }
      else
        ++it;
    } 

  }
  
}
