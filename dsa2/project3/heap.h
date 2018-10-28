/*
 * DSA II Programming Assignment 3
 * By: Guy Bar Yosef
 * 
 * Heap class definition
 * 
 */


#ifndef _HEAP
#define _HEAP


#include "hash.h"

#include <string>
#include <vector>

using namespace std;


class heap {
    private:
        /* private member class used to implement a heap node */
        struct node {
            public:
                string id;   /* the id this node */
                int key;     /* the key of this node */
                void *pData; /* a pointer to the actual data */
        };

        vector<node> data;  /* the actual binary heap */
        hashTable *mapping; /* maps ids to node pointers */
        int capacity;       /* capacity of heap (constant once object is initialized) */
        int filled;         /* the current size of the heap */

        /* private methods used to implement the public methods */
        void percolateUp(int postCur);
        void percolateDown(int posCur);
        void decidePercolation(int posCur);
        int getPos(node *pn);

    public:
        /* 
         * heap - The constructor allocates space for the nodes of the heap
         * and the mapping (hash table) based on the specified capacity.
         */
        heap(int cap);


        /*
         * heap destructor - frees the dynamically allocated hash table.
         */
        ~heap();


        /* 
         * insert - Inserts a new node into the binary heap
         *
         * Inserts a node with the specified id string, key,
         * and optionally a pointer. They key is used to
         * determine the final position of the new node.
         *
         * Returns:
         *   0 on success
         *   1 if the heap is already filled to capacity
         *   2 if a node with the given id already exists (but the heap
         *     is not filled to capacity)
         */
        int insert(const string &id, const int key, void * const pv = nullptr);


        /*
         * setKey - set the key of the specified node to the specified value
         * This function therefore acts as both 
         * an increaseKey and decreaseKey functions.
         *
         * Returns:
         *   0 on success
         *   1 if a node with the given id does not exist
         */
        int setKey(const string &id, int key);


        /*
         * deleteMin - return the data associated with the smallest key
         *            and delete that node from the binary heap
         *
         * If pId is supplied (i.e., it is not NULL), write to that address
         * the id of the node being deleted. If pKey is supplied, write to
         * that address the key of the node being deleted. If ppData is
         * supplied, write to that address the associated void pointer.
         *
         * Returns:
         *   0 on success
         *   1 if the heap is empty
         */
        int deleteMin(string *pId = nullptr, int *pKey = nullptr, void **ppData = nullptr);


        /*
         * remove - delete the node with the specified id from the binary heap
         *
         * If pKey is supplied, write to that address the key of the node
         * being deleted. If ppData is supplied, write to that address the
         * associated void pointer.
         *
         * Returns:
         *   0 on success
         *   1 if a node with the given id does not exist
         */
        int remove(const string &id, int *pKey = nullptr, void **ppData = nullptr);

};

#endif