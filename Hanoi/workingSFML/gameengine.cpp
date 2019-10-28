#include "gameengine.h"

GameEngine::GameEngine(const std::vector<int>& p_order, int n, int diff, sf::RenderWindow& win) : gameOver(false), winner(0), score(0), n(n), diff(diff), ge(p_order, win)
{
    // noecho();

    // int row, col;
    // getmaxyx(stdscr, row, col);
    // //33 = height of window
    // int y = (row - 33) / 2;
    // if (y < 0) { y = 0; }
    // int x = col/2;

    //sf::RenderWindow win(sf::VideoMode(825, 800), "Pancake Sorting Game");
    //if (demoGame) { AI demo(p_order, left_win, random number); } (demoGame will randomize n and diff)
    
    entities.push_back(new Player(p_order, win, ge));

    entities.push_back(new AI(p_order, win, ge, diff));


    // --y;
    // if (y < 0) { y = 0; }
    // mvprintw(y, 1, "Use the arrow keys to move up and down. Press enter to flip.");
    // refresh();
}


GameEngine::~GameEngine()
{
    std::vector<Entity*>::iterator iter;
    for (iter = entities.begin(); iter != entities.end(); ++iter) {
        delete *iter;
    }
}


void GameEngine::loop()
{
    while (!gameOver)
    {
        for (size_t i = 0; i < entities.size(); ++i)
        {
            //Each entity takes a turn
            entities.at(i)->takeTurn(i == 0);
            //Wait for 1 second
            sleep(1);

            //Determine if there is a winner
            if (entities.at(i)->stackSorted())
            {
                if (i == 0) { ++winner; }
                else { --winner; }

                gameOver = true;
            }
        }
        if (gameOver) { calculateScore(); }
    }
}


int GameEngine::getScore() { return score; }


int GameEngine::getWinner() { return winner; }


void GameEngine::calculateScore()
{
    switch(winner) {
		//Human winner
		case -1: 
			score = n;
			break;
		//Tie 
		case 0:
			score =  n * (diff + 1);
			break;
         //AI winner   
		case 1:
			score = 2 * n * (diff + 1);
			break;
	}
}
