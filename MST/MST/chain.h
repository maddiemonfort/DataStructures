//
//  chain.h
//
//  Created by Madeleine Monfort on 12/1/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#ifndef chain_h
#define chain_h
#include "linearList.h"
#include <sstream>
#include <stdexcept>

template <class T>
struct chainNode
{
    // data members
    T element;
    chainNode<T> *next;
    
    // constructors come here
    chainNode(const T& element) {
        this->element = element;
    }
    
    chainNode(const T& element, chainNode<T>* next) {
        this->element = element;
        this->next = next;
    }

};

template<class T>
class chain : public linearList<T> {
    
protected:
    void checkIndex(int theIndex) const {
        if (theIndex >= listSize || theIndex < 0) {
            throw "This index is out of range.";
        }
    }
    
    chainNode<T>* firstNode;
    int listSize;
    
public:
    // constructors and destructor defined here
    chain(int initialCapacity) { //=10
    // Constructor.
        if (initialCapacity < 1) {
            std::ostringstream s;
            s << "Initial capacity = " << initialCapacity << " Must be > 0";
            throw std::invalid_argument(s.str()); //illegalParameterValue
        }
        firstNode = NULL;
        listSize = 0;
    }
    
    chain() {
        firstNode = NULL;
        listSize = 0;
    }
    
    ~chain(){
        // Chain destructor. Delete all nodes
        // in chain.
        while (firstNode != NULL)
        {// delete firstNode
            chainNode<T>* nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }
    
    // ADT methods
    bool empty() const {return listSize == 0;}
    int size() const {return listSize;}
    
    // other ADT methods defined here
    T& get(int theIndex) const {
        // Return element whose index is theIndex.
        checkIndex(theIndex);
        // move to desired node
        chainNode<T>* currentNode = firstNode;
        for (int i = 0; i < theIndex; i++)
            currentNode = currentNode->next;
        return currentNode->element;
    }
    
    int indexOf(const T& theElement) const {
        // search the chain for theElement
        chainNode<T>* currentNode = firstNode;
        int index = 0;  // index of currentNode
        while (currentNode != NULL && currentNode->element != theElement) {
            // move to next node
            currentNode = currentNode->next;
            index++;
        }
        // make sure we found matching element
        if (currentNode == NULL)
            return -1;
        else
            return index;
    }
    
    void erase(int theIndex) {
        checkIndex(theIndex);
        chainNode<T>* deleteNode;
        if (theIndex == 0) {
            // remove first node from chain
            deleteNode = firstNode;
            firstNode = firstNode->next;
        }
        else {
            // use p to get to beforeNode
            chainNode<T>* p = firstNode;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            
            deleteNode = p->next;
            p->next = p->next->next; 
        }
        listSize--;
        delete deleteNode;
    }
    
    void insert(int theIndex, const T& theElement) {
        if (theIndex < 0 || theIndex > listSize) {
            // Throw illegalIndex exception
            throw "index out of bounds";
        }
        
        if (theIndex == 0)
            // insert at front
            firstNode = new chainNode<T> (theElement, firstNode);
        
        else {
            // find predecessor of new element
            chainNode<T>* p = firstNode;
            for (int i = 0; i < theIndex - 1; i++)
                p = p->next;
            
            // insert after p
            p->next = new chainNode<T>
            (theElement, p->next);
        }
        listSize++;
    }
    
    void insert(const T& theElement) {
        if (listSize == 0) //if empty
            // insert at front
            firstNode = new chainNode<T> (theElement, firstNode);
        
        else {
            // find the end of the list
            chainNode<T>* p = firstNode;
            for (int i = 0; i < listSize - 1; i++)
                p = p->next;
            
            // insert after p
            p->next = new chainNode<T>(theElement, p->next);
        }
        listSize++;
    }
    
    void print() {
        chainNode<T>* currentNode = firstNode;
        for (int i = 0; i < listSize-1; i++) {
            std::cout << currentNode->element << "\n";
            currentNode = currentNode->next;
        }
        std::cout << currentNode->element;
    }
    

};




#endif /* chain_h */
