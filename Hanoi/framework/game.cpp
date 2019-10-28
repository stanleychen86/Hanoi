#include "game.h"

Game::Game() : gameFinished(false) {}


void Game::run()
{
    initscr(); //Start curses mode
    keypad(stdscr, TRUE); //We get F1, F2 etc..
    cbreak(); //Line buffering disabled	

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);

    while (!gameFinished)
    {
        displaySplash();
        //Configs comprise <n, diff>
        std::pair<int,int> configs = requestConfigs();
        std::vector<int> order = requestInitState(configs.first);
        readAndDisplayHighScores();
        requestAndDisplayInitials();

        //Creates new instance of GameEngine with config info
        GameEngine* e = new GameEngine(order, configs.first, configs.second);
        e->loop();
        int score = e->getScore();
        int winner = e->getWinner();
        delete e;

        displayGameOver(score, winner);
        sortAndWriteHighScores(score);
    }

    endwin(); //End curses mode
}


//Show the splash screen
void Game::displaySplash(){
    // Don't echo() while we do getch
    noecho();
    attron(COLOR_PAIR(6));
    mvprintw(2, 10, "_________                              __");
    mvprintw(3, 10, "\\______  \\______   ____   ____ _____  |  | __ ____   ____");
    mvprintw(4, 10, "|     ___/ \\__  \\ /    \\_/ ___ \\__  \\ |  |/ // __ \\ /  ___/");
    mvprintw(5, 10, "|    |     / __ \\|   |  \\  \\___ / __ \\|     <\\  ___/ \\___ \\");
    mvprintw(6, 10, "|____|    (____  /___|  /\\___  >____  /__|_  /\\___  >____  >");
    mvprintw(7, 10, "	   	 \\/     \\/     \\/     \\/     \\/     \\/     \\/");
    attroff(COLOR_PAIR(6));
    attron(A_UNDERLINE);
    mvprintw(9, 22, "666666666666666666666666666666666666");
    attroff(A_UNDERLINE);
    mvprintw(11, 37, "Team 6");
    mvprintw(12, 36, "Members:");
    mvprintw(13, 27, "Andrew Wong, Omar Ramirez,");
    mvprintw(14, 29, "Roby Nkwamo, Yumei Li");
    attron(COLOR_PAIR(2) | A_BOLD | A_BLINK);
    mvprintw(16, 29, "Press Enter to Start");
    attroff(COLOR_PAIR(2) | A_BOLD | A_BLINK);
    refresh();

    int ch = getch();
    while (ch != 10) { ch = getch(); }
    clear();
    refresh();

    displayInstr();
    echo();
}


//Get config info n(number of pancakes) and diff(strength of AI) from user
std::pair<int, int> Game::requestConfigs()
{
    std::pair<int, int> nAndDiff;
    int n, diff, row, col;
    char pancakePrompt[] = "Enter number of pancakes (2-9): "; /* message to be appeared on the screen */
    char diffPrompt[] = "Enter difficulty level (2-9): ";      /* message to be appeared on the screen */
    char numPancakes[100], levelofDiff[100];

    getmaxyx(stdscr, row, col); /* get the number of rows and columns */
    
    bool inputValid = false;
    while (!inputValid)
    {
        mvprintw(row / 2 - 2, (col - strlen(pancakePrompt)) / 2, "%s", pancakePrompt);
        getstr(numPancakes);
        mvprintw(row / 2, (col - strlen(diffPrompt)) / 2, "%s", diffPrompt);
        getstr(levelofDiff);

        sscanf(numPancakes, "%d", &n);
        sscanf(levelofDiff, "%d", &diff);
        inputValid = checkConfigs(n, diff, numPancakes, levelofDiff);
        clear();
        refresh();
    }
    nAndDiff = std::make_pair (n,diff);

    return nAndDiff;
}

//Allow user to specify the initial state (must consist of numbers 1 through n) or to request a random order
std::vector<int> Game::requestInitState(int n)
{
    std::string seq = requestSeq(n);
    return createSeq(seq, n);
}


