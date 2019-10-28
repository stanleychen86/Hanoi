#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "player.h"
#include "ai.h"

class GameEngine
{
private:
  //Gamestate
  bool gameOver;
  //(1|0|-1) (player|tie|ai)
  int winner;
  int score;
  std::vector<Entity*> entities;
  //Number of pancakes
  int n;
  //Strength of AI
  int diff;
  GameEntities ge;

  void calculateScore();

public:
  GameEngine(const std::vector<int>& p_order, int n, int diff, sf::RenderWindow& win);
  ~GameEngine();
  void loop();
  int getScore();
  int getWinner();

  //Friend functions for test cases
  friend void calculateScoreTest(GameEngine &e);
  friend void setWinnerAndScore(GameEngine &e, int winner, int score);
  friend void setNAndDiff(GameEngine &e, int n, int diff);
};

#endif