// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList();// default constructor
  DLList(const DLList<T>& dll); // copy constructor
  DLList(DLList<T>&& dll); // move constructor
  ~DLList(); // destructor
  DLList<T>& operator=(const DLList<T>& dll); // copy assignment operator
  DLList<T>& operator=(DLList<T>&& dll); // move assignment operator
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insert_first(T obj); // insert to the first node
  T remove_first(); // remove the first node
  void insert_last(T obj); // insert to the last node
  T remove_last(); // remove the last node
  void insert_after(DLListNode<T> &p, T obj);
  void insert_before(DLListNode<T> &p, T obj);
  T remove_after(DLListNode<T> &p);
  T remove_before(DLListNode<T> &p);
};

template <typename T>
DLList<T>::DLList(){
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T>::DLList(const DLList<T>& dll){

    if(dll.is_empty()){
        header.next = &trailer;
        trailer.prev = &header;
    }
    else{
        header.next = &trailer;
        trailer.prev = &header;
        DLListNode<T> *firstNode = dll.first_node();
        const DLListNode<T> *lastNode = dll.after_last_node();
        while(firstNode != lastNode){
            insert_last(firstNode->obj);
            firstNode = firstNode->next;
        }
    }     
}

template <typename T>
DLList<T>::DLList(DLList<T>&& dll){
    if(dll.is_empty()){
        header.next = &trailer;
        trailer.prev = &header; 
    }
    else{
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &header;
        trailer.prev->next = &trailer;
        dll.trailer.prev = &dll.header;
        dll.header.next = &dll.trailer;
    }
}

template <typename T>
DLList<T>::~DLList(){
    DLListNode<T> *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll){
    if(&dll != this){
        this->~DLList();
        if(dll.is_empty()){
             DLList();
        }
        else{
            header.next = &trailer;
            trailer.prev = &header;
            DLListNode<T> *copy = dll.first_node();
            const DLListNode<T> *final = dll.after_last_node();
            while(copy != final){
                insert_last(copy->obj);
                copy = copy->next;
            }
        }
    }
    return *this;
}

template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll){
    if (this != &dll){
        if (!this->is_empty()){
            DLListNode<T> *prev_node, *node = header.next;
            while (node != &trailer){
                prev_node = node;
                node = node->next;
                delete prev_node;
            }
            header.next = &trailer;
            trailer.prev = &header;
        }
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;

        dll.header.next->prev = &header;
        trailer.prev->next = &trailer;

        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
    return *this;
}

template <typename T>
T DLList<T>::first() const{  //maybe
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    return header.next->obj;
}

template <typename T>
T DLList<T>::last() const{ //maybe
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    return trailer.prev->obj;
}

template <typename T>
void DLList<T>::insert_first(T obj){ //maybe
    DLListNode<T> *newNode = new DLListNode<T>(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

template <typename T>
T DLList<T>::remove_first(){
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    DLListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    T obj = node->obj;
    delete node;
    return obj;
}

template <typename T>
void DLList<T>::insert_last(T obj){
    DLListNode<T> *newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

template <typename T>
T DLList<T>::remove_last(){
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    else{
        DLListNode<T> *node = trailer.prev;
        node->prev->next = &trailer;
        trailer.prev = node->prev;
        T obj = node->obj;
        delete node;
        return obj;
    }
}

template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj){
    DLListNode<T> *afterNode = p.next;
    DLListNode<T> *insertNode = new DLListNode<T>(obj, &p, afterNode);
    afterNode->prev = insertNode;
    p.next = insertNode;
}

template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj){
    DLListNode<T> *beforeNode = p.prev;
    DLListNode<T> *insertNode = new DLListNode<T>(obj, beforeNode, &p);
    beforeNode->next = insertNode;
    p.prev = insertNode;
}

template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p){
    if (is_empty()) {
        throw "Empty Doubly Linked List";
    }
    else if (header.next == trailer.prev) {
        throw "1 Doubly Linked List";
    }
    else {
        DLListNode<T> *toDel = p.next;
        p.next = p.next->next;
        p.next->prev = &p;
        T toDelValue = toDel->obj;
        delete toDel;
        return toDelValue;
    }
}

template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p){
    if (is_empty()) {
        throw "Empty Doubly Linked List";
    }
    else if (header.next == trailer.prev) {
        throw "1 Doubly Linked List";
    }
    else {
        DLListNode<T> *toDel = p.prev;
        p.prev = p.prev->prev;
        p.prev->next = &p;
        T toDelValue = toDel->obj;
        delete toDel;
        return toDelValue;
    }
}

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll){
  DLListNode<T> *printNode = dll.first_node();
    while(printNode != dll.after_last_node()){
        out << printNode->obj << ", ";
        printNode = printNode->next;
    }
    return out;
}


#endif
