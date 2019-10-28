#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity
{
private:
  Simple_window* win;
  int pointer_index;

  void drawPointer(bool draw = true);
public:
  Player(const Vector<int>& p_order, Simple_window* p_win);
  int select();
  void takeTurn(bool isPlayer);
};

#endif