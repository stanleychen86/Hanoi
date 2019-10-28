#include "game.h"

Game::Game() : gameFinished(false), win(sf::VideoMode(825, 800), "Pancake Sorting Game") {}


void Game::run()
{
	font.loadFromFile("Arial.ttf");
	while (!gameFinished)
	{
		displaySplash();
		//Configs comprise <n, diff>
		std::pair<int, int> configs = requestConfigs();
		std::vector<int> order = requestInitState(configs.first);
		readAndDisplayHighScores();
		requestAndDisplayInitials();

		//Creates new instance of GameEngine with config info
		GameEngine* e = new GameEngine(order, configs.first, configs.second, win);
		e->loop();
		int score = e->getScore();
		int winner = e->getWinner();
		delete e;

		displayGameOver(score, winner);
		sortAndWriteHighScores(score);
	}
	win.close();
}


//Show the splash screen
void Game::displaySplash()
{
	sf::Texture splash;
	sf::Sprite splashimg;
	bool isEnter = false;
	if (!splash.loadFromFile("splash.png"))
		std::printf("Could not load splash file \n");

	splashimg.setTexture(splash);

	//Start when user presses enter
	bool enterPressed = false;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				win.close();
				break;
				// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter) { enterPressed = true; }
				break;
				// we don't process other types of events
			default:
				break;
			}
		}
		win.clear();
		win.draw(splashimg);
		//window.draw(PressEntertoStartText);
		win.display();
		if (enterPressed) { break; }
	}


	// mvprintw(2, 10, "_________                              __");
	// mvprintw(3, 10, "\\______  \\______   ____   ____ _____  |  | __ ____   ____");
	// mvprintw(4, 10, "|     ___/ \\__  \\ /    \\_/ ___ \\__  \\ |  |/ // __ \\ /  ___/");
	// mvprintw(5, 10, "|    |     / __ \\|   |  \\  \\___ / __ \\|     <\\  ___/ \\___ \\");
	// mvprintw(6, 10, "|____|    (____  /___|  /\\___  >____  /__|_  /\\___  >____  >");
	// mvprintw(7, 10, "	   	 \\/     \\/     \\/     \\/     \\/     \\/     \\/");

	displayInstr();

	//TESTING SFML INITIALS
	// std::string s;
	// std::string test = "Please Enter Your Initials: ";
	// sf::Text text;
	// sf::Text other;
	// sf::Font font;

	// font.loadFromFile("Arial.ttf");
	// text.setFont(font);
	// other.setFont(font);
	// text.setFillColor(sf::Color::Red);
	// other.setFillColor(sf::Color::Red);

	// other.setString(test);

	// while(win.isOpen()){
	//     sf::Event event;
	//     while (win.pollEvent(event)){
	//         if (event.type == sf::Event::Closed)
	//             win.close();
	//         if (event.type == sf::Event::TextEntered){
	//             if(event.KeyPressed == sf::Keyboard::BackSpace && s.size()!=0){
	//                 s.pop_back();
	//             }
	//             else if (event.text.unicode < 128) {
	//                 s.push_back((char)event.text.unicode);
	//             }
	//         }
	//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	//             {
	//                 win.clear();
	//                 text.setString(s);
	//             }
	//     }
	//     win.clear();
	//     other.setString(test + s);
	//     win.draw(other);
	//     win.display();
	// }

/*
	std::string prompt = "Enter your initials: ";
	std::string input;
	sf::Text text;
	font.loadFromFile("Arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	bool enterPressed = false;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				win.close();
				break;
				// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Enter) { enterPressed = true; }
				break;
				// text entered
			case sf::Event::TextEntered:
				if (event.text.unicode == 8 && input.size() != 0) { input.pop_back(); }
				else if (event.text.unicode < 128 && event.text.unicode != 8) { input += static_cast<char>(event.text.unicode); }
				break;
				// we don't process other types of events
			default:
				break;
			}
		}
		win.clear(sf::Color::White);
		text.setString(prompt + input);
		win.draw(text);
		win.display();
		if (enterPressed) { break; }
	}
	initials = input;
	*/
}


