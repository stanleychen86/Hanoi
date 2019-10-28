/*LIST OF FUNCTIONS THAT USE NCURSES*/
//Note: PancakeStack class has a ncurses WINDOW variable
//Note: PancakeStack, Entity, Player, and AI constructors have a WINDOW parameter

// 5 people can do 3 functions each, and one person will do 2 functions.

/*****GAME*****/
void displaySplash(); //medium
std::pair<int,int> requestConfigs(); //medium
void readAndDisplayHighScores(); //medium
void requestAndDisplayInitials(); //medium
void displayGameOver(int score, int winner); //medium
void displayInstr(); //easy
std::string requestSeq(int n); //medium
bool checkSeq(std::string seq, int n); //easy
void endingMenu(int num_choices, int highlight); //hard


/*****GAMEENGINE*****/
GameEngine(const std::vector<int>& p_order, int n, int diff); //medium


/*****PLAYER*****/
int select(); //hard
void drawPointer(bool draw = true); //hard


/*****PANCAKESTACK*****/
~PancakeStack(); //VERY easy
void blink(int index, bool all = true); //hard
void draw(); //hard
void displayMinSteps(); //easy
