#pragma once
#include "Console.h"
#include <string>
#include "Coordinate.h"
#include <queue>
using namespace std;

class Object
{
private:
	Console screen;
public:
	void HorizontalLine(int, int, int, char);
	void VerticalLine(int, int, int, char);
	void Cell(int, int, int, int, char, bool, bool, bool);
	void Button(int, int, int, int, string, bool);
	void TextEntry(int, int, int, int, string, string, string, bool);
	void LineBetweenCells(Coordinate, Coordinate, queue<Coordinate>);
	void MakePathLine(Coordinate, Coordinate);
};