//READ .TXT FILE WITH 5 HIGHSCORES AND DISPLAY THEM
void Game::readAndDisplayHighScores()
{
	std::string name;
	int score;
	std::ifstream myfile ("scores.txt");
	if (myfile.is_open()){
		while(myfile >> name >> score){
				std::pair <std::string, int> pairScore =  make_pair(name, score);
				highscores.push_back(pairScore);
				
		}
		myfile.close();
	}
	else{
		printw("scores.txt does not exist. Check your directory.");
        getch();
        abort();
	}
    mvprintw(10, 10, " _   _ ___ ____ _   _   ____   ____ ___  ____  _____ ____");
    mvprintw(11, 10, "| | | |_ _/ ___| | | | / ___| / ___/ _ \\|  _ \\| ____/ ___|");
    mvprintw(12, 10, "| |_| || | |  _| |_| | \\___ \\| |  | | | | |_) |  _| \\___ \\");
    mvprintw(13, 10, "|  _  || | |_| |  _  |  ___) | |__| |_| |  _ <| |___ ___) |");
    mvprintw(14, 10, "|_| |_|___\\____|_| |_| |____/ \\____\\___/|_| \\_\\_____|____/");
    int x = 34;
    for (unsigned i = 0; i < highscores.size(); ++i)
    {
        int x1 = x + 8;
        mvprintw(16+i, x, "%d. %s", i + 1, highscores[i].first.c_str());
        if (highscores[i].second > 99) { --x1; }
        else if (highscores[i].second < 10) { ++x1; }
        mvprintw(16 + i, x1,"%d", highscores[i].second);
    }
    refresh();
}


//ASK FOR USER INITIALS AND DISPLAY THEM BELOW HIGH SCORES
void Game::requestAndDisplayInitials()
{
    move(16 + highscores.size(),34);
    int y, x;            // to store where you are
    getyx(stdscr, y, x); // save current pos
	
	char str[100];
    bool inputValid = false;
    while (!inputValid) {

        printw("Enter initials: ");
	    getstr(str);
        inputValid = checkInitials(str);
        
	    move(y, 0);          // move to begining of line
        clrtobot();          // clear to bottom of screen
        move(y, x);          // move back to where you were
    }
    
    std::string s(str);
	initials = s;	

    attron(COLOR_PAIR(3));
	printw("%d. %s    0\n", highscores.size()+1, str); 
    attroff(COLOR_PAIR(3));

    mvprintw(18 + highscores.size(), 26, "Press any key to continue...");
	refresh();
    getch();
    clear();
    refresh();
	
}