//Get config info n(number of pancakes) and diff(strength of AI) from user
std::pair<int, int> Game::requestConfigs()
{
	std::pair<int, int> nAndDiff;
	int n = 0, diff = 0;

	std::string promptNum = "Enter number of pancakes (2-9): ";
	std::string promptDiff = "Enter difficulty level (2-9): ";

	sf::Text textNum;
	textNum.setFont(font);
	textNum.setFillColor(sf::Color::Red);
	textNum.setPosition(175, 250);

	sf::Text textDiff;
	textDiff.setFont(font);
	textDiff.setFillColor(sf::Color::Red);
	textDiff.setPosition(175, 350);

	bool inputValid = false;
	while (!inputValid)
	{
		std::string numPancakes;
		std::string levelofDiff;
		std::string inputNum;
		std::string inputDiff;
		int enterPresses = 0;
		while (win.isOpen())
		{
			sf::Event event;
			while (win.pollEvent(event))
			{
				// check the type of the event...
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					win.close();
					break;

					// key pressed
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Backspace && !inputNum.empty() && enterPresses == 0) { inputNum.pop_back(); }
					else if (event.key.code == sf::Keyboard::Backspace && !inputDiff.empty() && enterPresses == 1) { inputDiff.pop_back(); }
					else if (event.key.code == sf::Keyboard::Enter) { ++enterPresses; }
					break;

					// text entered
				case sf::Event::TextEntered:
					if (event.text.unicode == 8) { continue; }
					//if (event.text.unicode == 8 && !inputNum.empty() && enterPresses == 0) { inputNum.pop_back(); }
					else if (event.text.unicode < 128 && event.text.unicode != 10 && enterPresses == 0) { inputNum += static_cast<char>(event.text.unicode); }
					//else if (event.text.unicode == 8 && !inputDiff.empty() && enterPresses == 1) { inputDiff.pop_back(); }
					else if (event.text.unicode < 128 && event.text.unicode != 10 && enterPresses == 1) { inputDiff += static_cast<char>(event.text.unicode); }
					break;

					// we don't process other types of events
				default:
					break;
				}
			}
			win.clear(sf::Color::White);
			if (enterPresses == 0)
			{
				textNum.setString(promptNum + inputNum);
				textDiff.setString(promptDiff + levelofDiff);
				numPancakes = inputNum;
			}
			else if (enterPresses == 1)
			{
				textNum.setString(promptNum + numPancakes);
				textDiff.setString(promptDiff + inputDiff);
				levelofDiff = inputDiff;
			}
			win.draw(textNum);
			win.draw(textDiff);
			win.display();
			if (enterPresses == 2) { break; }
		}
		if (!numPancakes.empty() && isdigit(numPancakes.at(0))) { n = stoi(numPancakes); }
		if (!levelofDiff.empty() && isdigit(levelofDiff.at(0))) { diff = stoi(levelofDiff); }

		inputValid = checkConfigs(n, diff, numPancakes, levelofDiff);
	}
	nAndDiff = std::make_pair(n, diff);

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
	//font.loadFromFile("Arial.ttf");
	int count = 0;
	std::string name;
	int score;
	std::vector<sf::Text> scoresToPrint;
	std::ifstream myfile("scores.txt");
	if (myfile.is_open())
	{
		while (myfile >> name >> score)
		{
			std::pair<std::string, int> pairScore = make_pair(name, score);
			highscores.push_back(pairScore);
			sf::Text temp(std::to_string(count + 1) + ".  " + pairScore.first + "    " + std::to_string(pairScore.second), font);
			temp.setPosition(350, 150 + (50 * count));
			temp.setFillColor(sf::Color::Black);
			scoresToPrint.push_back(temp);
			count++;
		}
		myfile.close();
	}
	else
	{
		std::cout << "scores.txt does not exist. Check your directory." << std::endl;
		abort();
	}

	std::string prompt = "Enter your initials: ";
	std::string finalInput;

	sf::Text text;
	text.setPosition(275, 450);
	text.setFont(font);
	text.setFillColor(sf::Color::Red);

	sf::Text hscore("HIGH SCORES", font);
	hscore.setPosition(300, 30);
	hscore.setFillColor(sf::Color::Cyan);
	hscore.setStyle(sf::Text::Bold);

	bool inputValid = false;
	while (!inputValid)
	{
		std::string input;
		bool enterPressed = false;
		while (win.isOpen())
		{
			sf::Event event;
			while (win.pollEvent(event))
			{
				// check the type of the event...
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					win.close();
					break;

					// key pressed
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Backspace && !input.empty()) { input.pop_back(); }
					else if (event.key.code == sf::Keyboard::Enter) { enterPressed = true; }
					break;

					// text entered
				case sf::Event::TextEntered:
					if (event.text.unicode == 8) { continue; }
					//if (event.text.unicode == 8 && !input.empty()) { input.pop_back(); }
					else if (event.text.unicode < 128 && event.text.unicode != 10) { input += static_cast<char>(event.text.unicode); }
					break;

					// we don't process other types of events
				default:
					break;
				}
			}
			win.clear(sf::Color::White);
			text.setString(prompt + input);
			win.draw(text);
			win.draw(hscore);
			for (int i = 0; i < scoresToPrint.size(); i++) { win.draw(scoresToPrint.at(i)); }
			win.display();
			if (enterPressed) { break; }
		}
		inputValid = checkInitials(input);
		finalInput = input;
	}
	initials = finalInput;
}


