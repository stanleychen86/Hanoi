#ifndef MINIMAX_H
#define MINIMAX_H
#include <stdio.h>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <bits/stdc++.h>
#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
using namespace std;

class PancakeState {
public:
    Vector<int> order;

    PancakeState();
    PancakeState(Vector<int> order) {
        this->order = order;
    }

	int calcSortedness();

    Vector<int> flip(int index); //reverse part of the Vector order in PancakeState

    
	void printVector(Vector<int> vec);
    void testCase(Vector<int> order, int index);
    bool isSorted();
    String toStr() const;
    bool operator==(const PancakeState& other) const;
    //int AIchoice(int diff); //TODO::clean this 
};

class stackHash{
public:
    size_t operator()(const PancakeState& stack) const{
        String str = stack.toStr();
        hash<String> hasher;
        return hasher(str);
    }
};

class PancakeNode{
public:
	PancakeState stack;
	PancakeNode* parent;
    int depth;
	int sortedness = stack.calcSortedness();
    
    PancakeNode(PancakeState s);
    PancakeNode(PancakeState s, PancakeNode* par);
	bool isSorted(); //terminate the game if pancake stack is sorted
    Vector<PancakeNode*> successors(); //pointer to successors
    bool operator==(const PancakeNode& other) const;
	void printVector(Vector<int> vec);
    PancakeNode* findMin(Vector<PancakeNode*> pnVec);
    PancakeNode* minimax(int difficulty);
    int printPath();
};

#endif