//
//  main.cpp
//  sparseMatrix
//
//  Created by Madeleine Monfort on 9/24/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include "sparseMatrix.h"
#include "chain.h"

void RegMain();
void testChain(chain<int>* c);
void testRead();

int main(int argc, const char * argv[]) {
    /*chain<int>* c = new chain<int>();
    testChain(c);*/
    
    //testRead();
    
    RegMain();
    return 0;
}


void RegMain() {
    sparseMatrix<int>* a = new sparseMatrix<int>();
    sparseMatrix<bool>* b = new sparseMatrix<bool>();
    sparseMatrix<int>* c = new sparseMatrix<int>();
    
    std::cout << "Reading Matrix A" << std::endl;
    a->read();
    std::cout << "Matrix A:" << std::endl;
    a->print();
    std::cout << "Reading Matrix B" << std::endl;
    b->read();
    std::cout << "Matrix B, the boolean mask matrix:" << std::endl;
    b->print();
    
    //Masking
    a->mask(*b,*c);
    std::cout << "Matrix C, result:" << std::endl;
    c->print();
}

void testChain(chain<int>* c) {
    c->insert(0, 3);
    c->insert(1, 1);
    c->insert(2, 2);
    c->print();
    
    c->erase(1);
    c->print();
    
    c->insert(9, 9);
    c->print();
    c->insert(8, 8);
    c->print();
    
    try {
        c->insert(100, 0);
    }
    catch (char const* e) {
        std::cout << e  << " Columns numbered from 1 to n in an nXn matrix."<< std::endl;
        return;
    }
}

void testRead() {
    sparseMatrix<int>* r = new sparseMatrix<int>();
    std::cout << "Reading Matrix r" << std::endl;
    r->read();
    std::cout << "Matrix r:" << std::endl;
    r->print();
}

//LINEAR TIME! each function should be O(n)