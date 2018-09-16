/*
 * Decleration of the stack and queue classes as polymorphisms of the SimpleList class.
 */

#include "SimpleList.hpp"

/*
 *  Stack definition
 */
#ifndef LIST_STACK
#define LIST_STACK

template <typename T>
class Stack : public SimpleList<T> {
    public:
        //  Stack constructor, calling the SimpleList base class constructor
        Stack(const std::string & input) : SimpleList<T>(input) {}
        
        // Pushes an element onto the stack
        SimpleList<T> & push(const T & input) {
            return this->insertAtStart(input);
        }
        
        // Pops an element off the stack
        T* pop() {
            return this->removeFromStart();
        }
};
#endif


/*
 * Queue definition
 */
#ifndef LIST_QUEUE
#define LIST_QUEUE

template <typename T>
class Queue : public SimpleList<T> {
    public:
        // Constructor, calling the constructor of the base class (SimpleList)
        Queue(const std::string & input) : SimpleList<T>(input) {};
        
        // Pushed onto queue
        SimpleList<T> & push(const T & input) {
            return this->insertAtEnd(input);
        }
        T* pop() {
            return this->removeFromStart();
        }
};
#endif