//ASK FOR USER INITIALS AND DISPLAY THEM BELOW HIGH SCORES
void Game::requestAndDisplayInitials()
{
	//font.loadFromFile("Arial.ttf");
	std::vector<sf::Text> scoresToPrint;
	for (int i = 0; i < highscores.size(); ++i) {
		sf::Text temp(std::to_string(i + 1) + ".  " + highscores.at(i).first + "    " + std::to_string(highscores.at(i).second), font);
		temp.setPosition(340, 150 + (50 * i));
		temp.setFillColor(sf::Color::Black);
		temp.setFont(font);
		scoresToPrint.push_back(temp);
	}

	sf::Text anyKey;
	anyKey.setFont(font);
	anyKey.setString("Press any key to continue...");
	anyKey.setPosition(250, 450);
	anyKey.setFillColor(sf::Color::Red);

	sf::Text hscore("HIGH SCORES", font);
	hscore.setPosition(300, 30);
	hscore.setFillColor(sf::Color::Cyan);
	hscore.setStyle(sf::Text::Bold);

	sf::Text playerScore;
	playerScore.setPosition(340, 150 + (50 * highscores.size()));
	playerScore.setFillColor(sf::Color::Blue);
	playerScore.setFont(font);

	bool keyPressed = false;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				win.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				keyPressed = true;
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
		win.clear(sf::Color::White);
		for (int i = 0; i < scoresToPrint.size(); i++)
		{
			scoresToPrint.at(i).setFillColor(sf::Color::Black);
			win.draw(scoresToPrint.at(i));
		}
		playerScore.setString(std::to_string(highscores.size() + 1) + ".  " + initials + "      0");
		win.draw(playerScore);
		win.draw(anyKey);
		win.draw(hscore);
		win.display();
		if (keyPressed) { break; }
	}
}


//Display game over message and player score
//Ask player if they want to play again or quit
void Game::displayGameOver(int score, int winner)
{
	// noecho();
	// attron(COLOR_PAIR(6));
	// mvprintw(2, 9, "  _____          __  __ ______    ______      ________ _____");
	// mvprintw(3, 9, " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\");
	// mvprintw(4, 9, "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
	// mvprintw(5, 9, "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /");
	// mvprintw(6, 9, "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\");
	// mvprintw(7, 9, " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
	// attroff(COLOR_PAIR(6));
	// refresh();
	switch (winner)
	{
	case -1:
		// attron(COLOR_PAIR(1) | A_BOLD);
		// mvprintw(10, 38, "DEFEAT");
		// attroff(COLOR_PAIR(1) | A_BOLD);
		break;
	case 0:
		// attron(COLOR_PAIR(4) | A_BOLD);
		// mvprintw(10, 37, "DRAW");
		// attroff(COLOR_PAIR(4));
		break;
	case 1:
		// attron(COLOR_PAIR(2) | A_BOLD);
		// mvprintw(10, 37, "VICTORY");
		// attroff(COLOR_PAIR(2) | A_BOLD);

		break;
	}
	// attron(COLOR_PAIR(3));
	// mvprintw(11, 36, "SCORE: %d", score);
	// attroff(COLOR_PAIR(3));
	// refresh();

	sf::Text text("GAMEOVER", font, 48);
	sf::Text result("", font, 48);
	std::string scores = "SCORE: " + std::to_string(score);
	sf::Text prtscore(scores, font, 48);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	text.setPosition(250, 10);
	result.setStyle(sf::Text::Bold);
	result.setFillColor(sf::Color::Blue);
	result.setPosition(250, 500);
	prtscore.setStyle(sf::Text::Bold);
	prtscore.setFillColor(sf::Color::Black);
	prtscore.setPosition(250, 700);
	switch (winner) {
	case -1:
		result.setString("Result: DEFEAT");
		break;
	case 0:
		result.setString("Result: DRAW");
		break;
	case 1:
		result.setString("Result: VICTORY");
	default:
		break;
	}

	static std::vector<sf::Text> choices;
	sf::Text playAgain("Play Again", font);
	sf::Text quit("Quit", font);
	choices.push_back(playAgain);
	choices.push_back(quit);
	std::string choice = "";
	auto highlight = choices.begin();
	choices[0].setPosition(200, 150);
	choices[1].setPosition(200, 250);
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
					if (++highlight == choices.end())
						highlight = choices.begin();
					break;
				case sf::Keyboard::Up:
					if (highlight == choices.begin())
						highlight = std::prev(choices.end());
					else
						--highlight;
					break;
				case sf::Keyboard::Enter:
					choice = highlight->getString();
					break;
				default:
					break;
				}
			}
			break;
			case sf::Event::Closed:
			{
				win.close();
			}
			break;
			default:
				break;
			}
		}
		win.clear(sf::Color::White);
		win.draw(text);
		win.draw(result);
		win.draw(prtscore);
		endingMenu(choices, highlight);
		win.display();
		if (choice == "Play Again") { gameFinished = false; break; }
		else if (choice == "Quit") { gameFinished = true; break; }
	}
}


