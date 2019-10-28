#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity
{
private:
  WINDOW* win;
  int pointer_index;

  void drawPointer(bool draw = true);
public:
  Player(const std::vector<int>& p_order, WINDOW* p_win);
  int select();
  void takeTurn();
};

#endif