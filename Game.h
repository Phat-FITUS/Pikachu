#pragma once

#include "Console.h"
#include "Board.h"
#include "Object.h"
#include <string>

using namespace std;

class Game
{
private:
	Console screen;
	Object draw;
	string username;
	int rainbow[7];

	void selectDifficultPage();
	void printImageFromFile(int, int, string, bool);
public:
	Game();
	void start();
};