void Game::sortAndWriteHighScores(int score)
{
	highscores.push_back(make_pair(initials, score));
	std::stable_sort(highscores.begin(), highscores.end(), pairCompare);
	if (highscores.size() > 5) { highscores.pop_back(); }
	std::ofstream myfile("scores.txt");
	if (myfile.is_open())
	{
		for (unsigned i = 0; i < highscores.size(); ++i)
		{
			myfile << highscores[i].first.c_str() << " " << highscores[i].second << std::endl;
		}
		myfile.close();
	}
	else
	{
		std::cout << "scores.txt does not exist. Check your directory." << std::endl;
		abort();
	}
	highscores.clear();
}


//Display the instructions
void Game::displayInstr()
{
	// attron(COLOR_PAIR(5) | A_BOLD);
	// mvprintw(1, 34, "INSTRUCTIONS");
	// attroff(COLOR_PAIR(5) | A_BOLD);
	// mvprintw(3, 10, "The goal of the game is to get the pancake stack into order");
	// mvprintw(4, 10, "(from smallest on top to largest on bottom) by repeatedly");
	// mvprintw(5, 10, "flipping over a top-partial stack of some number of pancakes.");
	// mvprintw(6, 10, "Try to flip the stack into order before the opponent!");

	// mvprintw(8, 26, "Press any key to continue...");

	sf::Texture splash;
	sf::Sprite splashimg;
	bool isEnter = false;
	if (!splash.loadFromFile("instruction.png"))
		std::printf("Could not load splash file \n");

	splashimg.setTexture(splash);

	// sf::Text anyKey("Press any key to continue...", font);
	// anyKey.setFillColor(sf::Color::Red);

	//Continue when user presses key
	bool keyPressed = false;
	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				win.close();
				break;
				// key pressed
			case sf::Event::KeyPressed:
				keyPressed = true;
				break;
				// we don't process other types of events
			default:
				break;
			}
		}
		win.clear(sf::Color::White);
		win.draw(splashimg);
		win.display();
		if (keyPressed) { break; }
	}
}


//Check validity of config input
bool Game::checkConfigs(int n, int diff, std::string nString, std::string diffString)
{
	bool check = true;

	if (n < 2 || n > 9) { check = false; }

	if (diff < 2 || diff > 9) { check = false; }

	std::string::const_iterator it1 = nString.begin();
	while (it1 != nString.end() && isdigit(*it1)) { ++it1; }
	if (it1 != nString.end()) {
		check = false;
	}

	std::string::const_iterator it2 = diffString.begin();
	while (it2 != diffString.end() && isdigit(*it2)) { ++it2; }
	if (it2 != diffString.end()) {
		check = false;
	}
	return check;
}


