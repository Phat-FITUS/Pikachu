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

void Game::selectDifficultPage() {
	cout << "ditme BHT" << endl;
	return;
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
			else {
				this->screen.Clear();
				selectDifficultPage();
				system("pause");
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
			if (username.length() < 16 && selection == 0) username.push_back(key_press);
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