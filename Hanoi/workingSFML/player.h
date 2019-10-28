#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity
{
private:
  int pointer_index;
  sf::RenderWindow& win;
  GameEntities& ge;

  void drawPointer(bool draw = true);
public:
  Player(const std::vector<int>& p_order, sf::RenderWindow& p_win, GameEntities& ge);
  int select();
  void takeTurn();
};

#endif