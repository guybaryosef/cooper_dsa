/*
 *
 * 
 */
#ifndef LIST_STACK
#define LIST_STACK

#include "SimpleList.h"

template <typename T>
class Stack : public SimpleList<T> {
    public:
        Stack(const std::string &);
        SimpleList<T> & push(const T &);
        T pop();
};

#endif