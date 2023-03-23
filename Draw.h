#pragma once
#include "Console.h"
#include <string>

using namespace std;

class Draw
{
private:
	Console screen;
public:
	void HorizontalLine(int, int, int, char);
	void VerticalLine(int, int, int, char);
	void Cell(int, int, int, int, char);
	void Button(int, int, int, int, string);
	void TextEntry(int, int, int, int, string, string, string, bool);
};

