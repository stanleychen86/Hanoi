#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

bool gameFinished = false;
std::vector<std::pair<std::string, int>> highscores;

void endingMenu(std::vector<sf::Text>& choices, std::vector<sf::Text>::iterator highlight, sf::RenderWindow& window)
{
	for (auto choice = choices.begin(); choice != choices.end(); ++choice)
	{
		if (highlight == choice)
		{
			choice->setFillColor(sf::Color::Red);
			choice->setStyle(sf::Text::Bold);
			window.draw(*choice);
		}
		else
		{
			choice->setFillColor(sf::Color::Black);
			choice->setStyle(sf::Text::Regular);
			window.draw(*choice);
		}
	}
}
void endingSelection(sf::RenderWindow& window, sf::Font& font) {
	static std::vector<sf::Text> choices{ {"Play Again", font}, {"Quit", font} };
	std::string choice = "None"; auto highlight = choices.begin(); choices[0].setPosition(200, 150); choices[1].setPosition(200, 250);
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			switch (event.type)	{
			case sf::Event::KeyPressed:	{
				switch (event.key.code)	{
				case sf::Keyboard::Down:
					if (++highlight == choices.end())
						highlight = choices.begin();	break;
				case sf::Keyboard::Up:
					if (highlight == choices.begin())
						highlight = std::prev(choices.end());
					else --highlight;
					break;
				case sf::Keyboard::Enter:
					choice = highlight->getString();	break;
				default: break;	}
			} break;
			case sf::Event::Closed:	{
				window.close();	} break; default: break;	}	}
		window.clear(sf::Color::White);	endingMenu(choices, highlight, window);	window.display();
		if (choice == "Quit") { gameFinished = true; window.close(); }
		else {	gameFinished = false; std::cout << "Not done." << std::endl; }
	}
}
void readAndDisplayHighScores(sf::RenderWindow& window, sf::Font& font) {
	bool keepOpen = true; std::string name; int score;
	sf::Text leaveString("Press Q to go back.", font); leaveString.setPosition(150, 50); leaveString.setFillColor(sf::Color::Black);
	std::ifstream myfile("scores.txt"); std::vector<sf::Text> scoresToPrint;
	if (myfile.is_open()) {
		while (myfile >> name >> score) {
			std::pair <std::string, int> pairScore = make_pair(name, score); highscores.push_back(pairScore);
			sf::Text temp(pairScore.first + ": " + std::to_string(pairScore.second), font); scoresToPrint.push_back(temp);
		}	myfile.close();	}
	else {
		std::cout << "File not found." << std::endl; std::exit(-1);
	}
	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q)
					keepOpen = false; }
			if (event.type == sf::Event::Closed)
				window.close();	}
		window.clear(sf::Color::White); window.draw(leaveString);
		for (int i = 0; i < scoresToPrint.size(); i++) {
			scoresToPrint.at(i).setPosition(250, 150 + (50 * i)); scoresToPrint.at(i).setFillColor(sf::Color::Black); window.draw(scoresToPrint.at(i)); 
		}
		window.display(); if (!keepOpen) {  break; }
	}
}

int main()
{
	//sf::RenderWindow window(sf::VideoMode(600, 600), "Ending Menu", sf::Style::Default);
	sf::RenderWindow window(sf::VideoMode(600, 600), "High Scores", sf::Style::Default);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load arial.ttf\n";
		std::exit(-1);
	}
	//endingSelection(window, font);
	readAndDisplayHighScores(window, font);
}