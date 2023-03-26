#include "Game.h"
#include <fstream>
#include<conio.h>

Game::Game() {
	this->rainbow[0] = this->screen.color.LightRed;
	this->rainbow[1] = this->screen.color.LightAqua;
	this->rainbow[2] = this->screen.color.LightGreen;
	this->rainbow[3] = this->screen.color.LightPurple;
	this->rainbow[4] = this->screen.color.BrightWhite;
	this->rainbow[5] = this->screen.color.LightYellow;
	this->rainbow[6] = this->screen.color.Blue;
}

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
					this->leaderBoard();
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
		draw.Button(48, 18, 20, 5, "Hard (8x8)", selection == 2);
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
					
				}
				if (selection == 1) {
					
				}
				if (selection == 2) {
					
				}
				if (selection == 3) {
					playing = false;
				}
				break;
			default:
				selection = 0;
				break;
			}
		}
	}
}


void Game::customDifficultPage() {// Check cai nay lai van chua _getch() duoc width va height
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
					if (stoi(width_Board, 0, 10) > 0 && stoi(height_Board, 0, 10) > 0) {
						cout << "ditme BHT";
					}
				}
			}
			default:
				break;
		}
	}
}


void Game::leaderBoard() {

	this->screen.Clear();

	cout << "ditme BHT";
}

void Game::start() {
	bool playing = true;
	int selection = 0;

	while (playing) {
		
		this->screen.Clear();

		printImageFromFile(28, 0, "logo.bin", true);
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

void Game::printImageFromFile(int x, int y, string filename, bool colorful) {
	fstream f;
	f.open(filename.c_str(), ios::binary | ios::in);

	if (!f.is_open()) {
		cout << "File " << filename << " not found!\n";
		return;
	}

	char temp[100] = {};
	f.read((char*)&temp, 4);
	int line = atoi(temp);

	f.read((char*)&temp, 4);
	int amount = atoi(temp);

	for (int currentLine = 0; currentLine < line; currentLine++) {
		f.read((char*)&temp, amount);

		this->screen.GoTo(x, y + currentLine);
		if (colorful) {
			this->screen.SetColor(this->screen.color.Black, this->rainbow[currentLine % 7]);
		}
		else {
			this->screen.SetColor(this->screen.color.Black, this->screen.color.BrightWhite);
		}

		cout << temp;
	}
	f.close();
}