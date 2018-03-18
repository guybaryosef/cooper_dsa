/*
 * An implementation of a Queue as a polymorphism from a SimpleList class.
 */
#ifndef LIST_QUEUE
#define LIST_QUEUE

#include "SimpleList.h"

template <typename T>
class Queue : public SimpleList<T> {
    public:
        Queue(const std::string &);
        SimpleList<T> & push(const T &);
        T pop();
};

#endif