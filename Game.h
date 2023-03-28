#pragma once

#include "Console.h"
#include "Board.h"
#include "Object.h"
#include "User.h"
#include "Optimization.h"
#include <string>

using namespace std;

class Game
{
private:
	Console screen;
	Object draw;
	string username;
	Board board;

	void mainMenu();
	void selectDifficultPage();
	void customDifficultPage();
	void playingPage();
	void leaderBoard();
	bool isEndGame();
	void printImageFromFile(int, int, string, int);
public:
	void start();
};

