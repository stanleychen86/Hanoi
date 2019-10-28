#include "pancakestack.h"

PancakeStack::PancakeStack(Vector<int> order, Simple_window* win) : order(order), win(win) {}


PancakeStack::~PancakeStack()
{
    /*
    wclear(win);
    delwin(win);
    */
    Fl::delete_widget(win);
}


//Flip the order of pancakes
void PancakeStack::flip(int index)
{
    std::reverse(order.begin(), order.begin() + index);
}


//Blink pancakes for three seconds
//If all is false, then will only blink the pancake at index - used for displaying hint
void PancakeStack::blink(int index, bool all)  // Collin B
{
    /*
    int row, col;
    getmaxyx(win, row, col);
    int y = (row - 27) / 2;
    if (y < 0) { y = 0; }
    int x = col/2; 

    //loop from 0 to index, drawing pancakes
    if (all) {
        for (int i = 0; i < index; i++)
        {
            int length = (order.at(i) * 2) + 1;

            int x1 = x - (length / 2);

            mvwchgat(win, y, x1, length, A_BLINK, 0, NULL);
            mvwchgat(win, y + 1, x1, length, A_BLINK, 0, NULL);
            mvwchgat(win, y + 2, x1, length, A_BLINK, 0, NULL);
            y += 3;
        }
        wrefresh(win);
        sleep(3);
    }
    else {
        y += ((index - 1) * 3);
        int length = (order.at(index - 1) * 2) + 1;

        int x1 = x - (length / 2);

        mvwchgat(win, y, x1, length, A_BLINK, 0, NULL);
        mvwchgat(win, y + 1, x1, length, A_BLINK, 0, NULL);
        mvwchgat(win, y + 2, x1, length, A_BLINK, 0, NULL);
        wrefresh(win);
        sleep(2);
    } //

    // loop 0 to 5 (blink 5 times)
    for (int i=0; i<5; i++) {
        // loop through Pancake Widgets from 0 to index
        for (int j=0; j<index; j++) {
            // hide the pancake
            // pancakes is a vector of Widgets
            pancakes.at(j).hide();
        }
        // pause to give time to the blink
        sleep(0.25);
        // loop through Pancake Widgets from 0 to index
        for (int j=0; j<index; j++) {
            // hide the pancake
            // pancakes is a vector of Widgets
            pancakes.at(j).show();
        }
    }
    */
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 5 * 100000000;
    for (int i = 0; i < 3; ++i)
    {
        for (int i = 0; i < index; ++i)
        {
            win->detach(*(pancakes.at(i)));
        }
        Fl::redraw();
        Fl::flush();
        nanosleep(&ts, NULL);
        for (int i = 0; i < index; ++i)
        {
            win->attach(*(pancakes.at(i)));
        }
        Fl::redraw();
        Fl::flush();
        nanosleep(&ts, NULL);
    }
}


void PancakeStack::draw(bool isPlayer)
{
    for (int i=0; i<pancakes.size(); i++){
        win->detach(*(pancakes.at(i)));
    }
    pancakes.clear();

    int ht = 20;
    int start_x = 150;
    int start_y = 80;
    int max_sz = order.size();
    if (!isPlayer) start_x += 300;

    for (int i=0; i<order.size(); i++) {
        int wd = order.at(i) * 16; 
        int rect_x = start_x - wd/2;
        Rectangle* rect = new Rectangle(Point(rect_x, start_y + 2 * i * ht), wd, ht);
        rect->set_color(Color::black);
        rect->set_fill_color(Color::dark_yellow);
        pancakes.push_back(rect);
        win->attach(*rect);
    }
    Fl::redraw();
    Fl::flush();
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
Vector<int> PancakeStack::getOrder()
{
    return order;
}


//Display the minimum number of required flips to put the pancake stack in order
void PancakeStack::displayMinSteps()  // Collin B
{
    /*
    int row, col;
    getmaxyx(stdscr, row, col);
    int y = (row - 33) / 2 - 1;
    if (y < 0) { y = 0; }
    
    move(y, 0);          // move to begining of line
    clrtoeol();          // clear to end of line

    Vector<int>* solution_vector = find_solution(order);
    int min_flips = solution_vector->size();
    delete solution_vector;

    mvprintw(y, 1, "Minimum Flips Required: %d", min_flips);
    refresh();
    */

    // Calculate min_flips
    /*Vector<int>* solution_vector = find_solution(order);
    int min_flips = solution_vector->size();
    delete solution_vector;

    // Find correct X and Y coord on window to print
    int x = x_sz / 10;
    int y = y_sz / 10;

    // print min_flips to screen & redraw
    string to_print = "Minimum Flips Required: "+ min_flips;
    win->fl_draw(to_print, x, y);
    */
}



//Returns the recommended pancake index to flip next
int PancakeStack::requestHint()
{
    /*
    //Function is called when player presses hint button
    Vector<int>* solution_vector = find_solution(order);
    int hint = solution_vector->at(0);
    delete solution_vector;
    
    return hint;
    */
}

