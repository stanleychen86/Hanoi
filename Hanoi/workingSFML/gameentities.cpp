#include "gameentities.h"
#include <unistd.h>

GameEntities::GameEntities(std::vector<int> order, sf::RenderWindow& win) : player_order(order), ai_order(order), win(win), pan_color(sf::Color::Red) {
	create_pancakes(true);
	create_pancakes(false);
}


GameEntities::~GameEntities() {}

void GameEntities::set_order(bool is_player, std::vector<int> ord) {
	if (is_player) {
		player_order = ord;
	}
	else {
		ai_order = ord;
	}
}

void GameEntities::create_pancakes(bool is_player) {
	int offset = 0;
	int start_x = 200;
	int start_y = 100;
	int width = 60;
	int height = 35;
	int x_mult = 25;
	std::vector<int>* ord;
	std::vector<sf::RectangleShape>* cakes;
	if (is_player) {
		player_pancakes = *(new std::vector<sf::RectangleShape>());
		ord = &player_order;
		cakes = &player_pancakes;
	}
	else {
		ai_pancakes = *(new std::vector<sf::RectangleShape>());
		offset = 400;
		ord = &ai_order;
		cakes = &ai_pancakes;
	}
	for (int i = 0; i < ord->size(); i++) {
		sf::RectangleShape *rect = new sf::RectangleShape();
		int wd = (ord->at(i) * x_mult) + width;
		rect->setSize(sf::Vector2f(wd, height));
		rect->setFillColor(pan_color);
		int xpos = start_x + offset - wd/2;
		int ypos = start_y + (i * 70);
		rect->setPosition(xpos, ypos);
		cakes->push_back(*rect);
	}
}
void GameEntities::blink(int index, bool is_player) {
	int num_blinks = 3;
	struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 5 * 100000000;
	std::vector<sf::RectangleShape>* cakes = &player_pancakes;
	if (!is_player) {
		cakes = &ai_pancakes;
	}
	for (int j = 0; j < num_blinks; j++){
		for (int i = 0; i < index; i++) {
			cakes->at(i).setFillColor(sf::Color::Transparent);
		}
		win.clear(sf::Color::White);
		drawEntities();
		win.display();
		nanosleep(&ts, NULL);
		for (int i = 0; i < index; i++) {
			cakes->at(i).setFillColor(pan_color);
		}
		win.clear(sf::Color::White);
		drawEntities();
		win.display();
		nanosleep(&ts, NULL);
	}
}

void GameEntities::drawEntities()
{
	sf::Font font;
	sf::Text instr;
	font.loadFromFile("Arial.ttf");
	instr.setFont(font);
	instr.setString("Use the arrow keys to move up and down. Press enter to flip.");
    instr.setFillColor(sf::Color::Black);
    instr.setPosition(0,1);

	for (int i = 0; i < player_pancakes.size(); i++) {
		win.draw(player_pancakes.at(i));
		}
	for (int i = 0; i < ai_pancakes.size(); i++) {
		win.draw(ai_pancakes.at(i));
	}
	win.draw(instr);
}