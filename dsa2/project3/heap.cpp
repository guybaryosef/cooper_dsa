/*
 * DSA II Programming Assignment 3
 * By: Guy Bar Yosef
 * 
 * Heap class Implementation
 * 
 */


#include "heap.h"

#include <string>


/* 
 * heap - The constructor allocates space for the nodes of the heap
 * and the mapping (hash table) based on the specified capacity.
 */
heap::heap(int cap) : capacity(cap+1), filled(1) {
     /* 0th index will not be used for implementational reasons */
    data.resize(cap+1);
    mapping = new hashTable(cap*2);
}


/*
 * heap destructor - frees the dynamically allocated hash table.
 */
heap::~heap() {
    delete mapping;
}


/* 
 * insert - Inserts a new node into the binary heap.
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
int heap::insert(const string &id, const int key,  void * const pv) {
    if (filled == capacity)
        return 1;
    else if (mapping->contains(id))
        return 2;

    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    
    if (mapping->insert(id, &data[filled]) != 0)
        throw "Error in hashtable rehash.";

    percolateUp(filled);
    ++filled;

    return 0;
}


/*
 * setKey - set the key of the specified node to the specified value.
 * This function therefore acts as both 
 * an increaseKey and decreaseKey functions.
 *
 * Returns:
 *   0 on success
 *   1 if a node with the given id does not exist
 */
int heap::setKey(const string &id, int key) {
    node *pn; /* pointer to node whose key we will update */
    if (!(pn = static_cast<node *> (mapping->getPointer(id))))
        return 1;
    
    int curPos = getPos(pn); /* index of the specified node */
    data[curPos].key = key;
    
    decidePercolation(curPos);

    return 0;
}


/*
 * deleteMin - return the data associated with the smallest key
 *            and delete that node from the binary heap.
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
int heap::deleteMin(string *pId, int *pKey, void **ppData) {
    if (filled < 2) /* empty heap */
        return 1;
    
    if (pId)
        *pId = data[1].id;

    return remove(data[1].id, pKey, ppData);
}


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
int heap::remove(const string &id, int *pKey, void **ppData) {
    node *pn;  /* pointer to node that will be removed */
    if (!(pn = static_cast<node *> (mapping->getPointer(id))))
        return 1;
    
    if (!mapping->remove(id))
        throw "Unable to remove key from private hash table.";

    int curPos = getPos(pn); /* index of the node that will be removed */

    if (pKey)
        *pKey = data[curPos].key;
    if (ppData)
        *ppData = data[curPos].pData;
    
    --filled;
    if (curPos != filled && filled > 1) {
        data[curPos] = data[filled];
        mapping->setPointer(data[curPos].id, &data[curPos]);

        decidePercolation(curPos);
    }
    return 0;
}


/*
 * Given an inital node index in the heap, this function
 * percolates up, so as to maintain the heap order property.
 * This function does not return anything.
 */
void heap::percolateUp(int curPos) {

    /* error check if we need to do upward perculation */
    if (curPos == 1 || data[curPos].key >= data[curPos/2].key)
        return;

    /* perculate up using a hole, updating hash table each time */
    node hole = data[curPos];
    do  {
        data[curPos] = data[curPos/2];
        mapping->setPointer(data[curPos].id, &data[curPos]);
        
        curPos /= 2;
    } while (curPos != 1 && hole.key < data[curPos/2].key);
    
    /* replace hole with actual node at end of perculation */
    data[curPos] = hole;
    mapping->setPointer(data[curPos].id, &data[curPos]);
}


/*
 * Given an inital node index in the heap, this function
 * percolates down, so as to maintain the heap order property.
 * This function does not return anything.
 */
void heap::percolateDown(int curPos) {

    /* the index of the child with the smaller key, of node indexed by curPos */
    int min_child; 

    /* error check to see if we need downward perculation */
    if (2*curPos+1 < filled)
        min_child = (data[2*curPos].key < data[2*curPos+1].key) ? 2*curPos : 2*curPos+1;
    else if (2*curPos < filled)
        min_child = curPos*2;
    else  /* curPos is a leaf */
        return;
    
    if (data[min_child].key >= data[curPos].key)
        return;

    /* downward perculation using a hole, updating the hash table each time */
    node hole = data[curPos]; 
    do {
        data[curPos] = data[min_child];
        mapping->setPointer(data[curPos].id, &data[curPos]);

        curPos = min_child;

        if (2*curPos+1 < filled)
            min_child = (data[2*curPos].key < data[2*curPos+1].key) ? 2*curPos : 2*curPos+1;
        else if (2*curPos < filled)
            min_child = curPos*2;
        else  /* curPos is a leaf */
            break;
    } while (hole.key > data[min_child].key);

    /* replace hole with actual node at end of perculation */
    data[curPos] = hole;
    mapping->setPointer(data[curPos].id, &data[curPos]);
}

/* 
 * Decides whether to percolate up or down.
 * As there are error checking for each, it calls both
 * and at most one will do any actual percolating.
 * This function returns nothing.
 */
void heap::decidePercolation(int curPos) {
    percolateUp(curPos);
    percolateDown(curPos);
}


/* 
 * Gets and returns the position (index) in the heap 
 * of the node pointed to by pn.
 */
int heap::getPos(node *pn) {
    return pn - &data[0];
}