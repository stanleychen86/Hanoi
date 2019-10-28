#include "ai.h"

AI::AI(const std::vector<int>& p_order, sf::RenderWindow& p_win, GameEntities& ge, int diff) : Entity(p_order, p_win, ge), diff(diff) {}


//Return the index of the pancake in stack to flip
int AI::select()
{
    if (p.isSorted()) { return 1; }
    int index = this->minimax();
    return index + 1;
}


//Minimax search of depth diff
int AI::minimax()
{
    PancakeState currPancake(p.getOrder());
    PancakeNode pn(currPancake);
	return pn.minimax(diff)->printPath();
}
