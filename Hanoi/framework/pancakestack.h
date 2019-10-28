#ifndef PANCAKESTACK_H
#define PANCAKESTACK_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <ncurses.h>

class PancakeStack
{
private:
  //int size;
  //Make sure each pancake diff size
  std::vector<int> order;
  //Offset x-coordinates for drawing
  WINDOW* win;

public:
  PancakeStack(std::vector<int> order, WINDOW* win = stdscr);
  ~PancakeStack();
  void flip(int index);
  void blink(int index, bool all = true);
  void draw();
  bool isSorted();
  std::vector<int> getOrder();
  void displayMinSteps();
  int requestHint();
  //Return a vector of the sequence of flips to put stack of pancakes into order

};

std::vector<int>* find_solution(const std::vector<int>& pancakes);

#endif
