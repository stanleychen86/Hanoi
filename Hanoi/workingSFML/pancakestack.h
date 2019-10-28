#ifndef PANCAKESTACK_H
#define PANCAKESTACK_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
// #include <ncurses.h>
#include <SFML/Graphics.hpp>
#include "gameentities.h"

class PancakeStack
{
private:
  //int size;
  //Make sure each pancake diff size
  std::vector<int> order;
  //Offset x-coordinates for drawing
  sf::RenderWindow& win;
  GameEntities& ge;

public:
  PancakeStack(std::vector<int> order, sf::RenderWindow& win, GameEntities& ge);
  ~PancakeStack();
  void flip(int index, bool isPlayer);
  void blink(int index, bool isPlayer);
  void draw();
  bool isSorted();
  std::vector<int> getOrder();
  void displayMinSteps();
  int requestHint();
  //Return a vector of the sequence of flips to put stack of pancakes into order

};

// std::vector<int>* find_solution(const std::vector<int>& pancakes);

#endif
