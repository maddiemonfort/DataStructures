//
//  main.cpp
//  LPT
//
//  Created by Madeleine Monfort on 11/4/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include "heap.h"
#include "HBLT.h"
#include <ctime>

void LPT();
void heapTest1();
void heapTest2();
void heapTest3();
void heapTest4();
void heapTest5();
void HBLTTest1();
void HBLTTest2();
void HBLTTest3();
void machineTest();

struct machine {
    int time;
    std::string schedule;
    machine() {
        time = 0;
        schedule = "";
    }
    machine(int t, std::string s) { //constructor
        time = t;
        schedule = s;
    }
    //overload comparisons
    bool operator<(const machine& m) const {
        return this->time < m.time;
    }
    bool operator>(const machine& m) const {
        return this->time > m.time;
    }
    bool operator=(const machine& m) const {
        return this->time == m.time;
    }
    bool operator>=(const machine& m) const {
        return this->time >= m.time;
    }
    bool operator<=(const machine& m) const {
        return this->time <= m.time;
    }
    std::ostream& operator << (std::ostream& os) {
        os << time;
        return os;
    }
};


int main(int argc, const char * argv[]) {
    
    //heapTest5();
    //HBLTTest3();
    LPT();
    //machineTest();
    
    return 0;
}

void machineTest() {
    machine* m = new machine(0,"");
    machine* n = new machine(10,"");
    machine* t = new machine(14,"");
    if (m >= t || m >= n) {
        std::cout << "Error\n";
    }
    else {
        std::cout << "it works\n";
    }
}

void LPT() {
    int jobs;
    int machines;
    heap<int>* jobHeap; //contains sorted jobs
    heap<int>* jobHeap2;
    int runningMaxTime = 0;
    
    std::cout << "Enter number of job(s): " << std::endl;
    std::cin >> jobs;
    std::cout << "Enter number of machine(s): " << std::endl;
    std::cin >> machines;
    
    jobHeap = new heap<int>(jobs,false); //max heap
    jobHeap2 = new heap<int>(jobs, false);
    std::cout << "Enter processing time(s): " << std::endl;
    for (int i = 0; i < jobs; i++) {
        int time;
        std::cin >> time;
        jobHeap->push(time);
        jobHeap2->push(time);
    }
    
    
    clock_t start;
    clock_t finish;
    double elapsed_time;
    
    //-----------------------------------------------------measure for heaps:
    start = clock();
    heap<machine*>* machineHeap = new heap<machine*>(machines, true); //min heap
    //initialize heap
    for (int i = 0; i < machines; i++) {
        machineHeap->push(new machine(0,""));
    }
    
    for (int i = 0; i < jobs; i++) {
        //pop min element
        machine* temp = machineHeap->top();
        machineHeap->pop();
        //std::cout << temp->time << std::endl;
        
        //add max time to it
        int job = jobHeap->top();
        //std::cout << job << std::endl;
        jobHeap->pop();
        int t = temp->time + job;
        std::string s = temp->schedule + " " + std::to_string(job) + ",";
        
        temp = new machine(t,s);
        
        // push it back into stack.
        machineHeap->push(temp);
        
        //keeping track of finish time
        if (runningMaxTime < t) {
            runningMaxTime = t;
        }
    }
    std::cout << "Min Heap Finishing Time: " << runningMaxTime << std::endl;
    std::cout << "Schedule: " << std::endl;
    for (int i = 1; i < machines+1; i++) {
        machine* temp = machineHeap->top();
        std::cout << "Machine " << i << ": " << temp->schedule << std::endl;
        machineHeap->pop();
    }
    
    finish = clock();
    elapsed_time = (double)(finish-start)/CLOCKS_PER_SEC;
    std::cout << "Time Elapsed: " << elapsed_time << "\n\n";
    
    //------------------------------------------------------measure for HBLT:
    start = clock();
    HBLT<machine*>* machineTree = new HBLT<machine*>();
    //initialize
    for (int i = 0; i < machines; i++) {
        machineTree->push(new machine(0,""));
    }
    
    for (int i = 0; i < jobs; i++) {
        //pop min element
        machine* temp = machineTree->top();
        machineTree->pop();
        //std::cout << temp->time << std::endl;
        
        //add max time to it
        int job = jobHeap2->top();
        //std::cout << job << std::endl;
        jobHeap2->pop();
        int t = temp->time + job;
        std::string s = temp->schedule + " " + std::to_string(job) + ",";
        temp = new machine(t,s);
        
        // push it back into stack.
        machineTree->push(temp);
        
        //keeping track of finish time
        if (runningMaxTime < temp->time) {
            runningMaxTime = temp->time;
        }
    }
    std::cout << "Height Biased Leftist Tree Finishing Time: " << runningMaxTime << std::endl;
    std::cout << "Schedule: " << std::endl;
    for (int i = 1; i < machines+1; i++) {
        machine* temp = machineTree->top();
        std::cout << "Machine " << i << ": " << temp->schedule << std::endl;
        machineTree->pop();
    }
    
    finish = clock();
    elapsed_time = (double)(finish-start)/CLOCKS_PER_SEC;
    std::cout << "Time Elapsed: " << elapsed_time << std::endl;
}



