//
//  main.cpp
//  MST
//
//  Created by Madeleine Monfort on 11/23/15.
//  Copyright © 2015 Madeleine Monfort. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "chain.h"
#include "heap.h"
#include "UnionFind.h"

struct edge {
    int weight;
    int nodeTo;
    int nodeFrom;
    //constructors
    edge() {
        weight = 0;
        nodeTo = -1;
        nodeFrom = -1;
    }
    edge(int w, int node1, int node2) {
        this->weight = w;
        this->nodeFrom = node1;
        this->nodeTo = node2;
    }
    //override printing
    friend std::ostream &operator<<(std::ostream& os, const edge &e) {
        os << "(" << e.nodeFrom << ", " << e.nodeTo << ")";
        return os;
    }
    //override ==
    bool operator==(const edge& e) const {
        if(this->nodeFrom == e.nodeFrom && this->nodeTo == e.nodeTo) {
            return true;
        }
        else return false;
    }
    //override !=
    bool operator!=(const edge& m) const {
        if(this->nodeFrom == m.nodeFrom) {
            if(this->nodeTo != m.nodeTo) {
                return true;
            }
            else return false;
        }
        else return true;
    }
    bool operator<(const edge& m) const {
        return this->weight < m.weight;
    }
    bool operator<=(const edge& m) const {
        return this->weight <= m.weight;
    }
    bool operator>(const edge& m) const {
        return this->weight > m.weight;
    }
    bool operator>=(const edge& m) const {
        return this->weight >= m.weight;
    }
};

void mstFunc();
void Prim(int startNode, chain<edge>* list, int n, int e);
void Kruskal(chain<edge>* list, int n, int e);
void Sollin(int startNode, chain<edge>* list, int n, int e);

void testChain();
void testEdge();
void testHeap();
void testUF();
void printGraph(chain<edge>* c, int length);

int main(int argc, const char * argv[]) {
    
    mstFunc();
    //testEdge();
    //testHeap();
    //testUF();
    
    return 0;
}

void mstFunc() {
    
    std::cout << "Enter number of Node and Edge(s): " << std::endl;
    int node;
    int edges;
    std::cin >> node >> edges;
    chain<edge>* adjacencyList = new chain<edge>[node];
    //initialize the array of chains
    for (int i = 0; i < node; i++) {
        adjacencyList[i] = *new chain<edge>();
    }
    
    std::cout << "Enter Node A and Node B and Undirected Edge Weight(s): " << std:: endl;
    
    //will have to be made a for loop later
    for (int i = 0; i < edges; i++) {
        int nodeA;
        int nodeB;
        int weight;
        std::cin >> nodeA >> nodeB >> weight;
        edge edgeA = *new edge(weight,nodeA,nodeB);
        edge edgeB = *new edge(weight,nodeB,nodeA);
        adjacencyList[nodeA].insert(edgeA);
        adjacencyList[nodeB].insert(edgeB);
    }
    
    //test it by printing the adjacencyList:
    //printGraph(adjacencyList, node);
    
    std::cout << "Enter the start node: " << std::endl;
    int start;
    std::cin >> start;
    
    std::cout << "Prim's MST: " << std::endl;
    Prim(start, adjacencyList, node, edges);
    std::cout << "\nKruskal's MST: " << std::endl;
    Kruskal(adjacencyList, node, edges);
    std::cout << "\nBoruvka's MST: " << std::endl;
    Sollin(start, adjacencyList, node, edges);
}

void Prim(int startNode, chain<edge>* list, int n, int e) {//implement Prim's algorithm
    //array holding the isReached bool
    bool* mst = new bool[n];
    for (int i = 0; i < n; i++) {
        mst[i] = false; //initialized to false
    }
    //start with 1-vertex tree
    mst[startNode] = true;
    int totalWeight = 0;
    
    //min heap of edges (to choose from)
    heap<edge>* minEdges = new heap<edge>(2*e,true);
    
    //initialize with edges from startNode
    for (int i = 0; i < list[startNode].size(); i++) {
        minEdges->push(list[startNode].get(i));
    }
    
    //FOR LOOP:
    for (int i = 1; i < n; i++) { //Effectively FOR EACH NODE
        
        //add vertex & edge (least cost edge)
        edge toAdd = minEdges->top();
        
        //make sure the nodeTo isn't already reached (in the edge to add)
        while (true) {
            if (!mst[toAdd.nodeTo]) { //if nodeTo not reached
                break;
            }
            minEdges->pop();
            toAdd = minEdges->top();
        }
        
        //take added edge and update mst
        totalWeight = totalWeight + toAdd.weight;
        int newNode = toAdd.nodeTo;
        mst[newNode] = true;
        //once vertex added, add its edges to heap
        for (int j = 0; j < list[newNode].size(); j++) {
            minEdges->push(list[newNode].get(j));
        }
        //print out added edge
        std::cout << toAdd << std::endl;
       
    }
    
    //print out final weight
    std::cout << "Total Weight:\n" << totalWeight << std::endl;
}

