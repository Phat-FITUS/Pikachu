#pragma once
#include "Console.h"

class Draw
{
private:
	Console screen;
public:
	void HorizontalLine(int, int, int, char);
	void VerticalLine(int, int, int, char);
	void Cell(int, int, int, int, char);
};

