#ifndef AI_H
#define AI_H
#include "entity.h"
#include "minimax.h"

class AI : public Entity
{
private:
  int diff;
  
  int minimax();

public:
  AI(const std::vector<int> &p_order, sf::RenderWindow& p_win, GameEntities& ge, int diff);
  int select();
};

#endif
