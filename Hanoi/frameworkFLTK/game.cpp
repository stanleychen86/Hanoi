#include "game.h"

Game::Game() : gameFinished(false) {}


void Game::run()
{
    while (!gameFinished)
    {
        displaySplash();
        //Configs comprise <n, diff>
        std::pair<int,int> configs = requestConfigs();
        Vector<int> order = requestInitState(configs.first);
        readAndDisplayHighScores();
        requestAndDisplayInitials();
        //Creates new instance of GameEngine with config info
        GameEngine* e = new GameEngine(order, configs.first, configs.second);
        e->loop();
        int score = e->getScore();
        int winner = e->getWinner();
        delete e;
        //int score, winner = 3;
        displayGameOver(score, winner);
        sortAndWriteHighScores(score);
        
    }
}


//Show the splash screen
void Game::displaySplash(){
    Simple_window win(Point(100,50),600,600,"Pancake Sorting Game");
	Image splashscreen(Point{0,0}, "pancake.jpg");
	win.attach(splashscreen);
	win.attach(win.next_button2);
	win.wait_for_button();
    displayInstr();
}


//Get config info n(number of pancakes) and diff(strength of AI) from user
std::pair<int, int> Game::requestConfigs()
{
    Simple_window win(Point(100,50),600,600,"Configurations");
    win.color(FL_WHITE);
    std::pair<int, int> nAndDiff;
    int n, diff = 0;
    string pancakePrompt = "Enter number of pancakes (2-9): "; /* message to be appeared on the screen */
    string diffPrompt = "Enter difficulty level (2-9): ";      /* message to be appeared on the screen */

    // In_box inPancakes(Point{400, 200}, 20, 30, pancakePrompt);
    // win1.attach(inPancakes);

    // In_box indiff(Point{400, 300}, 20, 30, diffPrompt);
    // win1.attach(indiff);

    win.attach(win.enter_button1);
    bool inputValid = false;
    while (!inputValid)
    {
        In_box inPancakes(Point{400, 175}, 18, 30, pancakePrompt);
        win.attach(inPancakes);

        In_box indiff(Point{400, 250}, 18, 30, diffPrompt);
        win.attach(indiff);
        win.wait_for_button();

        n = inPancakes.get_int();
        diff = indiff.get_int();
        inputValid = checkConfigs(n, diff, inPancakes.get_string(), indiff.get_string());
        win.detach(inPancakes);
        win.detach(indiff);
    }
    // win.hide();
    nAndDiff = std::make_pair (n,diff);
    return nAndDiff;
}

//Allow user to specify the initial state (must consist of numbers 1 through n) or to request a random order
Vector<int> Game::requestInitState(int n)
{
    String seq = requestSeq(n);
    return createSeq(seq, n);
}


//READ .TXT FILE WITH 5 HIGHSCORES AND DISPLAY THEM
void Game::readAndDisplayHighScores()
{
    Simple_window hs_window(Point(100, 50), 600, 600, "High Scores");
    hs_window.color(FL_WHITE);
    String name;
    int score;
    ifstream myfile("scores.txt");
    if (myfile.is_open())
    {
        while (myfile >> name >> score)
        {
            std::pair<String, int> pairScore = std::make_pair(name, score);
            highscores.push_back(pairScore);
        }
        myfile.close();
    }
    else
    {
        Text ferror(Point(100, 100), String("scores.txt does not exist. Check your directory."));
        hs_window.attach(ferror);
        hs_window.wait_for_button();
        abort();
    }

    Text highscore_text(Point(200, 40), "HIGHSCORES");
    highscore_text.set_color(Color::blue);
    highscore_text.set_font_size(30);
    hs_window.attach(highscore_text);

    // Vector<Text*> firstScores;
    // Vector<Text*> secondScores;
    int x = 255;
    for (size_t i = 0; i < highscores.size(); ++i) {
        int x1 = x + 65;
        Text* scoreFirst = new Text(Point(x, 100 + (25 * i)), to_string(i+1) + ".  " + highscores[i].first);
        if (highscores[i].second > 99) { x1 -= 9; }
        else if (highscores[i].second < 10) { x1 += 9; }
        Text* scoreSecond = new Text(Point(x1, 100 + (25 * i)), to_string(highscores[i].second));
        hs_window.attach(*scoreFirst);
        hs_window.attach(*scoreSecond);
        // firstScores.push_back(scoreFirst);
        // secondScores.push_back(scoreSecond);
    }

    // if (highscores.size() >= 1)
    // {
    //     Text score1(Point(260, 100 + (25 * 0)), "1. " + highscores[0].first + "  " + to_string(highscores[0].second));
    //     hs_window.attach(score1);
    // }

    String str = "";
    hs_window.attach(hs_window.enter_button3);
    bool inputValid = false;
    while (!inputValid) {
        In_box initialsInput(Point(350, 225), 35, 30, "Enter your initials: ");
        hs_window.attach(initialsInput);
        hs_window.wait_for_button();
        str = initialsInput.get_string();
        inputValid = checkInitials(str);
        hs_window.detach(initialsInput);
    }
    // hs_window.hide();
    initials = str;
    
}


