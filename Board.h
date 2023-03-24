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
	bool selection = true;

	void allocate(); 
	void deallocate();
public:
	Board();
	Board(int, int);
	~Board();
	void display(int, int);
	void fill(char);
	void changeSize(int, int);
};

