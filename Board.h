#pragma once
#include "Object.h"

class Board
{
private:
	int height, width;
	char** data;
	Object draw;
	const int CELL_WIDTH = 9;
	const int CELL_HEIGHT = 5;
	static const int MAX_SIZE = 8;
	bool selection = true;

	void allocate(); 
	void deallocate();
	static bool checkValidSize(int width, int height);
public:
	Board();
	Board(int, int);
	~Board();
	void display(int, int);
	void fill(char);
	bool changeSize(int, int);
};