//ASK FOR USER INITIALS AND DISPLAY THEM BELOW HIGH SCORES
void Game::requestAndDisplayInitials()
{
    Simple_window win(Point(100, 50), 600, 600, "Initials");
    win.color(FL_WHITE);

    Text highscore_text(Point(200, 40), "HIGHSCORES");
    highscore_text.set_color(Color::blue);
    highscore_text.set_font_size(30);
    win.attach(highscore_text);

    // Vector<Text*> firstScores;
    // Vector<Text*> secondScores;
    int x = 255;
    for (size_t i = 0; i < highscores.size(); ++i)
    {
        int x1 = x + 65;
        Text *scoreFirst = new Text(Point(x, 100 + (25 * i)), to_string(i + 1) + ".  " + highscores[i].first);
        if (highscores[i].second > 99)
        {
            x1 -= 9;
        }
        else if (highscores[i].second < 10)
        {
            x1 += 9;
        }
        Text *scoreSecond = new Text(Point(x1, 100 + (25 * i)), to_string(highscores[i].second));
        win.attach(*scoreFirst);
        win.attach(*scoreSecond);
        // firstScores.push_back(scoreFirst);
        // secondScores.push_back(scoreSecond);
    }

    Text my_score1(Point(255, 100 + (25 * highscores.size())), to_string(highscores.size() + 1) + ".  " + initials);
    Text my_score2(Point(255 + 74, 100 + (25 * highscores.size())), "0");
    win.attach(my_score1);
    win.attach(my_score2);
    win.attach(win.continue_button);
    win.wait_for_button();

    // Simple_window win1(Point(100, 50), 600, 600, "Initials");
    // Text highscores(Point(250, 20), "HIGHSCORES");
    // highscores.set_color(Color::blue);
    // win1.attach(highscores);
    // In_box box1(Point(187, 80), 40, 30, "Please Enter Your Initials: ");
    // win1.attach(box1);
    // String str;
    // win1.wait_for_button();
    // str = box1.get_string();
    // win1.detach(box1);
    // Out_box out1(Point(200, 80), 60, 30, "Player Initials Entered: ");
    // win1.attach(out1);
    // out1.put(str);
    // initials = str;
    // Text waitEnter(Point(220, 350), "Press any key to continue...");
    // waitEnter.set_color(Color::red);
    // win1.attach(waitEnter);
    // win1.show();
    // Fl::run();
}


//Display game over message and player score
//Ask player if they want to play again or quit
void Game::displayGameOver(int score, int winner)
{
    Simple_window* win = new Simple_window(Point(100,50),600,600,"Game Over");
    win->color(FL_BLACK);
    fl_color(0,255,255);
    Text start(Point(120,40),"┏━━━┓ ┏━━━┓ ┏━┓┏━┓ ┏━━━┓ ┏━━━┓ ┏┓    ┏┓ ┏━━━┓ ┏━━━┓");
    Text start1(Point(120,55),"┃┏━┓┃ ┃┏━┓┃ ┃┃┗┛┃┃ ┃┏━━┛ ┃┏━┓┃ ┃┗┓┏┛┃ ┃┏━━┛ ┃┏━┓┃");
    Text start2(Point(120,70),"┃┃  ┗┛ ┃┃  ┃┃ ┃┏┓┏┓┃ ┃┗━━┓ ┃┃  ┃┃ ┗┓┃┃┏┛ ┃┗━━┓ ┃┗━┛┃");
    Text start3(Point(120,85),"┃┃┏━┓ ┃┗━┛┃ ┃┃┃┃┃┃ ┃┏━━┛ ┃┃  ┃┃   ┃┗┛┃   ┃┏━━┛ ┃┏┓┏┛");
    Text start4(Point(120,100),"┃┗┻━┃ ┃┏━┓┃ ┃┃┃┃┃┃ ┃┗━━┓ ┃┗━┛┃   ┗┓┏┛   ┃┗━━┓ ┃┃┃┗┓");
    Text start5(Point(120,115),"┗━━━┛ ┗┛  ┗┛ ┗┛┗┛┗┛ ┗━━━┛ ┗━━━┛     ┗┛     ┗━━━┛ ┗┛┗━┛");
    win->attach(start);
    win->attach(start1);
    win->attach(start2);
    win->attach(start3);
    win->attach(start4);
    win->attach(start5);

    fl_color(255,255,255);
    Text winner1(Point(225,175),"DEFEAT");
    Text winner2(Point(240,175),"DRAW");
    Text winner3(Point(210,175),"VICTORY");
    winner1.set_font_size(40);
    winner2.set_font_size(40);

    winner3.set_font_size(40);
      if(winner == -1){
        win->attach(winner1);
      }
      else if(winner == 0){
        win->attach(winner2);
      }
      else if(winner == 1){
        win->attach(winner3);
      }

    int x = 230;
    if (score > 99) { x -= 10; }
    else if (score < 10) { x += 10; }
    Text score1(Point(x,210),"Score: " + to_string(score));
    score1.set_font_size(30);
    win->attach(score1);

    endingSelection(win);

}


