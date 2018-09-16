/*
 * DSA II: Programming Assignment #1
 * By: Guy Bar Yosef
 * 
 * Implementation file for 'hash.h' and the hashTable class 
 * 
 */


#include "hash.h"

#include <vector>
#include <string>


/*
 * hashTable class constructor.
 * Uses getPrime to choose a prime number at least as large as
 * the specified size for the initial size of the hash table.
 */
hashTable::hashTable(int size) : filled(0) {
    capacity = getPrime(size);
    data.resize(capacity);
}


/* 
 * Insert the specified key into the hash table.
 * If an optional pointer is provided,
 * associate that pointer with the key.
 * Returns 0 on success,
 * 1 if key already exists in hash table,
 * 2 if rehash fails.
 */
int hashTable::insert(const std::string &key, void *pv) {

    if (findPos(key) != -1)
        return 1;
    
    int index = hash(key);

    while (data[index].isOccupied) 
        index = hash2(key, index);
    
    data[index].key = key;
    data[index].isOccupied = true;
    data[index].pv = pv;

    ++filled;
    if (filled > capacity/2)
        if (!rehash())
            return 2;
    
    return 0;
}


/*
 * Check if the specified key is in the hash table.
 * If so, return true; otherwise, return false.
 */
bool hashTable::contains(const std::string &key) {
    return (findPos(key) == -1) ? false : true;
}


/*
 * Get the pointer associated with the specified key.
 * If the key does not exist in the hash table, return NULL.
 * If an optional pointer to a bool is provided,
 * set the bool to true if the key is in the hash table,
 * and set the bool to false otherwise.
 */
void * hashTable::getPointer(const std::string &key, bool *b) {
    
    int index;
    if ((index = findPos(key)) == -1) {
        if (b != NULL)
            *b = false;
        return NULL;
    }
    else {
        if (b != NULL)
            *b = true;
    }
    return data[index].pv;
}


/*
 * Set the pointer associated with the specified key.
 * Returns 0 on success,
 * 1 if the key does not exist in the hash table.
 */
int hashTable::setPointer(const std::string &key, void *pv) {
    
    int index;
    if ((index = findPos(key)) == -1)
        return 1;

    data[index].pv = pv;
    return 0;
}


/*
 * Delete the item with the specified key.
 * Returns true on success,
 * false if the specified key is not in the hash table.
 */
bool hashTable::remove(const std::string &key) {
    int index;
    if ((index = findPos(key)) == -1)
        return false;
    
    data[index].isDeleted = true;
    return true;
}


/*
 * The first hash function, as implemented in 
 * 'Data Structures and Algorithm Analysis in C++' 3rd Ed, by Mark Allen Weiss.
 */
int hashTable::hash(const std::string &key) {
    int hashVal = 0;

    for (int i = 0 ;i < key.length() ; ++i)
        hashVal = 37*hashVal + key[i];

    hashVal %= capacity;
    if (hashVal < 0)
        hashVal += capacity;

    return hashVal;
}

#include <iostream>
/*
 * The second hash function, which is used
 * to deal with double hashing.
 */
int hashTable::hash2(const std::string &key, const int index) {
    int hashVal = 0;

    for (int i = 0 ;i < key.length() ; ++i)
        hashVal = index*719*hashVal + key[i];

    hashVal %= capacity;
    if (hashVal < 0)
        hashVal += capacity;

    if (hashVal == index)   // make sure we get a new hash value
        hashVal = (hashVal*index) % capacity;

    return hashVal;
}


/* 
 * Search for an item with the inputted 'key'.
 * Return the position if found, -1 otherwise.
 * The choice of a collision resolution will be double hashing.
 */
int hashTable::findPos(const std::string &key) {
    int index = hash(key);

    while (data[index].isOccupied) {
        if (data[index].key == key)
            return index;
        index = hash2(key, index);
    }
    return -1;
}


/* 
 * The rehash function; makes the hash table bigger.
 * Returns true on success, false if memory allocation fails.
 */
bool hashTable::rehash() {
    std::vector<hashItem> temp;
    try {
        temp.resize(getPrime(capacity+1));
    }
    catch(...) {
        return false;
    }

    for (auto item : data) {
        if (item.isOccupied && !item.isDeleted) {
            
            int index = hash(item.key);
            while (temp[index].isOccupied) 
                index = hash2(item.key, index);
            
            temp[index] = item;
        }
    }
    data = temp;
    return true;
}


/*
 * Returns a prime number at least as large as the input 'size'.
 * Uses a precomputed sequence of selected prime numbers.
 */
unsigned int hashTable::getPrime(int size) {
    const int primes[] = {98317, 196613, 393241, 786433, 1572869, 3145739,
                    6291469, 12582917, 25165843, 50331653, 100663319};

    for (int i = 0 ; i < 8 ; ++i)
        if (size < primes[i])
            return primes[i];

    // if size is larger than the first 8 primes of list, return largest possible hash table size
    return primes[9]; 
}
