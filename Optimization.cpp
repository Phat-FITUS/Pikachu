#include "Optimization.h"
#include <stdlib.h>
#include <climits>
#include <iostream>

template<typename T>
void Optimization::swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

void Optimization::initBoardGame(char** board, int width, int height){
	randomPair *list = new randomPair[width * height];

	//add value to pair
	for (int i = 0; i < width * height; i++) {
		list[i].value = i / 2 % ('Z' - 'A' + 1);
		list[i].randomOrder = rand() % 9876543210;
	}

	//sort the random order
	for (int i = 0; i < width * height; i++) {
		for (int j = i + 1; j < width * height; j++) {
			if (list[i].randomOrder > list[j].randomOrder) {
				Optimization::swap(list[i], list[j]);
			}
		}
	}

	//put the random to data
	int randomIndex = 0;
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= height; j++) {
			board[i][j] = list[randomIndex++].value + 'A';
		}
	}

	//delallocate the temporary memory
	delete[] list;
}

void Optimization::shuffleBoardGame(char** board, int width, int height) {
	//Get the number of non-zero element
	int numberOfNon_zeroElement = 0;
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= width; j++) {
			if (board[i][j] != 0) {
				numberOfNon_zeroElement++;
			}
		}
	}

	//Allocate list of random value
	randomPair* list = new randomPair[numberOfNon_zeroElement];

	//Add value to pair
	int index = 0;
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= width; j++) {
			if (board[i][j] != 0) {
				list[index].value = board[i][j];
				list[index++].randomOrder = rand() % 9876543210;
			}
		}
	}

	//sort the random order
	for (int i = 0; i < width * height; i++) {
		for (int j = i + 1; j < width * height; j++) {
			if (list[i].randomOrder > list[j].randomOrder) {
				Optimization::swap(list[i], list[j]);
			}
		}
	}

	//put the random to data
	index = 0;
	for (int i = 1; i <= width; i++) {
		for (int j = 1; j <= height; j++) {
			if (board[i][j] != 0) {
				board[i][j] = list[index++].value;
			}
		}
	}

	//delallocate the temporary memory
	delete[] list;
}

bool Optimization::canConnect(char** board, int width, int height, Coordinate root, Coordinate destination){
	//initialization
	bool** mark = new bool* [width + 2];
	Coordinate** trace = new Coordinate* [width + 2];

	for (int i = 0; i < width + 2; i++) {
		mark[i] = new bool[height + 2];
		trace[i] = new Coordinate[height + 2];

		for (int j = 0; j < height + 2; j++) {
			mark[i][j] = false;
			trace[i][j] = Coordinate(i, j);
		}
	}

	int numberOfTurn = INT_MAX;
	queue<Coordinate> queue;

	//Add root as first point to be visited
	mark[root.x][root.y] = true;
	queue.push(root);

	Optimization::spreadRoute(board, width, height, root, destination, trace, queue, mark, numberOfTurn);

	//Deallocation
	for (int i = 0; i < width + 2; i++) {
		delete[] mark[i];
		delete[] trace[i];
	}
	delete[] mark;
	delete[] trace;

	return numberOfTurn <= 2;
}

queue<Coordinate> Optimization::getPath(char** board, int width, int height, Coordinate root, Coordinate destination) {
	//initialization
	bool** mark = new bool* [width + 2];
	Coordinate** trace = new Coordinate * [width + 2];

	for (int i = 0; i < width + 2; i++) {
		mark[i] = new bool[height + 2];
		trace[i] = new Coordinate[height + 2];

		for (int j = 0; j < height + 2; j++) {
			mark[i][j] = false;
			trace[i][j] = Coordinate(i, j);
		}
	}

	int numberOfTurn = INT_MAX;
	queue<Coordinate> listPoint;

	//Add root as first point to be visited
	mark[root.x][root.y] = true;
	listPoint.push(root);

	Optimization::spreadRoute(board, width, height, root, destination, trace, listPoint, mark, numberOfTurn);

	queue<Coordinate> path = makePath(trace, destination);

	//Deallocation
	for (int i = 0; i < width + 2; i++) {
		delete[] mark[i];
		delete[] trace[i];
	}
	delete[] mark;
	delete[] trace;

	return path;
}

