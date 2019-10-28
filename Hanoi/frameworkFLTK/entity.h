#ifndef ENTITY_H
#define ENTITY_H
#include "pancakestack.h"

class Entity
{
protected:
  PancakeStack p;
public:
  Entity(const Vector<int>& p_order, Simple_window* p_win, bool isPlayer) : p(p_order, p_win) { p.draw(isPlayer); }
  virtual ~Entity() {}
  virtual int select() = 0;
  virtual void takeTurn(bool isPlayer) 
  {
    int index = select();
    p.blink(index);
    p.flip(index); 
    p.draw(isPlayer);
  }
  bool stackSorted() { return p.isSorted(); }
};

#endif
