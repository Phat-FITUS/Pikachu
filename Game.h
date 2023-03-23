#pragma once

#include "Console.h"
#include "Board.h"
#include "Object.h"

class Game
{
private:
	Console screen;
	Object draw;
public:
	void start();
};

