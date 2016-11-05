//
//  UnionFind.h
//  MST
//
//  Created by Madeleine Monfort on 12/12/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#ifndef UnionFind_h
#define UnionFind_h
class UnionFind {
    //data
private:
    int* datarr; //data array
    int size;
    int* sarr; //size array
    
public:
    //constructor
    UnionFind(int size) {
        this->size = size;
        datarr = new int[size];
        sarr = new int[size];
        //initialize arrays
        for(int i = 0; i < size; i++) {
            datarr[i] = i;
            sarr[i] = 1; //all only have 1 node, the head
        }
    }
    
    //destructor
    ~UnionFind() {
        delete datarr;
        delete sarr;
    }
    
    //find operation
    int find(int x){
        return datarr[x];
    }
    
    //weighted quick-union operation
    void Union(int x, int y) {
        int headx;
        int heady;
        for(headx = x; headx != datarr[headx]; headx = datarr[headx]) {
            datarr[headx] = datarr[datarr[headx]];
        } //find the head of the tree where x is found and compress path
        for(heady = y; heady != datarr[heady]; heady = datarr[heady]){
            datarr[heady] = datarr[datarr[heady]];
        } //find head of tree where y is found and compress path
        
        //connect smaller tree to head of larger tree
        if(sarr[headx] < sarr[heady]) { //if tree x is smaller than tree y
            datarr[headx] = heady;
            sarr[heady] += sarr[headx];
        }
        else { //if tree x is larger than tree y
            datarr[heady] = headx;
            sarr[headx] += sarr[heady];
        }
        
    }
    
    //returns whether a pair of numbers is connected or not
    bool connected(int x, int y){
        int headx;
        int heady;
        
        //find roots of trees
        for(headx = x; headx != datarr[headx]; headx = datarr[headx]); //find the head of the tree where x is found
        for(heady = y; heady != datarr[heady]; heady = datarr[heady]); //find head of tree where y is found
        
        //if roots are same
        if(headx == heady) {
            return true;
        }
        else return false;
    }
    
};

#endif /* UnionFind_h */
