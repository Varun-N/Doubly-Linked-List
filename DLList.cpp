// implementation of the DLList class

#include "DLList.h"
#include <iostream>

using namespace std;

DLList::DLList(){
    header.next = &trailer;
    trailer.prev = &header;
}

DLList::DLList(const DLList& dll){

    if(dll.is_empty()){
        header.next = &trailer;
        trailer.prev = &header;
    }
    else{
        header.next = &trailer;
        trailer.prev = &header;
        DLListNode *firstNode = dll.first_node();
        const DLListNode *lastNode = dll.after_last_node();
        while(firstNode != lastNode){
            insert_last(firstNode->obj);
            firstNode = firstNode->next;
        }
    }     
}

DLList::DLList(DLList&& dll){
    if(dll.is_empty()){
        header.next = &trailer;
        trailer.prev = &header; 
    }
    else{
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;
        dll.trailer.prev = &dll.header;
        dll.header.next = &dll.trailer;
    }
}

DLList::~DLList(){
    DLListNode *prev_node, *node = header.next;
    while (node != &trailer) {
        prev_node = node;
        node = node->next;
        delete prev_node;
    }
}

DLList& DLList::operator=(const DLList& dll){
    if(&dll != this){
        this->~DLList();
        if(dll.is_empty()){
             DLList();
        }
        else{
            header.next = &trailer;
            trailer.prev = &header;
            DLListNode *copy = dll.first_node();
            const DLListNode *final = dll.after_last_node();
            while(copy != final){
                insert_last(copy->obj);
                copy = copy->next;
            }
        }
    }
    return *this;
}

DLList& DLList::operator=(DLList&& dll){
    if (this != &dll){
        if (!this->is_empty()){
            DLListNode *prev_node, *node = header.next;
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

DLListNode*  DLList::first_node() const{
    return header.next;
}

const DLListNode* DLList::after_last_node() const{
    return trailer.prev->next;
}

bool DLList::is_empty() const{ //should be correct
    return header.next == &trailer;
}

int DLList::first() const{  //maybe
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    return header.next->obj;
}

int DLList::last() const{ //maybe
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    return trailer.prev->obj;
}

void DLList::insert_first(int obj){ //maybe
    DLListNode *newNode = new DLListNode(obj, &header, header.next);
    header.next->prev = newNode;
    header.next = newNode;
}

int DLList::remove_first(){
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    DLListNode *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    int obj = node->obj;
    delete node;
    return obj;
}

void DLList::insert_last(int obj){
    DLListNode *newNode = new DLListNode(obj, trailer.prev, &trailer);
    trailer.prev->next = newNode;
    trailer.prev = newNode;
}

int DLList::remove_last(){
    if (is_empty()){
        throw "Empty Doubly Linked List";
    }
    else{
        DLListNode *node = trailer.prev;
        node->prev->next = &trailer;
        trailer.prev = node->prev;
        int obj = node->obj;
        delete node;
        return obj;
    }
}

void DLList::insert_after(DLListNode &p, int obj){
    DLListNode *afterNode = p.next;
    DLListNode *insertNode = new DLListNode(obj, &p, afterNode);
    afterNode->prev = insertNode;
    p.next = insertNode;
}

void DLList::insert_before(DLListNode &p, int obj){
    DLListNode *beforeNode = p.prev;
    DLListNode *insertNode = new DLListNode(obj, beforeNode, &p);
    beforeNode->next = insertNode;
    p.prev = insertNode;
}

int DLList::remove_after(DLListNode &p){
    if (is_empty()) {
        throw "Empty Doubly Linked List";
    }
    else if (header.next == trailer.prev) {
        throw "1 Doubly Linked List";
    }
    else {
        DLListNode *toDel = p.next;
        p.next = p.next->next;
        p.next->prev = &p;
        int toDelValue = toDel->obj;
        delete toDel;
        return toDelValue;
    }
}

int DLList::remove_before(DLListNode &p){
    if (is_empty()) {
        throw "Empty Doubly Linked List";
    }
    else if (header.next == trailer.prev) {
        throw "1 Doubly Linked List";
    }
    else {
        DLListNode *toDel = p.prev;
        p.prev = p.prev->prev;
        p.prev->next = &p;
        int toDelValue = toDel->obj;
        delete toDel;
        return toDelValue;
    }
}

ostream& operator<<(ostream& out, const DLList& dll){
    DLListNode *printNode = dll.first_node();
    while(printNode != dll.after_last_node()){
        out << printNode->obj << ", ";
        printNode = printNode->next;
    }
    return out;
}