//
//  sparseMatrix.h
//  sparseMatrix
//
//  Created by Madeleine Monfort on 9/24/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#ifndef sparseMatrix_h
#define sparseMatrix_h
#include "chain.h"

template<class T>
class sparseMatrix {
public:
    //array of chains for rows
    chain<T>* row;
    int rows;
    int columns;
    
//public:
    //constructor
    sparseMatrix<T>() {
        //this->rows = r;
        //this->columns = c;
    }
    
    //destructor
    ~sparseMatrix<T>() {
        delete row;
    }
    
    void read() { //input from stdin
        //creates matrix
        std::cout << "Enter number of rows, columns" << std::endl;
        std::cin >> rows >> columns;
        row = new chain<T>[rows];
        //creating each row
        for(int i = 1; i < (rows+1); i++) {
            row[i] = *new chain<T>();
            std::cout << "Enter number of terms in row "<< i << std::endl;
            int terms;
            std::cin >> terms;
            if (terms != 0 && terms < columns) {
                std::cout << "Enter element's column, and value of each term in row " << i << std::endl;
                //filling in row with non-zero terms
                for (int j = 0; j < terms; j++) {
                    try {
                        T element;
                        int column;
                        std::cin >> column >> element;
                        if(column > columns || column <= 0) { //must be between 1 and columns
                            throw "ERROR: Column does not fit with matrix dimensions. Try again.\n";
                        }
                        row[i].insertByCol(element, column);
                        
                    } catch (char const* e) {
                        std::cout << e;
                        //try reading again
                        j--;
                    }
                }
            }
            if (terms > columns) {
                std::cout << "ERROR: only allowed one element per column. Try again.\n";
                i--; //reset
            }
        }
    }

    void print() {
        //prints out elements of matrix in form shown in project outline
        std::cout << "rows = " << rows << " columns = " << columns << std::endl;
        for(int i = 1; i < (rows+1); i++) {
            std::cout << "row " << i << "[ ";
            try {
                row[i].print();
            } catch (char const* e) {
                std::cout << e;
            }
            
            std::cout << "]" << std::endl;
        }
        std::cout << std::endl;
    }
    
    template<typename T1>
    //masks THIS with b and stores it in sparseMatrix c
    void mask(sparseMatrix<T1> &b, sparseMatrix<T> &c) {
        /*
         c(i,j) = a(i,j) if b(i,j) is true
         c(i,j) = 0 otherwise
         */
        //set up c
        c.rows = this->rows;
        c.columns = this->columns;
        c.row = new chain<T>[c.rows];
        for(int i = 1; i < (c.rows+1); i++) {
            c.row[i] = *new chain<T>();
        }
        
        //to access i and j, must use for loop
        for (int i = 1; i < this->rows+1; i++) {
            try {
                //check if b is empty
                if (b.row[i].getSize() == 0) {
                    throw "";//case where none of b is true
                    
                }
                Node<T>* current = this->row[i].getHead();
                Node<T1>* currentb = b.row[i].getHead();
                //while a still has elements
                while (current != NULL) {
                    if (current->column == currentb->column) {
                        c.row[i].insertByCol(current->element, current->column); //THIS's element and column
                        current = current->next;
                        currentb = currentb->next;
                     }
                     else if (current->column < currentb->column) {
                         //call next function for THIS
                         current = current->next;
                     }
                     else { //aCol > bCol
                         //call next function for b
                         if(currentb->next == NULL) {
                             throw "";
                         }
                         currentb = currentb->next;
                     }
                }
                
                
            } catch (char const* e) {
                //essentially do nothing and move on to next row
            }
        }
    }
};


#endif /* sparseMatrix_h */




