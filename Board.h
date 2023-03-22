#pragma once
#include "Draw.h"

class Board
{
private:
	int height, width;
	char** data;
	Draw draw;
	const int CELL_WIDTH = 9;
	const int CELL_HEIGHT = 5;
	
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

