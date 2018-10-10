/*
 * DSA II Programming Assignment #2
 * By: Guy Bar Yosef
 * 
 * Implementation file for 'heap.h' and its heap class 
 * 
 */


#include "heap.h"

#include <string>


/* 
 * heap - The constructor allocates space for the nodes of the heap
 * and the mapping (hash table) based on the specified capacity.
 */
heap::heap(int cap) : capacity(cap+1), filled(1) {
    data.resize(cap+1); // 0th index will not be used for implementational reasons
    mapping = new hashTable(cap*2);
}


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
int heap::insert(const string &id, int key, void *pv) {
    if (filled == capacity)
        return 1;
    else if (mapping->contains(id))
        return 2;

    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    if (mapping->insert(id, &data[filled]) != 0)
        throw "Unable to insert node to hashTable";

    percolateUp(filled);
    ++filled;

    return 0;
}


/*
 * setKey - set the key of the specified node to the specified value
 * This function therefore acts as both 
 * an increaseKey and decreaseKey functions.
 *
 * Returns:
 *   0 on success
 *   1 if a node with the given id does not exist
 */
int heap::setKey(const string &id, int key) {
    node *pn;
    if (!(pn = static_cast<node *> (mapping->getPointer(id))))
        return 1;
    
    int cur_i = getPos(pn); /* index of the specified node */
    data[cur_i].key = key;
    
    decidePercolation(cur_i);

    return 0;
}


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
int heap::deleteMin(string *pId, int *pKey, void *ppData) {
    if (filled == 1) /* empty heap */
        return 1;
    
    if (pId)
        *pId = data[1].id;
    
    if (pKey)
        *pKey = data[1].key;

    if (ppData)
        ppData = data[1].pData;

    mapping->remove(data[1].id);
    data[1] = data[filled-1];
    --filled;

    percolateDown(1);

    return 0;
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
int heap::remove(const string &id, int *pKey, void *ppData) {
    node *pn;
    if (!(pn = static_cast<node *> (mapping->getPointer(id))))
        return 1;
    
    if (!mapping->remove(id))
        throw "Unable to remove key.";

    int cur_i = getPos(pn); /* index of the node that will be removed */

    if (pKey)
        *pKey = data[cur_i].key;
    if (ppData)
        ppData = data[cur_i].pData;

    data[cur_i] = data[filled];
    
    --filled;
    decidePercolation(cur_i);
    
    return 0;
}


/*
 * Given an inital node index in the heap, this function
 * percolates up, so as to maintain the heap order property.
 * This function does not return anything.
 */
void heap::percolateUp(int posCur) {
    if (posCur == 1 || data[posCur].key >= data[posCur/2].key)
        return;

    node hole = data[posCur];
    do  {
        data[posCur] = data[posCur/2];
        mapping->setPointer(data[posCur].id, &data[posCur]);
        
        posCur /= 2;
    } while (posCur != 1 && hole.key < data[posCur/2].key);
    
    data[posCur] = hole;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}


/*
 * Given an inital node index in the heap, this function
 * percolates down, so as to maintain the heap order property.
 * This function does not return anything.
 */
void heap::percolateDown(int posCur) {

    int min_child; /* the index of the child of the node indexed by posCur with the smaller key */
    if (posCur*2 + 1 < filled)
        min_child = (data[posCur*2].key < data[posCur*2 + 1].key) ? posCur*2 : posCur*2 + 1;
    else if (posCur*2 < filled)
        min_child = posCur*2;
    else  /* posCur is a leaf */
        return;
    
    if (data[min_child].key >= data[posCur].key)
        return;

    node hole = data[posCur];
    do {
        data[posCur] = data[min_child];
        mapping->setPointer(data[posCur].id, &data[posCur]);

        posCur = min_child;

        if (posCur*2 + 1 < filled)
            min_child = (data[posCur*2].key < data[posCur*2 + 1].key) ? posCur*2 : posCur*2 + 1;
        else if (posCur*2 < filled)
            min_child = posCur*2;
        else  /* posCur is a leaf */
            break;
    } while (hole.key > data[min_child].key);

    data[posCur] = hole;
    mapping->setPointer(data[posCur].id, &data[posCur]);
}

/* 
 * Decides whether to percolate up or down.
 * As there are error checking for each, it calls both
 * and at most one will do any percolating.
 * This function returns nothing.
 */
void heap::decidePercolation(int posCur) {
    percolateUp(posCur);
    percolateDown(posCur);
}


/* 
 * Gets and returns the position (index) in the heap 
 * of the node pointed to by pn.
 */
int heap::getPos(node *pn) {
    return pn - &data[0];
}