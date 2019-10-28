#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H
#include <vector>
#include <SFML/Graphics.hpp>
// #include "player.h"
// #include "ai.h"

class GameEntities
{
private:
  sf::RenderWindow& win;
  std::vector<sf::RectangleShape> player_pancakes;
  std::vector<sf::RectangleShape> ai_pancakes;
  std::vector<int> player_order;
  std::vector<int> ai_order;
  //sf::Text instr;
  sf::Color pan_color;

public:
  GameEntities(std::vector<int> order, sf::RenderWindow& win);
  ~GameEntities();
  void set_order(bool is_player, std::vector<int> ord);
  void create_pancakes(bool is_player);
  void blink(int index, bool is_player);
  void drawEntities();
};

#endif

//Entities in this class: Player PancakeStack, AI PancakeStack, "Use the arrow keys to move up and down. Press enter to flip." text