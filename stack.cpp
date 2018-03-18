/*
 * An implementation of a Stack as a polymorphism from a SimpleList class.
 */

#include "stack.h"

/*
 *
 */
template <typename T>
Stack<T>::Stack(const & string input) : SimpleList(input);

/*
 * Pushes an element onto the stack
 */
template <typename T>
SimpleList & Stack<T>::push(const & T) {
    return insertAtEnd(T);
}

/*
 * Pops an element off the stack
 */
template <typename T>
T Stack<T>::pop() {
    return removeFromStart();
}