// Prompt for user-specified sequence or random sequence
std::string Game::requestSeq(int n)
{
	std::string seqPrompt1 = "Enter a pancake sequence(e.g. 12345)";
	std::string seqPrompt2 = "or \"r\" for a random sequence: ";
	std::string seqPancakes;

	sf::Text text1;
	text1.setString(seqPrompt1);
	text1.setFont(font);
	text1.setFillColor(sf::Color::Red);
	text1.setPosition(150, 300);

	sf::Text text2;
	text2.setFont(font);
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(150, 340);

	bool inputValid = false;
	while (!inputValid)
	{
		std::string input;
		bool enterPressed = false;
		while (win.isOpen())
		{
			sf::Event event;
			while (win.pollEvent(event))
			{
				// check the type of the event...
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
					win.close();
					break;

					// key pressed
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Backspace && !input.empty()) { input.pop_back(); }
					else if (event.key.code == sf::Keyboard::Enter) { enterPressed = true; }
					break;

					// text entered
				case sf::Event::TextEntered:
					if (event.text.unicode == 8) { continue; }
					//if (event.text.unicode == 8 && !inputNum.empty() && enterPresses == 0) { inputNum.pop_back(); }
					else if (event.text.unicode < 128 && event.text.unicode != 10) { input += static_cast<char>(event.text.unicode); }
					//else if (event.text.unicode == 8 && !inputDiff.empty() && enterPresses == 1) { inputDiff.pop_back(); }
					break;

					// we don't process other types of events
				default:
					break;
				}
			}
			win.clear(sf::Color::White);
			text2.setString(seqPrompt2 + input);
			win.draw(text1);
			win.draw(text2);
			win.display();
			if (enterPressed) { break; }
		}
		seqPancakes = input;
		inputValid = checkSeq(seqPancakes, n);
	}
	return seqPancakes;
}


//Check validity of sequence input
bool Game::checkSeq(std::string seq, int n)
{
	bool check = true;

	// int offsety = 0;
	// int row,col;
	// getmaxyx(stdscr, row, col);

	if ((seq == "r") | (seq == "R")) { return true; }

	if (seq.length() != n) {
		char msg1[] = "Sequence length must match number of pancakes";
		// mvprintw(row / 2 + offsety, (col - strlen(msg1)) / 2, msg1);
		// offsety +=2;
		check = false;
	}

	std::string::const_iterator it = seq.begin();
	while (it != seq.end() && (((int)*it - '0') >= 1) && (((int)*it - '0') <= n)) { ++it; }
	if (it != seq.end()) {
		char msg2[] = "Sequence must only contain numbers from 1 to n(number of pancakes)";
		// mvprintw(row / 2 + offsety, (col - strlen(msg2)) / 2, msg2);
		// offsety +=2;
		check = false;
	}

	std::string seqCopy(seq);
	std::sort(seqCopy.begin(), seqCopy.end());
	for (int i = 0; i < seqCopy.length() - 1; ++i) {
		if (seqCopy[i] == seqCopy[i + 1]) {
			char msg3[] = "Sequence must not contain repeated numbers";
			// mvprintw(row / 2 + offsety, (col - strlen(msg3)) / 2, msg3);
			// offsety +=2;
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
		// std::shuffle (sequence.begin(), sequence.end(), std::default_random_engine(seed));
		auto gen = std::default_random_engine(seed);
		std::shuffle(sequence.begin(), sequence.end(), gen);
		std::next_permutation(sequence.begin(), sequence.end());
	}
	else {
		//Convert string sequence into number vector
		int currNum;
		for (size_t i = 0; i < seq.length(); i++) {
			std::string currElem(1, seq.at(i));
			currNum = std::stoi(currElem);
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
	while (it != initials.end() && isalpha(*it)) { ++it; }
	if (it != initials.end()) {
		check = false;
	}
	return check;
}


//Give player the choice to play again or quit
void Game::endingSelection() {}


//Print the ending menu
void Game::endingMenu(std::vector<sf::Text>& choices, std::vector<sf::Text>::iterator highlight)
{
	for (auto choice = choices.begin(); choice != choices.end(); ++choice)
	{
		if (highlight == choice)
		{
			choice->setFillColor(sf::Color::Red);
			choice->setStyle(sf::Text::Bold);
			win.draw(*choice);
		}
		else
		{
			choice->setFillColor(sf::Color::Black);
			choice->setStyle(sf::Text::Regular);
			win.draw(*choice);
		}
	}
}


//Comparison function for comparing highscores
bool pairCompare(const std::pair<std::string, int>& first, const std::pair<std::string, int>& second)
{
	return first.second > second.second;
}