void Game::sortAndWriteHighScores(int score)
{	
	highscores.push_back(make_pair(initials, score));
	std::stable_sort(highscores.begin(),highscores.end(), pairCompare);
	if (highscores.size() > 5) { highscores.pop_back(); }
	ofstream myfile("scores.txt");
	if (myfile.is_open()){
		for (unsigned i = 0; i < highscores.size(); ++i){
		myfile << highscores[i].first.c_str() << " " << highscores[i].second << endl;
		}
		myfile.close();
	}
	else{
		// printw("scores.txt does not exist. Check your directory.");
        // getch();
        abort();
	}
	highscores.clear();
}


//Display the instructions
void Game::displayInstr() 
{
  Simple_window win(Point(100,50),600,600,"Instructions");
  Image instructions(Point(0,0),"Instructions.jpg");
  win.attach(instructions);
  win.attach(win.next_button2);
  win.wait_for_button();
}


//Check validity of config input
bool Game::checkConfigs(int n, int diff, String nString, String diffString)
{
    bool check = true;

    if (n < 2 || n > 9) { check = false; }

    if (diff < 2 || diff > 9) { check = false; }

    String::const_iterator it1 = nString.begin();
    while (it1 != nString.end() && std::isdigit(*it1)) { ++it1; }
    if (it1 != nString.end()) {
        check = false;
    }

    String::const_iterator it2 = diffString.begin();
    while (it2 != diffString.end() && std::isdigit(*it2)) { ++it2; }
    if (it2 != diffString.end()) {
        check = false;
    }
    return check;
}


// Prompt for user-specified sequence or random sequence
String Game::requestSeq(int n)
{
    Simple_window w(Point(100,50),600,600, "Pancake Sequence");
    w.color(FL_WHITE);
    String seqPancakes = "";

    w.attach(w.enter_button2);
    bool inputValid = false;
    while(!inputValid) {
        Text start(Point(160, 210), "Enter a pancake sequence(e.g. 12345)");
        In_box cat_in(Point(360, 220), 90, 30, "or \"r\" for a random sequence: ");
        w.attach(start);
        w.attach(cat_in);   
        w.wait_for_button();
        seqPancakes = cat_in.get_string();
        inputValid = checkSeq(seqPancakes, n);
        w.detach(cat_in);
        w.detach(start);
    }
    // w.hide();
    return seqPancakes;
}


//Check validity of sequence input
bool Game::checkSeq(String seq, int n) 
{
    bool check = true;

    int offsety = 0;
    int row,col;
    // getmaxyx(stdscr, row, col);

    if ((seq == "r") | (seq == "R")) { return true; }

    //Sequence length must match number of pancakes
    if (seq.length() != n) {
        check = false;
    }

    //Sequence must only contain numbers from 1 to n(number of pancakes)
    String::const_iterator it = seq.begin();
    while (it != seq.end() && (((int)*it - '0') >= 1) && (((int)*it - '0') <= n)) { ++it; }
    if (it != seq.end()) {
        check = false;
    }

    //Sequence must not contain repeated numbers
    String seqCopy(seq);
    int length = seqCopy.length() - 1;
    std::sort(seqCopy.begin(), seqCopy.end());
    if (seqCopy.length() == 0) { length = 0; }
    for (int i = 0; i < length; ++i) {
        if (seqCopy[i] == seqCopy[i + 1]) {
            check = false;
            break;
        }
    }
    return check;
}


//Generate the appropriate pancake sequence
Vector<int> Game::createSeq(String seq, int n) 
{
    Vector<int> sequence;
	if ((seq == "r") | (seq == "R")) { 
        for (int i = 1; i <= n; ++i) {
            sequence.push_back(i);
        }
        //Generate random sequence
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (sequence.begin(), sequence.end(), std::default_random_engine(seed));
        std::next_permutation(sequence.begin(), sequence.end());
	}
	else {
        //Convert string sequence into number vector
		int currNum;
	    for(size_t i = 0; i < seq.length(); i++){
		    String currElem(1,seq.at(i));
		    currNum =  std::stoi(currElem);
		    sequence.push_back(currNum);
	    }
    }
    return sequence;
}


//Check validity of initials input
bool Game::checkInitials(String initials) 
{
    bool check = true;

    if (initials.length() != 2) {
        check = false;
    }

    String::const_iterator it = initials.begin();
    while (it != initials.end() && std::isalpha(*it)) { ++it; }
    if (it != initials.end()) {
        check = false;
    }
    return check;
}


//Give player the choice to play again or quit
void Game::endingSelection(Simple_window* win) {
    win->attach(win->playagain_button);
    win->attach(win->quit_button);

    win->wait_for_button();
    gameFinished = win->getFinished();
}


//Comparison function for comparing highscores
bool pairCompare(const std::pair<String, int>& first, const std::pair<String, int>& second)
{
    return first.second > second.second;
}
