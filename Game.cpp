#include "Game.h"
#include <fstream>
#include <conio.h>
#include <chrono>

void Game::loginPage() {
	bool playing = true;
	int selection = 0;

	while (playing) {

		this->screen.Clear();

		printImageFromFile(23, 1, "logo.bin", this->screen.color.LightYellow);
		draw.TextEntry(40, 14, 38, 4, "username", this->username, "Your username...", selection == 0);
		draw.Button(40, 19, 18, 5, "Enter", selection == 1);
		draw.Button(60, 19, 18, 5, "Exit", selection == 2);
		this->printImageFromFile(5, 12, "tv.bin", this->screen.color.Green);

		char key_press = _getch();

		switch (key_press)
		{
		case TAB: {
			selection = (selection + 1) % 3;
			break;
		}
		case ENTER: {
			if (selection == 2) {
				playing = false;
			}
			else if (!this->username.empty()) { //Only accept unempty username
				this->mainMenu();
				playing = false;
			}
			break;
		}
		case BACKSPACE:
		case DELETE_KEY:
		case 83: case -32: { //delete key of some laptop board
			if (username.length() && selection == 0) username.pop_back();
			else cout << '\a'; //Error sound of windows when can not delete anymore
			break;
		}
		default:
			if (username.length() < 32 && selection == 0 &&
				((key_press >= 'a' && key_press <= 'z')
					|| (key_press >= 'A' && key_press <= 'Z')
					|| key_press == 32)
				) username.push_back(key_press);
			else cout << '\a'; //Error sound of windows when can not accept the key press

			break;
		}
	}
}

