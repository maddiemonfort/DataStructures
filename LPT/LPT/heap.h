//
//  heap.h
//  LPT
//
//  Created by Madeleine Monfort on 11/4/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#ifndef heap_h
#define heap_h
template <class T>
class heap {
private:
    int numElements;
    int capacity;
    //array implementation
    T* heapArr;
    bool isMin;
    
public:
    heap(int c, bool m) {
        this->capacity = c;
        this->isMin = m;
        heapArr = new T[capacity];
        numElements = 0;
    }
    
    ~heap() {
        delete heapArr;
    }
    
    bool empty() {
        return numElements == 0;
    }
    
    int size() {
        return numElements;
    }
    
    void push(T element) {
        //error checking:
        
        //if inserting into empty heap
        if (empty()) {
            heapArr[1] = element;
        }
        //insert element
        else {
            heapArr[numElements+1] = element;
            //then reOrder according to min/max-ness
            reOrderPush(numElements+1, (numElements+1)/2);
        }
        numElements++;
    }
    
    T top() {
        //get top of tree, or root.  should be in the first position
        return heapArr[1];
    }
    
    void pop() {
        //check if empty
        if (empty()) {
            throw "Cannot pop from an empty heap.";
        }
        //remove top element by replacing with bottom element
        heapArr[1] = heapArr[numElements];
        numElements--;
        
        //travel down tree to reOrder
        int parent = 1;
        int child = 2;
        while (child <= numElements) {
            if(isMin) { //min tree
                //get smaller of two children
                if(child < numElements && heapArr[child] > heapArr[child+1]) {
                    child++;
                }
                //reOrder
                if (heapArr[child] < heapArr[parent]) {
                    swap(child, parent);
                }
                
            }
            else { //max tree
                //get larger of two children
                if(child < numElements && heapArr[child] < heapArr[child+1]) {
                    child++;
                }
                //reOrder
                if (heapArr[child] > heapArr[parent]) {
                    swap(child,parent);
                }
            }
            parent = child;
            child = child*2;
        }
    }
    
    void swap(int i, int j) { //input indices of elements to swap
        T temp = heapArr[i];
        heapArr[i] = heapArr[j];
        heapArr[j] = temp;
    }
    
    void reOrderPush(int child, int parent) { //input indices of parent and child
        //recursive function
        if (parent == 0) { //base case
            return; //forces it to act "iteratively"
        }
        
        //check whether min or max
        if(isMin) { //min tree
            if (heapArr[child] < heapArr[parent]) {
                swap(child, parent);
                reOrderPush(parent, parent/2); //do same for parent and grandparent
            }
        }
        else { //max tree
            if (heapArr[child] > heapArr[parent]) {
                swap(child,parent);
                reOrderPush(parent, parent/2); //do the same for the parent and grandparent
            }
        }
    }
    
    void print() {
        for (int i = 0; i < numElements+1; i++) {
            std::cout << heapArr[i] << " ";
        }
        std::cout << std::endl;
    }
    
};

#endif /* heap_h */