void Kruskal(chain<edge>* list, int n, int e) {//implement Kruskal's algorithm
    heap<edge>* minEdges = new heap<edge>(e,true); //hold all the edges
    
    //add all the edges into a min heap
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < list[i].size(); j++) {
            edge toAdd = list[i].get(j);
            //get rid of duplicates
            if (toAdd.nodeTo > i) {
                minEdges->push(toAdd);
            }
        }
    }
    
    UnionFind* mst = new UnionFind(n); //needs to hold all the nodes
    int runningW = 0;
    
    while (!minEdges->empty()) { //while there are edges to add
        //add each least cost edge
        edge toAdd = minEdges->top();
        //make sure a cycle is not created
        if (mst->connected(toAdd.nodeFrom, toAdd.nodeTo)) {
            //it creates a cycle
        }
        else {
            mst->Union(toAdd.nodeFrom, toAdd.nodeTo);
            //increment weight
            runningW = runningW + toAdd.weight;
            //print edge
            std::cout << toAdd << std::endl;
        }
        
        minEdges->pop();
    }
    
    std::cout << "Total Weight:\n" << runningW << std::endl;
}

void Sollin(int startNode, chain<edge>* list, int n, int e) {//implement Sollin's algorithm
    chain<edge>* E = new chain<edge>(); // only holds edges to be added to mst
    int* components = new int[n]; //to hold components for the process
    for (int i = 0; i < n; i++) {
        components[i] = i; //initialize
    }
    int total = 0;
    
    //while disjoint
    int l = 0;
    while (l < n-1) {
        
        //for each component
        for (int i = startNode; i < n; i++) {
            
            heap<edge>* S = new heap<edge>(e,true); //holds many edges
            
            if (components[i] != i) {
                continue;
            }
            
            //for each vertex in component
            for (int j = i; components[j] == i; j++) {
                //push the vertex's edges into S
                for (int k = 0; k < list[j].size(); k++) {
                    edge temp = list[j].get(k);
                    //make sure not in component
                    if (components[temp.nodeTo] != i) {
                        S->push(temp);
                    }
                }
            }
            //add cheapest edge in S to E
            edge temp = S->top();
            components[temp.nodeTo] = i;
            E->insert(temp);
            total = total + temp.weight;
            l++;
            if (l == n-1) {
                break;
            }
        }
    }
    
    //print out edges and total weight
    E->print();
    std::cout << "\nTotal Weight:\n" << total << std::endl;
}

//---------------------------------------------------TESTING FUNCTIONS--------------------------------------------------------
void testChain() {
    chain<int>* c = new chain<int>();
    try {
        c->insert(0, 4);
        c->insert(1, 8);
        c->insert(2, 4);
        
        c->print();
        
        c->erase(2);
        c->print();
        
        c->insert(2, 3);
        c->print();
        c->erase(1);
        c->print();
        
    } catch (char const* e) {
        std::cout << e << std::endl;
    }
}

void testEdge() {
    chain<edge>* c = new chain<edge>();
    chain<edge>* d = new chain<edge>();
    try {
        c->insert(0, edge(0,1,8));
        c->print();
        c->insert(1, edge(3,2,4));
        c->print();
        c->erase(1);
        c->print();
        
        d->insert(edge(1,2,8));
        d->print();
        d->insert(edge(3,3,4));
        d->print();
        
    } catch (char const* e) {
        std::cout << e << std::endl;
    }

    std::cout << std::endl;
    edge one = edge(3,4,5);
    edge two = edge(7,3,5);
    edge three = edge(3,4,5);
    edge four = edge(3,5,8);
    
    if (one != two) {
        std::cout << "!= comparison works" << std::endl;
    }
    if (one < two) {
        std::cout << "< comparison works" << std::endl;
    }
    if (two > one) {
        std::cout << "> comparison works" << std::endl;
    }
    if (one <= four) {
        std::cout << "<= comparison works" << std::endl;
    }
    if (one >= four) {
        std::cout << ">= comparison works" << std::endl;
    }
    if (one == three) {
        std::cout << "== comparison works" << std::endl;
    }
    
}

void testHeap() {
    heap<edge>* h = new heap<edge>(10,true);
    h->push(edge(3,1,0));
    std::cout << h->top() << std::endl;
    h->print();
    h->push(edge(7,2,1));
    h->print();
    h->push(edge(2,1,2));
    std::cout << h->top() << std::endl;
    h->print();
}

void testUF() {
    UnionFind* uftest = new UnionFind(10);
    uftest->Union(1, 0);
    uftest->Union(1, 2);
    uftest->Union(7, 1);
    uftest->Union(3, 7);
}

void printGraph(chain<edge>* c, int length) {
    
    for (int i = 0; i < length; i++) {
        //std::cout << i << ": [";
        c[i].print();
        //std::cout << "]" << std::endl;
        std::cout << std::endl;
    }
}






