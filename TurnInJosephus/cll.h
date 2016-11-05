//
//  cll.h
//  josephus
//
//  Created by Madeleine Monfort on 9/10/15.
//  Copyright (c) 2015 Madeleine Monfort. All rights reserved.
//

#ifndef josephus_cll_h
#define josephus_cll_h



template <typename T>
class CircularLL {
private:
    struct Node {
        //parts of a node
        Node* next;
        T element;
        Node(T e, Node* n) {
            this->next = n;
            this->element = e;
        }
        
    };
    
    //components of a circular linked list
    Node* headerNode;
    int size;
    bool empty() {
        return size == 0;
    }
    
    
public:
    //functions
    CircularLL<T>() { //constructor
        headerNode = NULL;
        size = 0;
    }
    ~CircularLL<T>() { //destructor
        Node* currentNode = headerNode;
        //delete all the later nodes then delete the head
        for(int i = 0; i < size; i++) {
            Node* tempNode = currentNode->next;
            delete currentNode;
            currentNode = tempNode;
        }
    }
    void insert(T element, int index) {
        if(index > (size + 1)) {
            std::cout << "ERROR: cannot insert there.  List is not that big" << std::endl;
            return;
        }
        if(empty()) {
            headerNode = new Node(element, headerNode);
            size++;
        }
        //inserting at end
        else if(index == size) {
            Node* current = headerNode;
            for(int i = 0; i < (size - 1); i++) {
                current = current->next;
            }
            current->next = new Node(element, headerNode);
            size++;
        }
        //inserting at beginning
        else if(index == 0) {
            Node* temp = headerNode;
            Node* newNode = new Node(element, temp);
            //point last node to this new node
            for (int i = 0; i < (size - 1); i++) {
                temp = temp->next;
            }
            temp->next = newNode;
            headerNode = newNode;
            size++;
        }
        //inserting at any other point
        else {
            Node* current = headerNode;
            for(int i = 0; i < (index-1); i++) {
                current = current->next;
            }
            Node* temp = current->next; //save the next node
            Node* newNode = new Node(element, temp);
            current->next = newNode;
            size++;
        }
    }
    
    void deleteElem(int index) {
        if(empty()) {
            std::cout << "ERROR: Cannot delete from an empty list" <<std::endl;
        }
        else {
            //beginning of iteration of loop
            if(index%size == 0) {
                Node* current = headerNode;
                for(int i = 0; i < (size - 1); i++) {
                    current = current->next;
                }
                Node* temp = headerNode;
                current->next = temp->next;
                temp = NULL;
                delete temp;
                headerNode = current->next;
            }
            else {
                Node* current = headerNode;
                for(int i = 0; i < (index-1); i++) {
                    current = current->next;
                }
                Node* temp = current->next;
                current->next = temp->next;
                temp = NULL;
                delete temp;
            }
        }
            
        size--;
    }
           
    void print() {
        Node* current = headerNode;
        for(int i = 0; i < (size - 1); i++) {
            std::cout << current->element << " ";
            current = current->next;
        }
        std::cout << current->element << std::endl;
    }
    
    void printElement(int index) {
        Node* current = headerNode;
        for(int i = 0; i < index; i++) {
            current = current->next;
        }
        std::cout << current->element << " ";
    }
    
    void checkCircular() {
        Node* current = headerNode;
        for(int i = 0; i < size*3; i++) {
            std::cout << current->element << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    
    int getSize() {
        return size;
    }
    
};

#endif

