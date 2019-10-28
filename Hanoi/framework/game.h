#ifndef GAME_H
#define GAME_H
#include <utility>
#include <string>
#include <string.h>
#include <chrono>
#include <random>
#include <fstream>
#include "gameengine.h"

class Game
{
private:
  bool gameFinished;
  std::vector<std::pair<std::string, int>> highscores;
  std::string initials;

  void displaySplash();
  std::pair<int,int> requestConfigs();
  std::vector<int> requestInitState(int n);
  void readAndDisplayHighScores();
  void requestAndDisplayInitials();
  void displayGameOver(int score, int winner);
  void sortAndWriteHighScores(int score);

  void displayInstr();
  bool checkConfigs(int n, int diff, std::string nString, std::string diffString);
  std::string requestSeq(int n);
  bool checkSeq(std::string seq, int n);
  std::vector<int> createSeq(std::string seq, int n);
  bool checkInitials(std::string initials);
  void endingSelection();
  void endingMenu(int num_choices, int highlight);

public:
  Game();
  void run();

  //Friend functions for test cases
  friend bool checkConfigsTest(Game& g, int n, int diff, std::string nString, std::string diffString);
  friend bool checkSeqTest(Game& g, std::string seq, int n);
  friend std::vector<int> createSeqTest(Game& g, std::string seq, int n);
  friend bool checkInitialsTest(Game& g, std::string initials);
};

bool pairCompare(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second);

#endif
