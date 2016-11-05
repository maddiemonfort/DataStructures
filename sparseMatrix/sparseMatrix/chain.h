//
//  chain.h
//  sparseMatrix
//
//  Created by Madeleine Monfort on 9/28/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

/*
 NOTE: all functions must be O(n)
*/

#ifndef chain_h
#define chain_h

template<typename T>
struct Node{
    T element;
    int column;
    Node* next;
    Node(T e, int c, Node* n) {
        this->element = e;
        this->column = c;
        this->next = n;
    }
};

template<typename T>
class chain {
private:
    int size = 0;
    Node<T>* head = NULL;
    //initialized in case constructor not called
    
    bool empty() {
        return size == 0;
    }
    
public:
    chain<T>() {
        this->head = NULL;
        this->size = 0;
    }
    
    ~chain<T>() {
        Node<T>* currentNode = head;
        //delete all the later nodes then delete the head
        for(int i = 0; i < size; i++) {
            Node<T>* tempNode = currentNode->next;
            delete currentNode;
            currentNode = tempNode;
        }
    }
    
    void insertByCol(T element, int col) {
        //inserting to empty list
        if(empty()) {
            head = new Node<T>(element, col, NULL);
            size++;
        }
        //inserting at beginning
        else if(col == 1) {
            Node<T>* temp = head;
            Node<T>* newNode = new Node<T>(element, col, temp);
            head = newNode;
            size++;
        }
        //inserting at any other point ordered by column number
        else {
            Node<T>* current = head;
            Node<T>* previous = NULL;
            while (current->column < (col-1) && current->next != NULL) {
                previous = current;
                current = current->next;
            }
            if (current->column > col) { //accounting for off by one error
                current = previous;
            }
            Node<T>* temp = current->next; //save the next node
            Node<T>* newNode = new Node<T>(element, col, temp);
            current->next = newNode;
            size++;
        }
    }
    
    void print() {
        if (empty()) {
            throw "";
        }
        Node<T>* current = head;
        for(int i = 0; i < (size - 1); i++) {
            std::cout << "col:" << current->column << " val= " << current->element << ", ";
            current = current->next;
        }
        std::cout << "col:" << current->column << " val= " << current->element;
    }
    
    //helper functions
    
    int getSize() {
        return size;
    }
    
    Node<T>* getHead() {
        return head;
    }
    
    
//*************************************************************************************************
    //These functions not in use in sparseMatrix.
    
    //function not necessary--> issues inherent with sparseMatrix implementation not dealt with
    void erase(int column) {
        if(empty()) {
            throw "ERROR: Cannot delete from an empty list";
        }
        
        else {
            Node<T>* current = head;
            for(int i = 0; i < (column-1); i++) {  //not accurate if all columns not filled.  will reach NULL values
                current = current->next;
            }
            Node<T>* temp = current->next;
            current->next = temp->next;
            temp = NULL;
            delete temp;
        }
        
        size--;
    }
    
    //Extra function for different kind of insertion
    void insert(T element, int col) {
        Node<T>* next = head;
        Node<T>* newNode = new Node<T>(element, col, next);
        head = newNode;
        size++;
    }
    
    
};


#endif /* chain_h */
