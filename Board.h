#pragma once
#include "Object.h"
#include "Coordinate.h"

class Board
{
private:
	int height, width;
	char** data;
	Object draw;
	const int CELL_WIDTH = 9;
	const int CELL_HEIGHT = 5;
	static const int MAX_SIZE = 6;

	void allocate(); 
	void deallocate();
	bool checkValidSize(int width, int height);
public:
	Board();
	Board(int, int);
	~Board();
	void display(int, int, Coordinate, Coordinate[2], CoupleCoordinate);
	void fill(char);
	void addPokemon();
	bool changeSize(int, int);
	bool canPlay();
	CoupleCoordinate help();
	int getWidth();
	int getHeight();
	char** getData();
};

