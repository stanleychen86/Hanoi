#include "gameengine.h"

GameEngine::GameEngine(const std::vector<int>& p_order, int n, int diff) : gameOver(false), winner(0), score(0), n(n), diff(diff)
{
    noecho();

    int row, col;
    getmaxyx(stdscr, row, col);
    //33 = height of window
    int y = (row - 33) / 2;
    if (y < 0) { y = 0; }
    int x = col/2;

    WINDOW* left_win = newwin(33, x, y, 0);
    //if (demoGame) { AI demo(p_order, left_win, random number); } (demoGame will randomize n and diff)
    entities.push_back(new Player(p_order, left_win));

    WINDOW* right_win = newwin(33, x, y, x);
    entities.push_back(new AI(p_order, right_win, diff));

    y -= 2;
    if (y < 0) { y = 0; }
    mvprintw(y, 1, "Press \"h\" to get a hint.");

    --y;
    if (y < 0) { y = 0; }
    mvprintw(y, 1, "Use the arrow keys to move up and down. Press enter to flip.");
    refresh();
}


GameEngine::~GameEngine()
{
    echo();

    std::vector<Entity*>::iterator iter;
    for (iter = entities.begin(); iter != entities.end(); ++iter) {
        delete *iter;
    }
    
    clear();
    refresh();
}


void GameEngine::loop()
{
    while (!gameOver)
    {
        for (size_t i = 0; i < entities.size(); ++i)
        {
            //Each entity takes a turn
            entities.at(i)->takeTurn();
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
