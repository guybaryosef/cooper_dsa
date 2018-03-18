/*
 * Implementation of the Queue Class
 */

#include "queue.h"

/*
 * Constructor, calling the constructor of the base class (SimpleList)
 */
template <typename T>
Queue<T>::Queue(const std::string & input) : SimpleList(input);

/*
 * Pushes onto 
 */
template <typename T>
SimpleList & Queue<T>::push(const T &) {
    return insertAtEnd(T);
}

/*
 * Pops the last element in the queue
 */
template <typename T>
T Queue<T>::pop() {
    return removeFromStart();
}