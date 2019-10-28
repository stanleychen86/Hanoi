#ifndef MINIMAX_H
#define MINIMAX_H  
#include <string>
#include <string.h>
#include <iostream>
#include <utility>
#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

class PancakeState {
public:
    vector<int> order;

    PancakeState();
    PancakeState(vector<int> order) {
        this->order = order;
    }

	int calcSortedness();

    vector<int> flip(int index); //reverse part of the vector order in PancakeState

    
	void printVector(vector<int> vec);
    void testCase(vector<int> order, int index);
    bool isSorted();
    string toStr() const;
    bool operator==(const PancakeState& other) const;
    //int AIchoice(int diff); //TODO::clean this 
};

class stackHash{
public:
    size_t operator()(const PancakeState& stack) const{
        string str = stack.toStr();
        hash<string> hasher;
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
    vector<PancakeNode*> successors(); //pointer to successors
    bool operator==(const PancakeNode& other) const;
	void printVector(vector<int> vec);
    PancakeNode* findMin(vector<PancakeNode*> pnVec);
    PancakeNode* minimax(int difficulty);
    int printPath();
};

#endif