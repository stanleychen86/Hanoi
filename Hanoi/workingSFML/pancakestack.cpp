#include "pancakestack.h"

PancakeStack::PancakeStack(std::vector<int> order, sf::RenderWindow& win, GameEntities& ge) : order(order), win(win), ge(ge) {}


PancakeStack::~PancakeStack() {}


//Flip the order of pancakes
void PancakeStack::flip(int index, bool isPlayer)
{
    std::reverse(order.begin(), order.begin() + index);
	ge.set_order(isPlayer, order);
	ge.create_pancakes(isPlayer);
}


//Blink pancakes for three seconds
//If all is false, then will only blink the pancake at index - used for displaying hint
void PancakeStack::blink(int index, bool isPlayer)
{
	ge.blink(index, isPlayer);
    // int row, col;
    // getmaxyx(win, row, col);
    // int y = (row - 27) / 2;
    // if (y < 0) { y = 0; }
    // int x = col/2; 

    //loop from 0 to index, drawing pancakes
    //if (isPlayer) {
        // for (int i = 0; i < index; i++)
        // {
        //     int length = (order.at(i) * 2) + 1;

        //     int x1 = x - (length / 2);

        //     mvwchgat(win, y, x1, length, A_BLINK, 0, NULL);
        //     mvwchgat(win, y + 1, x1, length, A_BLINK, 0, NULL);
        //     mvwchgat(win, y + 2, x1, length, A_BLINK, 0, NULL);
        //     y += 3;
        // }
        // wrefresh(win);
        // sleep(3);
    //}
    //else {
        // y += ((index - 1) * 3);
        // int length = (order.at(index - 1) * 2) + 1;

        // int x1 = x - (length / 2);

        // mvwchgat(win, y, x1, length, A_BLINK, 0, NULL);
        // mvwchgat(win, y + 1, x1, length, A_BLINK, 0, NULL);
        // mvwchgat(win, y + 2, x1, length, A_BLINK, 0, NULL);
        // wrefresh(win);
        // sleep(2);
    //}
}


void PancakeStack::draw()
{
    // wclear(win);

    // int row, col;
    // getmaxyx(win, row, col);
    // //27 = height of pancake stack
    // int y = (row - 27) / 2;
    // if (y < 0) { y = 0; }
    // int x = col/2; 

    // for (size_t i = 0; i < order.size(); i++)
    // {
    //     int length = (order.at(i) * 2) + 1; 
    //     char num = '0' + order.at(i);

    //     int x1 = x - (length / 2);
    //     int x2 = x + (length / 2);

    //     mvwhline(win, y, x1 + 1, '-', length - 2);
    //     mvwhline(win, y + 2, x1 + 1, '-', length - 2);
    //     mvwvline(win, y, x1, '+', 3);
    //     mvwvline(win, y, x2, '+', 3);
    //     mvwvline(win, y + 1, x1, '|', 1);
    //     mvwvline(win, y + 1, x2, '|', 1);
    //     mvwhline(win, y + 1, x, num, 1);

    //     y += 3;
    // }

    // wrefresh(win);


    win.clear(sf::Color::White);
    ge.drawEntities();
    win.display();
}


bool PancakeStack::isSorted()
{
    for (size_t i = 0; i < order.size() - 1; ++i) {
        if (order.at(i) > order.at(i+1)) { return false; }
    }
    return true;
    //if (find_solution(order).size() == 0) return true; else false;
    //OR return std::is_sorted(order.begin(), order.end())
}


//Get the pancake order
std::vector<int> PancakeStack::getOrder()
{
    return order;
}


//Display the minimum number of required flips to put the pancake stack in order
void PancakeStack::displayMinSteps()
{
    // int row, col;
    // getmaxyx(stdscr, row, col);
    // int y = (row - 33) / 2 - 1;
    // if (y < 0) { y = 0; }
    
    // move(y, 0);          // move to begining of line
    // clrtoeol();          // clear to end of line

    // std::vector<int>* solution_vector = find_solution(order);
    // int min_flips = solution_vector->size();
    // delete solution_vector;

    // mvprintw(y, 1, "Minimum Flips Required: %d", min_flips);
    // refresh();
}



//Returns the recommended pancake index to flip next
int PancakeStack::requestHint()
{
    // //Function is called when player presses hint button
    // std::vector<int>* solution_vector = find_solution(order);
    // int hint = solution_vector->at(0);
    // delete solution_vector;
    
    // return hint;
    return 1;
}

