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
	LeaderBoard leader_board;
	int current_mode = 0; //1: easy, 2: medium, 3: hard

	void mainMenu();
	void selectDifficultPage();
	void customDifficultPage();
	void playingPage();
	void leaderBoardPage();
	bool isEndGame();
	void endGamePage(int, int);
	void exitPage();
	void printImageFromFile(int, int, string, int);
public:
	void start();
};

