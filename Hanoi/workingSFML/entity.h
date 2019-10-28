#ifndef ENTITY_H
#define ENTITY_H
#include "pancakestack.h"

class Entity
{
protected:
  PancakeStack p;
public:
  Entity(const std::vector<int>& p_order, sf::RenderWindow& p_win, GameEntities& ge) : p(p_order, p_win, ge) { p.draw(); }
  virtual ~Entity() {}
  virtual int select() = 0;
  virtual void takeTurn(bool isPlayer) 
  { 
    int index = select();
    p.blink(index, isPlayer);
    p.flip(index, isPlayer); 
    p.draw();
  }
  bool stackSorted() { return p.isSorted(); }
};

#endif
