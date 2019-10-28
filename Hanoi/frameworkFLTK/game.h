#ifndef GAME_H
#define GAME_H
#include <utility>
#include <chrono>
#include <random>
#include <fstream>
#include "gameengine.h"

class Game
{
private:
  bool gameFinished;
  Vector<std::pair<String, int>> highscores;
  String initials;

  void displaySplash();
  std::pair<int,int> requestConfigs();
  Vector<int> requestInitState(int n);
  void readAndDisplayHighScores();
  void requestAndDisplayInitials();
  void displayGameOver(int score, int winner);
  void sortAndWriteHighScores(int score);

  void displayInstr();
  bool checkConfigs(int n, int diff, String nString, String diffString);
  String requestSeq(int n);
  bool checkSeq(String seq, int n);
  Vector<int> createSeq(String seq, int n);
  bool checkInitials(String initials);
  void endingSelection(Simple_window* win);

public:
  Game();
  void run();

  //Friend functions for test cases
  friend bool checkConfigsTest(Game& g, int n, int diff, String nString, String diffString);
  friend bool checkSeqTest(Game& g, String seq, int n);
  friend Vector<int> createSeqTest(Game& g, String seq, int n);
  friend bool checkInitialsTest(Game& g, String initials);
};

bool pairCompare(const std::pair<String, int>& first, const std::pair<String, int>& second);

#endif
