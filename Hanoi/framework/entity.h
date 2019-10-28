#ifndef ENTITY_H
#define ENTITY_H
#include "pancakestack.h"

class Entity
{
protected:
  PancakeStack p;
public:
  Entity(const std::vector<int>& p_order, WINDOW* p_win) : p(p_order, p_win) { p.draw(); }
  virtual ~Entity() {}
  virtual int select() = 0;
  virtual void takeTurn() 
  { 
    int index = select();
    p.blink(index);
    p.flip(index); 
    p.draw();
  }
  bool stackSorted() { return p.isSorted(); }
};

#endif
