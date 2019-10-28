#include "player.h"

Player::Player(const std::vector<int> &p_order, sf::RenderWindow &p_win, GameEntities &ge) : Entity(p_order, p_win, ge), win(p_win), ge(ge), pointer_index(1) { p.displayMinSteps(); }

//Return the index of the pancake in stack to flip
int Player::select()
{
	//Call p.requestHint() when player presses hint button

	std::vector<sf::CircleShape> pointers;
	sf::CircleShape leftPointer(15.f, 3);
	leftPointer.setFillColor(sf::Color::Green);
	leftPointer.setOutlineColor(sf::Color::Black);
	leftPointer.setOutlineThickness(3.f);
	leftPointer.setPosition(20.f, 110.f);
	// pointers.push_back(leftPointer);
	//leftPointer.rotate(90.f);
	sf::CircleShape rightPointer(15.f, 3);
	rightPointer.setFillColor(sf::Color::Green);
	rightPointer.setOutlineColor(sf::Color::Black);
	rightPointer.setOutlineThickness(3.f);
	rightPointer.setPosition(350.f, 110.f);
	// pointers.push_back(rightPointer);
	// for (int i = 0; i < pointers.size(); ++i)
	// {
	// 	pointers.at(i).setFillColor(sf::Color::Green);
	// 	pointers.at(i).setOutlineColor(sf::Color::Black);
	// 	pointers.at(i).setOutlineThickness(3.f);
	// 	pointers.at(i).setPosition(30.f + (i * 300.f), 100.f);
	// }

	bool enterPressed = false;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			sf::Vector2f movement(0.f, 0.f);
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				win.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (pointer_index == 1)
					{
						pointer_index = p.getOrder().size();
						movement.y += 70.f * (p.getOrder().size() - 1);
					}
					else
					{
						--pointer_index;
						movement.y -= 70.f;
					}
					leftPointer.move(movement);
					rightPointer.move(movement);
					break;
				case sf::Keyboard::Down:
					if (pointer_index == p.getOrder().size())
					{
						pointer_index = 1;
						movement.y -= 70.f * (p.getOrder().size() - 1);
					}
					else
					{
						++pointer_index;
						movement.y += 70.f;
					}
					leftPointer.move(movement);
					rightPointer.move(movement);
					break;
				case sf::Keyboard::H:

					// p.blink(p.requestHint(), false);
					// p.draw();

					break;
				case sf::Keyboard::Enter:
					enterPressed = true;
					break;
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		win.clear(sf::Color::White);
		win.draw(leftPointer);
		win.draw(rightPointer);
		ge.drawEntities();
		win.display();
		if (enterPressed) { break; }
	}
	return pointer_index;
}

void Player::takeTurn()
{
	Entity::takeTurn(true);
	p.displayMinSteps();
}

//Draw visual pointer to pancake - if draw == false, then erase instead
void Player::drawPointer(bool draw)
{
	// int row, col;
	// getmaxyx(win, row, col);
	// int y = (row - 27) / 2;
	// if (y < 0) { y = 0; }
	// y += ((pointer_index-1) * 3) + 1;

	// int length = (p.getOrder().at(pointer_index-1) * 2) + 1;
	// int x1 = (col - length) / 2 - 1;
	// int x2 = (col + length) / 2 + 2;

	// if (draw) {
	//     mvwaddch(win, y, x1, ACS_RARROW);
	//     mvwaddch(win, y, x2, ACS_LARROW);
	// }
	// else {
	//     mvwaddch(win, y, x1, ' ');
	//     mvwaddch(win, y, x2, ' ');
	// }
	// wrefresh(win);
}
