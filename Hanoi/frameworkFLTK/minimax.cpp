#include <cassert>
#include <queue>
#include <unordered_set>
#include <sstream>
#include "minimax.h"

using namespace std;    

PancakeState::PancakeState() : order(){

}

PancakeNode::PancakeNode(PancakeState s){
    stack = s;
    parent = NULL;
    depth = 0;
}

PancakeNode::PancakeNode(PancakeState s, PancakeNode* par){
	stack = s; 
	parent = par;
	depth = parent->depth + 1;
}



/*Given a Vector and a index n, reverse the first n+1 numbers in Vector */
Vector<int> PancakeState::flip(int index){
	//create a Vector flippedCakes storing pancakes being flipped
	Vector<int> flippedCakes;
	for(int i = 0; i <= index; i++){
		flippedCakes.push_back(order[i]);
	}
	//reverse the Vector 
	reverse(flippedCakes.begin(), flippedCakes.end());

	for(size_t i = 0; i < flippedCakes.size(); i++){
		order[i] = flippedCakes[i];
	}

	// cout << "Flipping at " << index << endl;
	// printVector(order);
	return order;
}


//calculate sortedness of given state
int PancakeState::calcSortedness(){
	Vector<int> temp;

	int count = 0;

	//push 0 at the front of Vector

	temp.push_back(0);

	for(int i : order)

		temp.push_back(i);

	//count how many pairs of operators are sorted

	for(size_t i = 1; i < temp.size() - 1; i++){

		if(!((temp[i-1] < temp[i] && temp[i] < temp[i+1])||(temp[i-1] > temp[i] && temp[i] > temp[i+1]))){

			count ++;

			}

	}
	//std::cout << count << endl;
	return count;
}

//check if Vector is sorted 
bool PancakeState::isSorted(){
    for (size_t i = 0; i < order.size() - 1; ++i) {
        if (order.at(i) >= order.at(i+1))
			return false; 
    }
    return true;
}

//check if the node represent a sorted pancake, aka end state
bool PancakeNode::isSorted(){
	return stack.isSorted();
}


//convert a Vector to String
String PancakeState::toStr() const{
	ostringstream ss;
	String orderStr;
	for(int i:order){
		ss << i << " ";
	}
	return ss.str();
}

//compare if two states equal
bool PancakeState::operator==(const PancakeState& other) const{
	return ( order == other.order);
}


/*Given a Vector, print all its elements*/
void PancakeNode::printVector(Vector<int> vec){
	for(int num: vec){
		cout << num << " ";
	}
	cout << endl;
}

/*Given a Vector, print all its elements*/
void PancakeState::printVector(Vector<int> vec){
	for(int num: vec){
		cout << num << " ";
	}
	cout << endl;
}

//print the sucessors of a node by flipping all possible pancakes
Vector<PancakeNode*> PancakeNode::successors(){
	Vector<PancakeNode*> successors;
	//flip at index from 1 to size-1, store each state into a node
	//printVector(stack.order);
	for(size_t i = 1; i < (stack.order).size();i++){
		Vector<int> stackOrder = stack.order;//flip will change original stack
		PancakeState tempStack(stackOrder);
		Vector<int> newOrder = tempStack.flip(i);
		PancakeState ps(newOrder);
		PancakeNode* newPN = new PancakeNode(ps, this);
		successors.push_back(newPN);
	} 
	return successors;
}

//compare if two node equal
bool PancakeNode::operator==(const PancakeNode& other) const{
	return ( stack.order == other.stack.order);
}

//find the minimum sortedness node in a node Vector
PancakeNode* PancakeNode::findMin(Vector<PancakeNode*> pnVec){
	PancakeNode* minNode = pnVec[0];
	for(PancakeNode* pn:pnVec){
		if(pn->sortedness < minNode->sortedness)
			minNode = pn;
	}
	return minNode;
}

//given a difficulty, return a pointer to the last level pancake node with least sortedness value
PancakeNode* PancakeNode::minimax(int difficulty){
	PancakeNode* currNode = this;
	queue<PancakeNode*> nodes;
	unordered_set<PancakeState, stackHash> explored;
	nodes.push(currNode);

	while(currNode->depth < difficulty && nodes.size() != 0){
		currNode = nodes.front();
	    explored.insert(currNode->stack);
		nodes.pop();

		if(currNode->isSorted())
			return currNode;

		if(currNode->depth + 1 <= difficulty){//stop generating when reach diff
			Vector<PancakeNode*> successors = currNode->successors();
			for(PancakeNode* pn:successors){
				if(explored.find(pn->stack) != explored.end()){//duplicate stack
					delete pn;
				}
				else{
					nodes.push(pn);
				}
			}
		}
	}

	Vector<PancakeNode*> lastLevel;
	while(nodes.size() != 0){
		currNode = nodes.front();
		nodes.pop();
		lastLevel.push_back(currNode);
	}

	return findMin(lastLevel);
}

//helper function, print solution path to root
//return the index of the pancake that AI will flip from the root node
int PancakeNode::printPath(){
	PancakeNode *currNode = this;
	int count = this->depth;
	PancakeNode* nextMove;
	PancakeNode* rootNode;
	while(count >=0){
		if(count == 1){
			nextMove = currNode;
		}
		else if(count == 0){
			rootNode = currNode;
		}
		// printVector(currNode->stack.order);
		currNode = currNode -> parent;
		count --;
	}
	//compare the nextMove node with root state
	int stackSize = rootNode->stack.order.size();
	// cout << endl;
	// printVector(rootNode->stack.order);
	// printVector(nextMove->stack.order);
	// cout << endl;
	int flipIndex = 1;
	for(int i = stackSize-1; i > 0; i--){
		if(rootNode->stack.order[i] != nextMove->stack.order[i]){
			return i;
		}
	}
}
