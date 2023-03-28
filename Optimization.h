#pragma once
#include "Coordinate.h"
#include <queue>
using namespace std;

struct randomPair {
	int value;
	int randomOrder;

	void operator = (randomPair other) {
		this->value       = other.value;
		this->randomOrder = other.randomOrder;
	}
};

class Optimization
{
private:
	static int getNumberOfTurn(Coordinate**, Coordinate);
	static void spreadRoute(char**, int, int, Coordinate, Coordinate, Coordinate**, queue<Coordinate>, bool**, int&);
	static void moveTo(char**, Coordinate, Coordinate, Coordinate, Coordinate**, queue<Coordinate>&, bool**, int&);
	static queue<Coordinate> makePath(Coordinate**, Coordinate);
public:
	static void initBoardGame(char**, int, int);
	template<typename T>
	static void sort(T*, int, bool(*cmp)(T a, T b));
	template<typename T>
	static void swap(T&, T&);
	static bool canConnect(char**, int, int, Coordinate, Coordinate);
	static queue<Coordinate> getPath(char**, int, int, Coordinate, Coordinate);
};
