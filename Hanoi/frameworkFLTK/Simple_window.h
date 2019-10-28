
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Simple_window : Graph_lib::Window {
    Simple_window(Point xy, int w, int h, const string& title );

    bool wait_for_button(); // simple event loop
    
    Vector<Button*> choice_buttons;
    int getSelect();

    Button playagain_button;
    Button quit_button;
    bool getFinished();

    Button next_button2;

    Button enter_button1;
    Button enter_button2;
    Button enter_button3;
    Button continue_button;
    
private:
    Button next_button;     // the "next" button
    bool button_pushed;     // implementation detail

    static void cb_next(Address, Address); // callback for next_button
    void next();            // action to be done when next_button is pressed

    static void cb_choice1(Address, Address);
    void choice1();
    static void cb_choice2(Address, Address);
    void choice2();
    static void cb_choice3(Address, Address);
    void choice3();
    static void cb_choice4(Address, Address);
    void choice4();
    static void cb_choice5(Address, Address);
    void choice5();
    static void cb_choice6(Address, Address);
    void choice6();
    static void cb_choice7(Address, Address);
    void choice7();
    static void cb_choice8(Address, Address);
    void choice8();
    static void cb_choice9(Address, Address);
    void choice9();
    int select;

    static void cb_playagain(Address, Address);
    void playagain(); 
    static void cb_quit(Address, Address);
    void quit(); 
    bool finished;

    static void cb_enter(Address, Address);
    void enter();

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