//Display game over message and player score
//Ask player if they want to play again or quit
void Game::displayGameOver(int score, int winner)
{
    noecho();
    attron(COLOR_PAIR(6));
    mvprintw(2, 9, "  _____          __  __ ______    ______      ________ _____");
    mvprintw(3, 9, " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\");
    mvprintw(4, 9, "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
    mvprintw(5, 9, "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /");
    mvprintw(6, 9, "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\");
    mvprintw(7, 9, " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
    attroff(COLOR_PAIR(6));
    refresh();
    switch (winner)
    {
    case -1:
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(10, 38, "DEFEAT");
        attroff(COLOR_PAIR(1) | A_BOLD);
        break;
    case 0:
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(10, 37, "DRAW");
        attroff(COLOR_PAIR(4));
        break;
    case 1:
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(10, 37, "VICTORY");
        attroff(COLOR_PAIR(2) | A_BOLD);
        
        break;
    }
    attron(COLOR_PAIR(3));
    mvprintw(11, 36, "SCORE: %d", score);
    attroff(COLOR_PAIR(3));
    refresh();

    endingSelection();
    clear();
    refresh();
    echo();
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
		printw("scores.txt does not exist. Check your directory.");
        getch();
        abort();
	}
	highscores.clear();
}


//Display the instructions
void Game::displayInstr() 
{
    attron(COLOR_PAIR(5) | A_BOLD);
    mvprintw(1, 34, "INSTRUCTIONS");
    attroff(COLOR_PAIR(5) | A_BOLD);
    mvprintw(3, 10, "The goal of the game is to get the pancake stack into order");
    mvprintw(4, 10, "(from smallest on top to largest on bottom) by repeatedly");
    mvprintw(5, 10, "flipping over a top-partial stack of some number of pancakes.");
    mvprintw(6, 10, "Try to flip the stack into order before the opponent!");

    mvprintw(8, 26, "Press any key to continue...");


    refresh(); /* Print onto the real screen */
    getch();
    clear();
    refresh();
}


//Check validity of config input
bool Game::checkConfigs(int n, int diff, std::string nString, std::string diffString)
{
    bool check = true;

    if (n < 2 || n > 9) { check = false; }

    if (diff < 2 || diff > 9) { check = false; }

    std::string::const_iterator it1 = nString.begin();
    while (it1 != nString.end() && std::isdigit(*it1)) { ++it1; }
    if (it1 != nString.end()) {
        check = false;
    }

    std::string::const_iterator it2 = diffString.begin();
    while (it2 != diffString.end() && std::isdigit(*it2)) { ++it2; }
    if (it2 != diffString.end()) {
        check = false;
    }
    return check;
}


// Prompt for user-specified sequence or random sequence
std::string Game::requestSeq(int n)
{
	char seqPrompt1[]="Enter a pancake sequence(e.g. 12345)";
    char seqPrompt2[]="or \"r\" for a random sequence: ";
	char seqPancakes[100];

	int row,col;				
	getmaxyx(stdscr,row,col);		/* get number of rows and columns */

    bool inputValid = false;
    while(!inputValid) {
        mvprintw(row / 2 - 3, (col-strlen(seqPrompt1))/2, "%s", seqPrompt1);
        mvprintw(row / 2 - 2, (col-strlen(seqPrompt2))/2, "%s", seqPrompt2);
	    getstr(seqPancakes);
        inputValid = checkSeq(seqPancakes, n);
        if (!inputValid) { getch(); }
        clear();
        refresh();
    }
	return seqPancakes;
}


//Check validity of sequence input
bool Game::checkSeq(std::string seq, int n) 
{
    bool check = true;

    int offsety = 0;
    int row,col;
    getmaxyx(stdscr, row, col);

    if ((seq == "r") | (seq == "R")) { return true; }

    if (seq.length() != n) {
        char msg1[] = "Sequence length must match number of pancakes";
        mvprintw(row / 2 + offsety, (col - strlen(msg1)) / 2, msg1);
        offsety +=2;
        check = false;
    }

    std::string::const_iterator it = seq.begin();
    while (it != seq.end() && (((int)*it - '0') >= 1) && (((int)*it - '0') <= n)) { ++it; }
    if (it != seq.end()) {
        char msg2[] = "Sequence must only contain numbers from 1 to n(number of pancakes)";
        mvprintw(row / 2 + offsety, (col - strlen(msg2)) / 2, msg2);
        offsety +=2;
        check = false;
    }

    std::string seqCopy(seq);
    std::sort(seqCopy.begin(), seqCopy.end());
    for (int i = 0; i < seqCopy.length() - 1; ++i) {
        if (seqCopy[i] == seqCopy[i + 1]) {
            char msg3[] = "Sequence must not contain repeated numbers";
            mvprintw(row / 2 + offsety, (col - strlen(msg3)) / 2, msg3);
            offsety +=2;
            check = false;
            break;
        }
    }
    return check;
}

//Generate the appropriate pancake sequence
std::vector<int> Game::createSeq(std::string seq, int n) 
{
    std::vector<int> sequence;
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
		    std::string currElem(1,seq.at(i));
		    currNum =  std::stoi(currElem);
		    sequence.push_back(currNum);
	    }
    }
    return sequence;
}


//Check validity of initials input
bool Game::checkInitials(std::string initials) 
{
    bool check = true;

    if (initials.length() != 2) {
        check = false;
    }

    std::string::const_iterator it = initials.begin();
    while (it != initials.end() && std::isalpha(*it)) { ++it; }
    if (it != initials.end()) {
        check = false;
    }
    return check;
}


//Give player the choice to play again or quit
void Game::endingSelection() {
    int highlight = 1;
	int choice = 0;
	int c;
    int num_choices = 2;

    flushinp(); //Flush typeahead buffer
    endingMenu(num_choices, highlight);
    while (1)
    {
        c = getch();
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = num_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == num_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        }
        endingMenu(num_choices, highlight);
        if (choice != 0) /* User selected a choice, break out of the infinite loop */
            break;
    }
    if (choice == 1) { gameFinished = false; }
    else if (choice == 2) { gameFinished = true;}
}


//Print the ending menu
void Game::endingMenu(int num_choices, int highlight)
{
    char *choices[] = {
        "Play Again",
        "Quit"};

    int x, y;	

	x = 35;
	y = 15;

	for(int i = 0; i < num_choices; ++i)
	{	if (highlight == i + 1) /* Highlight the present choice */
		{	attron(A_REVERSE); 
			mvprintw(y, x, "%s", choices[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y, x, "%s", choices[i]);
		y += 2;
	}
	refresh();
}


//Comparison function for comparing highscores
bool pairCompare(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second)
{
    return first.second > second.second;
}
