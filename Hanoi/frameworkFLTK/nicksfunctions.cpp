#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"

//using namespace std;

bool gameFinished;

Vector<std::pair<String,int>> highscores;

Simple_window end_window(Point(100,200), 400, 300, "End Game Menu");

static void play_again_cb(Address, Address) {
	gameFinished = false;
	Text *msg = new Text(Point(120,100),"Press Next to play again.");
	end_window.attach(*msg);
	Fl::redraw();
}

static void quit_cb(Address, Address) {
	gameFinished = true;
	Text *msg = new Text(Point(140,100), "Press Next to quit.");
	end_window.attach(*msg);
	Fl::redraw();
}

void Game::endingMenu()
{
	String play_again_msg("Would you like to play again?");
	Text warning(Point(100,60), String("ONLY PRESS A BUTTON ONCE."));
	Button play_again(Point(150, 140), 100, 40, "Play Again", play_again_cb);
	Button quit(Point(150, 220), 100, 40, "Quit", quit_cb);
	Text playagain(Point(100,40), play_again_msg);
	end_window.attach(playagain); end_window.attach(play_again); end_window.attach(quit); end_window.attach(warning);
	end_window.show();
	end_window.wait_for_button();
}

void Game::readAndDisplayHighScores()
{
    Simple_window hs_window(Point(100,200), 400, 300, "High Scores");
	String name;
	int score;
	ifstream myfile ("scores.txt");
	if (myfile.is_open()){
		while(myfile >> name >> score){
			std::pair<String, int> pairScore =  std::make_pair(name, score);
			highscores.push_back(pairScore);		}
		myfile.close();}
	else{	Text ferror(Point(100,100), String("scores.txt does not exist. Check your directory.")); hs_window.attach(ferror);
		return; }
	Text score1(Point(150,50),String("1: " + highscores[0].first + "  " + to_string(highscores[0].second)));
	Text score2(Point(150,75),String("2: " + highscores[1].first + "  " + to_string(highscores[1].second)));
	Text score3(Point(150,100),String("3: " + highscores[2].first + "  " + to_string(highscores[2].second)));
	Text score4(Point(150,125),String("4: " + highscores[3].first + "  " + to_string(highscores[3].second)));
	Text score5(Point(150,150),String("5: " + highscores[4].first + "  " + to_string(highscores[4].second)));
	hs_window.attach(score1); hs_window.attach(score2); hs_window.attach(score3); hs_window.attach(score4); hs_window.attach(score5);
	Text closemsg(Point(80,225),"Press Next to close the window.");
	hs_window.attach(closemsg);
	hs_window.wait_for_button();
}

int main() {
	readAndDisplayHighScores();
	endingMenu();
	Fl::run();
	return 0;
}
