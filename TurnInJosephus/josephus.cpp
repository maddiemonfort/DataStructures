//
//  main.cpp
//  josephus
//
//  Created by Madeleine Monfort on 9/10/15.
//  Copyright (c) 2015 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include "cll.h"
#include <cstring>

void testCases(CircularLL<std::string>* c);
void testCase2(CircularLL<std::string>* c);
void josephus(int n, int k, CircularLL<int>* c);

int main(int argc, const char * argv[]) {
    //create pointer to Circular Linked list
//    CircularLL<std::string>* c = new CircularLL<std::string>();
//    testCase2(c);
//    //testCases(c);
    CircularLL<int>* c = new CircularLL<int>();
    
    //std::cout << "Number of inputs: ";
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        char opcode;
        std::cin >> opcode;
        switch (opcode) {
            case 'S': {
                //print list in sequence
                c->print();
                break;
            }
            //insert element
            case 'I': {
                //take in element
                int elem;
                std::cin >> elem;
                //take in index
                int index;
                std::cin >> index;
                c->insert(elem, index);
                break;
            }
            //print element
            case 'P': {
                //take in element's index
                int index;
                std::cin >> index;
                c->printElement(index);
                std::cout << std::endl;
                break;
            }
            //delete element
            case 'D': {
                //take in element's index
                int index;
                std::cin >> index;
                c->deleteElem(index);
                break;
            }
            //run josephus program
            case 'J': {
                //take in n & k
                int n;
                std::cin >> n;
                int k;
                std::cin >> k;
                for(int i = 0; i < n; i++) {
                    int elem;
                    std::cin >> elem;
                    c->insert(elem, 0);
                }
                josephus(n, k, c);
                break;
            }
                
            default:
                break;
        }
        
    }
    

    
    return 0;
}

void josephus(int n, int k, CircularLL<int>* c) {
    //loop through c deleting every k element.
    int i = 0;
    int size = n;
    while (size > 1) {
        i = i + k - 1;
        i = i%size;
        //std::cout << i << std::endl;
        c->printElement(i);
        //std::cout << std::endl;
        c->deleteElem(i);
        //c->print();
        size = c->getSize();
    }
    c->print();
    std::cout << std::endl;
}

void testCases(CircularLL<std::string>* c) {
    //inserting into empty list
    c->insert("0", 0);
    c->printElement(0);
    std::cout << std::endl;
    c->print();
    
    //check if circular
    c->insert("1", 1);
    c->insert("2", 2);
    c->insert("3", 3);
    c->print();
    c->checkCircular();
    
    //deleting elements
    c->printElement(2);
    std::cout << std::endl;
    c->deleteElem(2);
    c->print();
    
    
    //deleting element at 0
    c->deleteElem(0);
    c->print();
    
    //deleting element at end
    c->printElement(1);
    std::cout << std::endl;
    c->deleteElem(1);
    c->print();
    
    //insert from newly empty list
    c->printElement(0);
    std::cout << std::endl;
    c->deleteElem(0);
    c->insert("new1", 0);
    c->print();
    
    //inserting elements randomly
    c->insert("new2", 1);
    c->insert("new3", 2);
    c->print();
    c->insert("oddball", 1);
    c->insert("oddball2", 3);
    c->print();
    
    //deleting element looped around cll multiple times
    c->printElement(12);
    std::cout << std::endl;
    c->deleteElem(12);
    c->print();
    
    //inserting elements at 0
    c->insert("new5", 0);
    c->insert("new4", 0);
    c->print();
}

void testCase2(CircularLL<std::string>* c) {
    c->insert("0", 0);
    c->insert("1", 1);
    c->insert("2", 2);
    c->insert("3", 3);
    c->deleteElem(1);
    
    //inserting only at 0 and then deleting at different places, checking loop and deleting at head
    c->insert("4", 0);
    c->insert("5", 0);
    c->insert("6", 0);
    c->insert("7", 0);
    c->insert("8", 0);
    c->print();
    c->printElement(1);
    std::cout << std::endl;
    c->deleteElem(1);
    c->print();
    
    c->printElement(2);
    std::cout << std::endl;
    c->deleteElem(2);
    c->print();
    
    c->printElement(6);
    std::cout << std::endl;
    c->deleteElem(6);
    c->print();
    
    c->printElement(7);
    std::cout << std::endl;
    c->deleteElem(7);
    c->print();
}
