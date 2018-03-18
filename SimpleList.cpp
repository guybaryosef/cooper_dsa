/*
 * Impementation of the SimpleList abstract class
 */

#include "SimpleList.h"

/*
 * Private nested class Node
 */
template<typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

/*
 * SimpleList constructor
 */
template <typename T>
SimpleList<T>::SimpleList(const std::string & input){
    name = input;
    head = new Node;
    tail = *head;
}

/*
 * Getter function to get the List's name
 */
template <typename T>
std::string SimpleList<T>::getName() {
    return name;
}

/*
 *  Adds a new node at the end of the list
 */
template <typename T>
SimpleList<T> & SimpleList<T>::insertAtEnd(const T & input) {
    tail->next = new Node;
    tail = tail->next;
    tail->data = input;
    return *this;
}

/*
 * Adds a new node at the beginning of the list
 */
template <typename T>
SimpleList<T> & SimpleList<T>::insertAtStart( const T & input) {
    Node* buf = new Node;
    buf->data = input;
    buf->next = head->next;
    head->next = *buf;
    return *this;
}

/*
 * Removes the node at the start of the list
 */
template <typename T>
SimpleList<T> & SimpleList<T>::removeFromStart() {
    if (tail = head)
        return nullptr;
    else {
        Node* buf = *head->next;
        head->next = head->next->next;
        delete(buf);
        return *this;
    }
}
