/*
   Simple_window.cpp
   Minimally revised for C++11 features of GCC 4.6.3 or later
   Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
    next_button(Point(x_max()-70,0), 70, 20, "Next", cb_next),
    button_pushed(false),
    select(1),
    playagain_button(Point(185, 300), 100, 35, "Play Again", cb_playagain),
    quit_button(Point(315, 300), 100, 35, "Quit", cb_quit),
    finished(false),
    next_button2(Point(0,0), x_max(), y_max(), "", cb_next),
    enter_button1(Point(255,300), 90, 30, "Enter", cb_enter),
    enter_button2(Point(255,275), 90, 30, "Enter", cb_enter),
    enter_button3(Point(255,275), 90, 30, "Enter", cb_enter),
    continue_button(Point(255,275), 90, 30, "Continue", cb_next)
{
    choice_buttons.push_back(new Button(Point(20,80), 50, 20, ">", cb_choice1));
    choice_buttons.push_back(new Button(Point(20,120), 50, 20, ">", cb_choice2));
    choice_buttons.push_back(new Button(Point(20,160), 50, 20, ">", cb_choice3));
    choice_buttons.push_back(new Button(Point(20,200), 50, 20, ">", cb_choice4));
    choice_buttons.push_back(new Button(Point(20,240), 50, 20, ">", cb_choice5));
    choice_buttons.push_back(new Button(Point(20,280), 50, 20, ">", cb_choice6));
    choice_buttons.push_back(new Button(Point(20,320), 50, 20, ">", cb_choice7));
    choice_buttons.push_back(new Button(Point(20,360), 50, 20, ">", cb_choice8));
    choice_buttons.push_back(new Button(Point(20,400), 50, 20, ">", cb_choice9));
    //attach(next_button); 
}

//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void Simple_window::cb_next(Address, Address pw)
// call Simple_window::next() for the window located at pw
{  
    reference_to<Simple_window>(pw).next();    
}

//------------------------------------------------------------------------------

void Simple_window::next()
{
    button_pushed = true;
    hide();
}

//------------------------------------------------------------------------------

void Simple_window::cb_choice1(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice1();    
}

void Simple_window::cb_choice2(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice2();    
}

void Simple_window::cb_choice3(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice3();    
}

void Simple_window::cb_choice4(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice4();    
}

void Simple_window::cb_choice5(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice5();    
}

void Simple_window::cb_choice6(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice6();    
}

void Simple_window::cb_choice7(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice7();    
}

void Simple_window::cb_choice8(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice8();    
}

void Simple_window::cb_choice9(Address, Address pw)
{  
    reference_to<Simple_window>(pw).choice9();    
}


void Simple_window::choice1() {
    select = 1;
    button_pushed = true;
}

void Simple_window::choice2() {
    select = 2;
    button_pushed = true;
}

void Simple_window::choice3() {
    select = 3;
    button_pushed = true;
}

void Simple_window::choice4() {
    select = 4;
    button_pushed = true;
}

void Simple_window::choice5() {
    select = 5;
    button_pushed = true;
}

void Simple_window::choice6() {
    select = 6;
    button_pushed = true;
}

void Simple_window::choice7() {
    select = 7;
    button_pushed = true;
}

void Simple_window::choice8() {
    select = 8;
    button_pushed = true;
}

void Simple_window::choice9() {
    select = 9;
    button_pushed = true;
}


int Simple_window::getSelect() { return select; }



void Simple_window::cb_playagain(Address, Address pw)
{  
    reference_to<Simple_window>(pw).playagain();    
}

void Simple_window::cb_quit(Address, Address pw)
{  
    reference_to<Simple_window>(pw).quit();    
}


void Simple_window::playagain() {
    finished = false;
    button_pushed = true;
    hide();
}

void Simple_window::quit() {
    finished = true;
    button_pushed = true;
    hide();
}

bool Simple_window::getFinished() { return finished; }



void Simple_window::cb_enter(Address, Address pw)
{  
    reference_to<Simple_window>(pw).enter();    
}

void Simple_window::enter()
{
    button_pushed = true;
}