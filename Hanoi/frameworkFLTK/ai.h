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
  AI(const Vector<int> &p_order, Simple_window* p_win, int diff);
  int select();
};

#endif