void Game::mainMenu() {
	
	bool playing = true;
	int selection = 0;

	while (playing) {

		this->screen.Clear();

		this->printImageFromFile(40, 0, "menu.bin", this->screen.color.LightYellow);
		draw.Button(17, 9, 20, 5, "Play", selection == 0);
		draw.Button(38, 9, 20, 5, "Custom Play", selection == 1);
		draw.Button(59, 9, 20, 5, "Leaderboard", selection == 2);
		draw.Button(80, 9, 20, 5, "Exit", selection == 3);
		this->printImageFromFile(48, 15, "tv2.bin", this->screen.color.Green);

		char key_press = _getch();

		switch (key_press)
		{
			case TAB: {
				selection = (selection + 1) % 4;
				break;
			}
			case ENTER: {
				if (selection == 0) {
					this->selectDifficultPage();
				}
				if (selection == 1) {
					this->customDifficultPage();
				}
				if (selection == 2) {
					this->leaderBoardPage();
				}
				if (selection == 3) {
					playing = false;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Game::selectDifficultPage() {
	bool playing = true;
	int selection = 0;

	while (playing) {

		this->screen.Clear();

		this->printImageFromFile(2, 0, "choose_mode.bin", this->screen.color.LightYellow);
		draw.Button(17, 9, 20, 5, "Easy (2x2)", selection == 0);
		draw.Button(38, 9, 20, 5, "Medium (4x4)", selection == 1);
		draw.Button(59, 9, 20, 5, "Hard (6x6)", selection == 2);
		draw.Button(80, 9, 20, 5, "Exit", selection == 3);
		this->printImageFromFile(48, 15, "tv2.bin", this->screen.color.Green);

		char key_press = _getch();

		switch (key_press)
		{
			case TAB: {
				selection = (selection + 1) % 4;
				break;
			}
			case ENTER: {
				if (selection == 0) {
					this->board.changeSize(2, 2);
					this->current_mode = 1;
					this->playingPage();
				}
				if (selection == 1) {
					this->board.changeSize(4, 4);
					this->current_mode = 2;
					this->playingPage();
				}
				if (selection == 2) {
					this->board.changeSize(6, 6);
					this->current_mode = 3;
					this->playingPage();
				}
				playing = false;
			}
				break;
			default:
				break;
		}
	}
}

void Game::customDifficultPage() {
	bool playing = true;
	int selection = 0;
	string width_Board;
	string height_Board;


	while (playing) {

		this->screen.Clear();

		this->printImageFromFile(2, 0, "custom_mode.bin", this->screen.color.LightYellow);
		draw.TextEntry(40, 10, 19, 4, "Width", width_Board, "Your width...", selection == 0);
		draw.TextEntry(60, 10, 19, 4, "Height",height_Board, "Your height...", selection == 1);
		draw.Button(40, 15, 19, 5, "Enter", selection == 2);
		draw.Button(60, 15, 19, 5, "Exit", selection == 3);
		this->printImageFromFile(90, 10, "tv2.bin", this->screen.color.Green);
		this->printImageFromFile(10, 10, "tv3.bin", this->screen.color.Green);

		char key_press = _getch();

		switch (key_press)
		{
			case TAB: {
				selection = (selection + 1) % 4;
				break;
			}
			case ENTER: {
				if (selection == 3) {
					playing = false;
				}
				else {
					if (!width_Board.empty() && !height_Board.empty() && board.changeSize(stoi(width_Board), stoi(height_Board))) {
						this->current_mode = 0;
						this->playingPage();
						playing = false;
					}
					else {
						//Error sound of windows
						cout << '\a';
					}
				}
				break;
			}
			case BACKSPACE:
			case DELETE_KEY:
			case 83: case -32: { //delete key of some laptop board
				if (width_Board.length() > 0 && selection == 0) width_Board.pop_back();
				if (height_Board.length() > 0 && selection == 1) height_Board.pop_back();
				break;
			}
			default:
				if (key_press >= '0' && key_press <= '9')
				if (selection == 0) width_Board.push_back(key_press);
				if (selection == 1) height_Board.push_back(key_press);
				break;
		}
	}
}

void Game::playingPage() {
	bool playing = true;
	Coordinate selection(1, 1);
	Coordinate choices[2];
	CoupleCoordinate hint{ Coordinate(-1, -1), Coordinate(-1, -1) };

	this->board.addPokemon();
	this->screen.Clear();

	//Start time
	auto start = std::chrono::steady_clock::now();

	while (playing) {
		this->board.display(10, 6, selection, choices, hint);
		this->printImageFromFile(85, 5, "tv5.bin", this->screen.color.Green);

		char key_press = _getch();

		switch (key_press)
		{
		case ESC: {
			playing = false;
			break;
		}
		case 'h': {
			//Create new one
			hint = this->board.help();
			break;
		}
		case ENTER: {
			char** board_data = this->board.getData();

			if (board_data[selection.x][selection.y] == 0) break;

			if (choices[0] == Coordinate()) {
				choices[0] = selection;
			}
			else if (choices[1] == Coordinate()) {
				//Unselect the selection
				if (choices[0] == selection) {
					this->screen.Clear();
					choices[0] = Coordinate();
					break;
				}
				choices[1] = selection;
				this->board.display(10, 6, selection, choices, hint);

				char** board_data = this->board.getData();

				if ((Optimization::canConnect(board_data, this->board.getWidth(), this->board.getHeight(), choices[0], choices[1]) 
					|| Optimization::canConnect(board_data, this->board.getWidth(), this->board.getHeight(), choices[1], choices[0]))
					&& board_data[choices[0].x][choices[0].y] == board_data[choices[1].x][choices[1].y] && board_data[choices[0].x][choices[0].y] != 0) {
					queue<Coordinate> path = Optimization::getPath(board_data, this->board.getWidth(), this->board.getHeight(), choices[0], choices[1]);
					if (path.size() == 0) {
						path = Optimization::getPath(board_data, this->board.getWidth(), this->board.getHeight(), choices[1], choices[0]);
					}

					//Purple arrow
					this->screen.SetColor(this->screen.color.Black, this->screen.color.LightPurple);
					draw.LineBetweenCells(choices[0], choices[1], path);

					//Make matched cells empty
					board_data[choices[0].x][choices[0].y] = 0;
					board_data[choices[1].x][choices[1].y] = 0;

					//Remove hint
					hint.first_choice = Coordinate(-1, -1);
					hint.second_choice = Coordinate(-1, -1);
				}
				else {
					//Error sound of windows
					cout << '\a';
				}

				Sleep(500);

				if (this->isEndGame()) {
					//Finish time
					auto end = std::chrono::steady_clock::now();
					auto duration_sec = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

					// Calculate the minutes and seconds
					int minutes = duration_sec / 60;
					int seconds = duration_sec % 60;

					//Let user see the board last time :((
					this->screen.Clear();
					choices[0] = Coordinate();
					choices[1] = Coordinate();
					this->board.display(10, 6, selection, choices, hint);
					Sleep(500);

					//Custom mode will not save anything
					if (this->current_mode) {
						//Move to ending page
						this->endGamePage(minutes, seconds);
					}

					return;
				}

				//Slide the empty cell(s) up in hard mode
				if (this->current_mode == 3) {
					Optimization::slideDownBoardCell(board_data, this->board.getWidth(), this->board.getHeight());
				}

				//Shuffle the board until there is a path connecting any cell
				while (!this->board.canPlay()) {
					Optimization::shuffleBoardGame(board_data, this->board.getWidth(), this->board.getHeight());
				}

				choices[0] = Coordinate();
				choices[1] = Coordinate();
				this->screen.Clear();
			}
			break;
		}
		case RIGHTARROW:
		case 'd': {
			selection = Coordinate(selection.x == this->board.getWidth() ? 1 : selection.x + 1, selection.y);
			break;
		}
		case LEFTARROW:
		case 'a': {
			selection = Coordinate(selection.x > 1 ? selection.x - 1 : this->board.getWidth(), selection.y);
			break;
		}
		case UPARROW:
		case 'w': {
			selection = Coordinate(selection.x, selection.y > 1 ? selection.y - 1 : this->board.getHeight());
			break;
		}
		case DOWNARROW:
		case 's': {
			selection = Coordinate(selection.x, selection.y == this->board.getHeight() ? 1 : selection.y + 1);
			break;
		}
		default:
			break;
		}
	}
}

void Game::leaderBoardPage() {
	this->screen.Clear();

	bool playing = true;
	int selection = 0;
	this->leader_board.sort();

	while (playing) {
		int mode_line[3] = { 12, 12, 12 };

		this->printImageFromFile(90, 18, "tv4.bin", this->screen.color.Green);

		this->printImageFromFile(30, 0, "leader_art.bin", this->screen.color.LightYellow);

		this->screen.SetColor(this->screen.color.Black, this->screen.color.Green);
		this->screen.GoTo(14, 8);
		cout << "Easy Mode";

		this->screen.GoTo(2, 10);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.BrightWhite);
		printf_s("NO. %-16s %s", "Username", "Finish Time");
		this->draw.HorizontalLine(2, 11, 35, '-');

		this->screen.SetColor(this->screen.color.Black, this->screen.color.Yellow);
		this->screen.GoTo(53, 8);
		cout << "Medium Mode";

		this->screen.GoTo(42, 10);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.BrightWhite);
		printf_s("NO. %-16s %s", "Username", "Finish Time");
		this->draw.HorizontalLine(42, 11, 35, '-');

		this->screen.SetColor(this->screen.color.Black, this->screen.color.Red);
		this->screen.GoTo(94, 8);
		cout << "Hard Mode";

		this->screen.GoTo(82, 10);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.BrightWhite);
		printf_s("NO. %-16s %s", "Username", "Finish Time");
		this->draw.HorizontalLine(82, 11, 35, '-');

		for (int i = 0; i < this->leader_board.getSize(); i++) { //Just show top 5
			User current = this->leader_board.at(i);

			if (current.mode == 0) continue; //ignore custom mode

			if (mode_line[current.mode - 1] - 12 > 5) continue; //ignore over top 5

			this->screen.GoTo((current.mode - 1) * 40 + 2, mode_line[current.mode - 1]++);
			printf_s("%-2d. %-16s %d:%d", mode_line[current.mode - 1] - 12, current.username, current.minute, current.second);
		}

		char key_press = _getch();

		switch (key_press)
		{
		case ESC: {
			playing = false;
			break;
		}
		default:
			break;
		}
	}
}

bool Game::isEndGame() {
	bool endGame = true;

	for (int i = 1; i <= this->board.getWidth() && endGame; i++) {
		for (int j = 1; j <= this->board.getHeight() && endGame; j++) {
			if (this->board.getData()[i][j] != 0) {
				endGame = false;
			}
		}
	}

	return endGame;
}

void Game::endGamePage(int minute, int second) {
	bool playing = true;
	int selection = 0;

	//Check existing user
	User user_result(username.c_str(), minute, second, this->current_mode);
	int user_index = this->leader_board.find(user_result);

	//Push new result to leader board if user is new, otherwise edit user's result when the new one is higher then save to file
	if (user_index == -1) {
		this->leader_board.push_back(user_result);
	}
	else {
		User user_old_result = this->leader_board.at(user_index);
		int old_score = user_old_result.minute * 60 + user_old_result.second;
		int new_score = user_result.minute * 60 + user_result.second;

		if (old_score > new_score) {
			this->leader_board.editAt(user_index, user_result);
		}
	}
	this->leader_board.save();

	while (playing) {

		this->screen.Clear();

		this->printImageFromFile(80, 13, "tv2.bin", this->screen.color.Green);

		this->screen.GoTo(31, 8);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.LightGreen);
		cout << "Congratulation user " << this->username << " on finishing the game!";

		this->screen.GoTo(44, 11);
		cout << "Do you want to continue?";

		draw.Button(34, 13, 19, 5, "Let's go", selection == 0);
		draw.Button(54, 13, 19, 5, "No tks!", selection == 1);

		char key_press = _getch();

		switch (key_press)
		{
		case TAB: {
			selection = (selection + 1) % 2;
			break;
		}
		case ENTER: {
			if (selection == 0) {
				this->current_mode = this->current_mode % 3 + 1;
				this->board.changeSize(this->current_mode * 2, this->current_mode * 2);
				this->playingPage();
			}
			playing = false;
			break;
		}
		default:
			break;
		}
	}
}

void Game::thankyouPage() {
	this->screen.Clear();

	this->printImageFromFile(5, 0, "thanks.bin", this->screen.color.LightYellow);
	this->printImageFromFile(30, 10, "thanks2.bin", this->screen.color.LightYellow);

	this->screen.GoTo(44, 21);
	cout << "Press any key to exit";

	char key_press = _getch();
}

void Game::start() {
	this->loginPage();
	this->thankyouPage();

	//Set the default color to console before exit
	this->screen.SetColor(this->screen.color.Black, this->screen.color.BrightWhite);
}

void Game::printImageFromFile(int x, int y, string filename, int colorCode) {
	fstream f;
	f.open(filename.c_str(), ios::binary | ios::in);

	if (!f.is_open()) {
		cout << "File " << filename << " not found!\n";
		return;
	}
	string line;
	int currentLine = 0;
	while (getline(f, line)) {
		this->screen.GoTo(x, y + currentLine);
		this->screen.SetColor(this->screen.color.Black, colorCode);

		cout << line;
		currentLine++;
	}
	f.close();
}