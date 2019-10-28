#include "gameengine.h"

GameEngine::GameEngine(const Vector<int>& p_order, int n, int diff) : gameOver(false), winner(0), score(0), n(n), diff(diff)
{
    Simple_window* win = new Simple_window(Point(100,50),600,600,"Game");
    win->color(FL_WHITE);
    entities.push_back(new Player(p_order, win));

    entities.push_back(new AI(p_order, win, diff));

    /*
    Simple_window win1(Point(100,200),600,600,"The pancake game");
    win1.color(FL_BLACK);
    fl_color(255,255,255);
    Text start(Point(5,20),"Press \"h\" to get a hint.");
    Text start1(Point(5,40),"Use the arrow keys to move up and down. Press enter to flip.");
    win1.attach(start);
    win1.attach(start1);
    win1.wait_for_button();
    */
}


GameEngine::~GameEngine()
{
    Vector<Entity*>::iterator iter;
    for (iter = entities.begin(); iter != entities.end(); ++iter) {
        delete *iter;
    }
    
    //clear();
    //refresh();
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
