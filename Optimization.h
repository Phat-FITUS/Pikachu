#pragma once
#include "Coordinate.h"
#include <queue>
#include <string>
using namespace std;

struct randomPair {
	int value;
	int randomOrder;

	void operator = (randomPair other) {
		this->value       = other.value;
		this->randomOrder = other.randomOrder;
	}

	randomPair() {
		this->value       = 0;
		this->randomOrder = 0;
	}
};

class Optimization
{
private:
	static void RemoveLeadingAndTrailingSpaces(string&);
	static void FormatString(string&);
	static void RemoveExtraSpaces(string&);
	static int getNumberOfTurn(Coordinate**, Coordinate);
	static void spreadRoute(char**, int, int, Coordinate, Coordinate, Coordinate**, queue<Coordinate>, bool**, int&);
	static void moveTo(char**, Coordinate, Coordinate, Coordinate, Coordinate**, queue<Coordinate>&, bool**, int&);
	static queue<Coordinate> makePath(Coordinate**, Coordinate);
public:
	static void TrimString(string&);
	static void initBoardGame(char**, int, int);
	static void shuffleBoardGame(char**, int, int);
	static void slideDownBoardCell(char**, int, int);
	template<typename T>
	static void swap(T&, T&);
	static bool canConnect(char**, int, int, Coordinate, Coordinate);
	static queue<Coordinate> getPath(char**, int, int, Coordinate, Coordinate);
};
