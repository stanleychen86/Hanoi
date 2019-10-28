#include "player.h"

Player::Player(const Vector<int>& p_order, Simple_window* p_win) : Entity(p_order, p_win, true), win(p_win), pointer_index(1) { p.displayMinSteps(); }


//Return the index of the pancake in stack to flip
int Player::select()
{
    for (int i = 0; i < p.getOrder().size(); ++i) { win->attach(*(win->choice_buttons.at(i))); }
    Fl::redraw();
    win->wait_for_button();
    for (int i = 0; i < p.getOrder().size(); ++i) { win->detach(*(win->choice_buttons.at(i))); }
    Fl::redraw();
    return win->getSelect();
}


void Player::takeTurn(bool isPlayer)
{
    Entity::takeTurn(isPlayer);
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

    // int length = (p.getOrder().size().at(pointer_index-1) * 2) + 1;
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