queue<Coordinate> Optimization::makePath(Coordinate** trace, Coordinate destination) {
	queue<Coordinate> path;
	Coordinate currentPoint = destination;

	while (trace[currentPoint.x][currentPoint.y] != currentPoint) {
		path.push(currentPoint);
		currentPoint = trace[currentPoint.x][currentPoint.y];
	}
	path.push(currentPoint);

	return path;
}

int Optimization::getNumberOfTurn(Coordinate** trace, Coordinate destination) {
	queue<Coordinate> path = Optimization::makePath(trace, destination);
	
	if (path.size() < 2) {
		//In case of no path, max int is return to make sure the greedy condition ignore it
		return INT_MAX;
	}

	int numberOfTurn = 0;

	//Take 2 first of point as a root to get the type of change
	Coordinate p1 = path.front();
	path.pop();

	Coordinate p2 = path.front();
	path.pop();

	//See x change as a basical type
	bool isXChange = p1.x != p2.x;

	//Traverse from destination to the root
	while (!path.empty()) {
		//Move point to the next
		p1 = p2;
		p2 = path.front();
		path.pop();

		//Save the current change
		bool isCurrentXChange = p1.x != p2.x;

		//If the change is the same type, the line will continune with the old direction
		//Otherwise, the direction is changed, so the path is turned
		//Assign the new direction to the old one to make sure the next is compared to the current
		if (isCurrentXChange != isXChange) {
			isXChange = isCurrentXChange;
			numberOfTurn++;
		}
	}

	return numberOfTurn;
}

void Optimization::spreadRoute(char** board, int width, int height, Coordinate root, Coordinate destination, Coordinate** trace, queue<Coordinate> listPoint, bool** isVisited, int& numberOfTurn) {
	//Nothing to spread
	if (listPoint.empty()) return;

	queue<Coordinate> newQueue;

	while (!listPoint.empty()){
		Coordinate currentPoint = listPoint.front();

		//Move up
		if (currentPoint.y > 0) {
			Optimization::moveTo(board, currentPoint, Coordinate(currentPoint.x, currentPoint.y - 1), destination, trace, listPoint, isVisited, numberOfTurn);
		}

		//Move down
		if (currentPoint.y < height + 1) {
			Optimization::moveTo(board, currentPoint, Coordinate(currentPoint.x, currentPoint.y + 1), destination, trace, listPoint, isVisited, numberOfTurn);
		}

		//Move left
		if (currentPoint.x > 0) {
			Optimization::moveTo(board, currentPoint, Coordinate(currentPoint.x - 1, currentPoint.y), destination, trace, listPoint, isVisited, numberOfTurn);
		}

		//Move right
		if (currentPoint.x < width + 1) {
			Optimization::moveTo(board, currentPoint, Coordinate(currentPoint.x + 1, currentPoint.y), destination, trace, listPoint, isVisited, numberOfTurn);
		}

		//remove the calculated point
		listPoint.pop();
	}

	//Call recursion
	Optimization::spreadRoute(board, width, height, root, destination, trace, newQueue, isVisited, numberOfTurn);
}

void Optimization::moveTo(char** board, Coordinate previous, Coordinate current, Coordinate destination, Coordinate** trace, queue<Coordinate>& listPoint, bool** isVisited, int& numberOfTurn) {
	//Do not go back to the old path =)))
	if (isVisited[current.x][current.y]) return;

	//Reach the destination
	if (current == destination) {
		//Save the previous point which came to the destination
		Coordinate previousPoint = trace[destination.x][destination.y];

		//Try assigning the new path
		trace[destination.x][destination.y] = previous;

		//Get the number of turn when assigning the new path
		int newNumberOfTurn = Optimization::getNumberOfTurn(trace, destination);

		//Use greedy to take only the path with smallest number of turn
		//Otherwise, restore the old path to the destination
		if (numberOfTurn > newNumberOfTurn) {
			numberOfTurn = newNumberOfTurn;
		}
		else {
			trace[destination.x][destination.y] = previousPoint;
		}
	}
	else if (board[current.x][current.y] == 0) { //Can only go to the empty cell
		listPoint.push(current);
		trace[current.x][current.y] = previous;
		isVisited[current.x][current.y] = true;
	}

}