//-------------------------------------------------Testing functions----------------------------------------------------------
void heapTest1() {
    heap<int>* h = new heap<int>(12, true); //min heap
    h->push(5);
    h->push(6);
    std::cout << h->top() << std::endl;
    //testing swap function:
    h->swap(1, 2);
    std::cout << h->top() << std::endl;
}

void heapTest2() {
    heap<int>* h = new heap<int>(10, true); //min heap
    h->push(5);
    h->push(4);
    h->push(10);
    h->push(3);
    h->push(8);
    std::cout << h->top() << std::endl;
    //testing pop
    h->pop();
    std::cout << h->top() << std::endl;
    std::cout << std::endl;
    
    heap<int>* m = new heap<int>(10,false); //max heap
    m->push(5);
    m->push(4);
    m->push(10);
    m->push(3);
    m->push(8);
    std::cout << m->top() << std::endl;
    //testing pop
    m->pop();
    std::cout << m->top() << std::endl;
    m->pop();
    std::cout << m->top() << std::endl;
    m->pop();
    std::cout << m->top() << std::endl;
    m->pop();
    std::cout << m->top() << std::endl;
    m->pop();
    std::cout << m->top() << std::endl;
}

void heapTest3() {
    heap<int>* h = new heap<int>(10, false); //max heap
    h->push(14);
    h->push(7);
    h->push(10);
    h->push(6);
    h->push(2);
    h->push(3);
    h->push(5);
    h->print();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->print();
    h->pop();
    std::cout << h->top() << std::endl;
    h->print();
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
}

void heapTest5() {
    heap<int>* h = new heap<int>(10, true); //min heap
    h->push(0);
    h->push(0);
    h->push(0);
    
    int j = 0;
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(14+j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(10+j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(7 + j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(6+j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(5+j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(3+j);
    std::cout << h->top() << std::endl;
    j = h->top();
    h->pop();
    h->push(2+j);
}

void heapTest4() {
    heap<int>* h = new heap<int>(12, true); //min heap
    try {
        h->pop();
    } catch (char const* c) {
        std::cout << c << std::endl;
    }
    
}

void HBLTTest1() {
    HBLT<int>* h = new HBLT<int>();
    h->push(1);
    std::cout << h->top() << std::endl;
    h->push(4);
    h->push(2);
    h->push(30);
    h->push(10);
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
}

void HBLTTest2() {
    HBLT<int>* h = new HBLT<int>();
    try {
        h->pop();
    } catch (char const* e) {
        std::cout << e << std::endl;
    }
}

void HBLTTest3() { //more comprehensive test
    HBLT<int>* h = new HBLT<int>();
    h->push(10);
    h->push(2);
    h->push(5);
    h->push(15);
    h->push(40);
    h->push(6);
    h->push(4);
    h->push(12);
    
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    std::cout << h->top() << std::endl;
    h->pop();
    
    try {
        h->pop();
    } catch (char const* e) {
        std::cout << e << std::endl;
    }
}



