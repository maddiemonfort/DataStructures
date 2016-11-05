//
//  HBLT.h
//  LPT
//
//  Created by Madeleine Monfort on 11/4/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#ifndef HBLT_h
#define HBLT_h

int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    else {
        return b;
    }
}

template <typename T>
struct HBLTNode {
    T element;
    HBLTNode* L;
    HBLTNode* R;
    int shortPath;
    
    HBLTNode(T e) { //constructor of a single node
        this->element = e;
        this->L = this->R = NULL;
        shortPath = 1; //or is it 0?
    }
    
    HBLTNode(HBLTNode* left, HBLTNode* right, T e) { //constructor including left and right children (trees)
        L = left;
        R = right;
        element = e;
        shortPath = R->shorthPath + 1;
    }
    
};

//MIN Height-Biased Leftist Tree
template <typename T>
class HBLT {
private:
    int numElements;
    //linked implementation
    HBLTNode<T>* root;
    
public:
    HBLT() {
        root = NULL;
        numElements = 0;
    }
    
    ~HBLT() {
        erase(root);
    }
    
    void erase(HBLTNode<T>* r) { //delete left root tree, then right, then root
        if (r->L == NULL && r->R == NULL) { //base case
            delete r;
            r = NULL;
        }
        erase(r->L);
        erase(r->R);
    }
    
    HBLTNode<T>* meld(HBLTNode<T>* &r1, HBLTNode<T>* &r2) { //returns the root of the new melded tree
        //compare the roots
        if (r1->element <= r2->element) {
            //base case
            if (r1->R == NULL) {
                //make r2 the right child of r1
                r1->R = r2;
                //check heights and switch if R height is larger than L height
                if(r1->L == NULL || r1->R->shortPath > r1->L->shortPath) {
                    r1 = swap(r1);
                }
                //if R ==NULL->shortpath = 1;
                if (r1->R == NULL) {
                    r1->shortPath = 1;
                }
                else {
                    r1->shortPath = min(r1->L->shortPath, r1->R->shortPath) + 1;
                }

                return r1;
            }
            
            r1->R = meld(r1->R, r2);
            //fix shortestpath
            if(r1->L == NULL || r1->R->shortPath > r1->L->shortPath) {
                r1 = swap(r1);
            }
            //if R==NULL - shortpath = 1
            if (r1->R == NULL) {
                r1->shortPath = 1;
            }
            else {
                r1->shortPath = r1->R->shortPath + 1;
            }
            
            return r1;
        }
        
        else {
            //base case
            if (r2->R == NULL) {
                //make r1 the right child of r2
                r2->R = r1;
                //check heights
                if (r2->L == NULL || r1->shortPath > r2->L->shortPath) {
                    r2 = swap(r2);
                }
                //update the shortest path
                if(r2->R == NULL) {
                    r2->shortPath = 1;
                }
                else {
                    r2->shortPath = r2->R->shortPath + 1;
                }
                return r2;
            }
            
            r2->R = meld(r1, r2->R);
            //fix shortest path
            if(r2->R->shortPath > r2->L->shortPath) {
                r2 = swap(r2);
            }
            r2->shortPath = min(r2->L->shortPath, r2->R->shortPath) + 1;
            return r2;
        }
        
    }
    
    bool empty() {
        return numElements == 0;
    }
    
    int size() {
        return numElements;
    }
    
    T top() {
        //catch error of empty tree
        if(empty()) {
            throw "Error: Tree is empty. ";
        }
        return root->element;
    }
    
    void push(T element) {
        //empty case
        if(empty()) {
            root = new HBLTNode<T>(element);
        }
        else {
            HBLTNode<T>* n = new HBLTNode<T>(element);
            root = meld(root, n);
        }
        numElements++;
    }
    
    void pop() {
        //empty case
        if (empty()) {
            throw "Error: Cannot pop from empty HBLT. ";
        }
        //single node tree
        if (size() == 1) {
            delete root;
            root = NULL;
        }
        else if (root->R == NULL) {//case for root only having one child!
            //no melding necessary
            HBLTNode<T>* rootL = root->L;
            delete root;
            root = NULL;
            root = rootL;
        }
        else {
            HBLTNode<T>* rootL = root->L;
            HBLTNode<T>* rootR = root->R;
            delete root;
            root = NULL;
            root = meld(rootL, rootR);
        }
        
        numElements--;
    }
    
    HBLTNode<T>* swap(HBLTNode<T>* &r) {
        HBLTNode<T>* temp = r->L;
        r->L = r->R;
        r->R = temp;
        return r;
    }
};

#endif /* HBLT_h */
