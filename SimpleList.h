/*
 *  Header file for SimpleList abstract class
 */

#ifndef SIMPLE_LIST
#define SIMPLE_LIST

#include <string>

/*
 * The decleration of the SimpleList class using templating
 */
template <typename T>
class SimpleList {
        struct Node;
        std::string name;
        Node* head;
        Node* tail;

    protected:
        SimpleList<T> & insertAtEnd(const T &);
        SimpleList<T> & insertAtStart(const T &);
        SimpleList<T> & removeFromStart();

    public:
        SimpleList(const std::string &);

        virtual SimpleList & push(const T &) = 0;
        virtual T pop() = 0;

        std::string getName();
};

#endif