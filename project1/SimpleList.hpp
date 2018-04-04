/*
 * Header file for SimpleList abstract class.
 */

#ifndef SIMPLE_LIST
#define SIMPLE_LIST

#include <string>


/*
 * The definition of the abstract SimpleList class
 */
template <typename T>
class SimpleList {
        struct Node {
            T data;
            Node* next = nullptr;
        };
        std::string name;
        Node* head;
        Node* tail;

    protected:
        //Adds a new node at the end of the list
        SimpleList<T> & insertAtEnd(const T & input) {
            tail->next = new Node;
            tail = tail->next;
            tail->data = input;
            return *this;
        }

        //Adds a new node at the beginning of the list
        SimpleList<T> & insertAtStart( const T & input) {
            Node* buf = new Node;
            buf->data = input;
            buf->next = head->next;
            head->next = buf;
            if (head == tail)
                tail = buf;
            return *this;
        }

        // Removes the node at the start of the list
        T* removeFromStart() {
            if (tail == head) {
                return nullptr;     // the list is empty
            }   
            else {
                Node* buf = head->next;
                if (tail == head->next) {
                    tail = head;
                    head->next = nullptr;
                }
                else
                    head->next = head->next->next;
                T* output = new T;
                *output = buf->data;
                delete(buf);
                return output;
            }

    public:
        // Constructor allocates memory for a sentinel head node
        SimpleList(const std::string & input){
            name = input;
            head = new Node;
            tail = head;
        }
        
        // Destructor frees all allocated memory in the class
        virtual ~SimpleList(){
            Node* buffer1 = head;
            Node* buffer2 = head->next;
            while (buffer2) {
                delete(buffer1);
                buffer1 = buffer2;
                buffer2 = buffer2->next;
            }
            delete(buffer1);
        } 

        // Returnns the 'name' member variable
        std::string getName() {
            return name;
        }

        virtual SimpleList & push(const T &) = 0;
        virtual T* pop() = 0;
};

#endif