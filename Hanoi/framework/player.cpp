#include "player.h"

Player::Player(const std::vector<int>& p_order, WINDOW* p_win) : Entity(p_order, p_win), win(p_win), pointer_index(1) { p.displayMinSteps(); }


//Return the index of the pancake in stack to flip
int Player::select()
{
    //Call p.requestHint() when player presses hint button

    keypad(win, TRUE); //We get F1, F2 etc..

    flushinp(); //Flush typeahead buffer
    int ch;
    drawPointer();
    while(1)
	{	
        ch = wgetch(win);
		switch(ch)
		{	
            case KEY_UP:
                drawPointer(false);
                if (pointer_index == 1) { pointer_index = p.getOrder().size(); }
                else { --pointer_index; }
                drawPointer();
				break;
			case KEY_DOWN:
                drawPointer(false);
                if (pointer_index == p.getOrder().size()) { pointer_index = 1; }
                else { ++pointer_index; }
                drawPointer();
				break;
            case 72:
            case 104:
                p.blink(p.requestHint(), false);
                p.draw();
                drawPointer();
                flushinp(); //Flush typeahead buffer
                break;
		}
		if (ch == 10) { break; }
	}	
    drawPointer(false);

    return pointer_index;
}


void Player::takeTurn()
{
    Entity::takeTurn();
    p.displayMinSteps();
}


//Draw visual pointer to pancake - if draw == false, then erase instead
void Player::drawPointer(bool draw)
{
    int row, col;
    getmaxyx(win, row, col);
    int y = (row - 27) / 2;
    if (y < 0) { y = 0; }
    y += ((pointer_index-1) * 3) + 1;

    int length = (p.getOrder().at(pointer_index-1) * 2) + 1;
    int x1 = (col - length) / 2 - 1;
    int x2 = (col + length) / 2 + 2;
    
    if (draw) {
        mvwaddch(win, y, x1, ACS_RARROW);
        mvwaddch(win, y, x2, ACS_LARROW);
    }
    else {
        mvwaddch(win, y, x1, ' ');
        mvwaddch(win, y, x2, ' ');
    }
    wrefresh(win);
}
