#include "Game.h"
#include <fstream>
#include <conio.h>
#include <chrono>

void Game::mainMenu() {
	
	bool playing = true;
	int selection = 0;

	while (playing) {

		this->screen.Clear();

		draw.Button(48, 8, 20, 5, "Play", selection == 0);
		draw.Button(48, 13, 20, 5, "Custom Play", selection == 1);
		draw.Button(48, 18, 20, 5, "Leaderboard", selection == 2);
		draw.Button(48, 23, 20, 5, "Exit", selection == 3);

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

		draw.Button(48, 8, 20, 5, "Easy (2x2)", selection == 0);
		draw.Button(48, 13, 20, 5, "Medium (4x4)", selection == 1);
		draw.Button(48, 18, 20, 5, "Hard (6x6)", selection == 2);
		draw.Button(48, 23, 20, 5, "Exit", selection == 3);

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

		draw.TextEntry(34, 8, 19, 4, "Width", width_Board, "Your width...", selection == 0);
		draw.TextEntry(54, 8, 19, 4, "Height",height_Board, "Your height...", selection == 1);
		draw.Button(34, 13, 19, 5, "Enter", selection == 2);
		draw.Button(54, 13, 19, 5, "Exit", selection == 3);

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
						this->playingPage();
						playing = false;
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
	Coordinate* hint = new Coordinate[2];

	this->board.addPokemon();
	this->screen.Clear();

	//Start time
	auto start = std::chrono::steady_clock::now();

	while (playing) {
		this->board.display(10, 6, selection, choices, hint);

		char key_press = _getch();

		char** board_data = this->board.getData();

		switch (key_press)
		{
		case ESC: {
			playing = false;
			break;
		}
		case 'h': {
			//Delete old hint
			delete[] hint;

			//Create new one
			hint = this->board.help();
			break;
		}
		case ENTER: {
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

				if (Optimization::canConnect(board_data, this->board.getWidth(), this->board.getHeight(), choices[0], choices[1]) 
					&& board_data[choices[0].x][choices[0].y] == board_data[choices[1].x][choices[1].y] && board_data[choices[0].x][choices[0].y] != 0) {
					queue<Coordinate> path = Optimization::getPath(board_data, this->board.getWidth(), this->board.getHeight(), choices[0], choices[1]);

					draw.LineBetweenCells(choices[0], choices[1], path);

					//Make matched cell empty
					board_data[choices[0].x][choices[0].y] = 0;
					board_data[choices[1].x][choices[1].y] = 0;

					//Delete old hint
					try {
						delete[] hint;
					}
					catch(exception e) {
						//Co loi thi keme no di :)) xoa cho chac an thoi
					}

					//Create new one
					hint = new Coordinate[2];
				}

				Sleep(500);

				if (this->isEndGame()) {
					//Finish time
					auto end = std::chrono::steady_clock::now();
					auto duration_sec = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

					// Calculate the minutes and seconds
					int minutes = duration_sec / 60;
					int seconds = duration_sec % 60;

					//Move to ending page
					this->endGamePage(minutes, seconds);

					return;
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

	//Delete temporary hint
	try {
		delete[] hint;
	}
	catch (exception e) {
		//Co loi thi keme no di :)) xoa cho chac an thoi
	}
}

void Game::leaderBoardPage() {
	this->screen.Clear();

	bool playing = true;
	int selection = 0;
	this->leader_board.sort();

	while (playing) {
		int mode_line[3] = { 12, 12, 12 };

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

		for (int i = 0; i < this->leader_board.getSize(); i++) {
			User current = this->leader_board.at(i);

			if (current.mode == 0) continue; //ignore custom mode

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

	while (playing) {

		this->screen.Clear();

		this->screen.GoTo(31, 8);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.LightGreen);
		cout << "Congratulation user " << this->username << " on finishing the game!";

		this->screen.GoTo(10, 11);
		cout << "You have finished the game in " << minute << " minutes and " << second << " seconds. Do you want to save your score?";

		draw.Button(34, 13, 19, 5, "Save", selection == 0);
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
				//When user agree to save his score, push it to leader board
				this->leader_board.push_back(User(username.c_str(), minute, second, this->current_mode));
			}
			this->exitPage();
			playing = false;
			break;
		}
		default:
			break;
		}
	}
}

void Game::exitPage() {
	bool playing = true;
	int selection = 0;

	while (playing) {

		this->screen.Clear();

		this->screen.GoTo(38, 8);
		this->screen.SetColor(this->screen.color.Black, this->screen.color.LightGreen);
		cout << "Do you want to play more?";

		draw.Button(36, 13, 19, 5, "Yesss", selection == 0);
		draw.Button(54, 13, 19, 5, "No, exit", selection == 1);

		char key_press = _getch();

		switch (key_press)
		{
		case TAB: {
			selection = (selection + 1) % 2;
			break;
		}
		case ENTER: {
			if (selection == 0) {
				this->mainMenu();
			}
			if (selection == 1) {
				//exit(0);
			}
			playing = false;
			break;
		}
		default:
			break;
		}
	}
}

void Game::start() {
	bool playing = true;
	int selection = 0;

	while (playing) {
		
		this->screen.Clear();

		printImageFromFile(32, 1, "logo.bin", this->screen.color.BrightWhite);
		draw.TextEntry(40, 8, 38, 4, "username", this->username, "Your username...", selection == 0);
		draw.Button(40, 13, 18, 5, "Enter", selection == 1);
		draw.Button(60, 13, 18, 5, "Exit", selection == 2);

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
			else if (!this->username.empty()){ //Only accept unempty username
				this->mainMenu();
			}
			break;
		}
		case BACKSPACE:
		case DELETE_KEY:
		case 83: case -32: { //delete key of some laptop board
			if (username.length() && selection == 0) username.pop_back();
			break;
		}
		default:
			if (username.length() < 32 && selection == 0) username.push_back(key_press);
			break;
		}
	}
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