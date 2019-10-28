#ifndef PANCAKESTACK_H
#define PANCAKESTACK_H
#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <string>

class PancakeStack
{
private:
  //int size;
  //Make sure each pancake diff size
  Vector<int> order;
  //Offset x-coordinates for drawing
  //WINDOW* win;
  Simple_window* win;
  Vector<Rectangle*> pancakes;
  int x_sz;
  int y_sz;

public:
  PancakeStack(Vector<int> order, Simple_window* win);
  ~PancakeStack();
  void flip(int index);
  void blink(int index, bool all = true);
  void draw(bool isPlayer);
  bool isSorted();
  Vector<int> getOrder();
  void displayMinSteps();
  int requestHint();
  //Return a vector of the sequence of flips to put stack of pancakes into order

};

//Vector<int>* find_solution(const Vector<int>& pancakes);

#endif
