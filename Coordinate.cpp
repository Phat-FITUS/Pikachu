#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) {
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate() {
	this->x = -1;
	this->y = -1;
}

bool Coordinate::operator == (Coordinate other) {
	return this->x == other.x && this->y == other.y;
}

bool Coordinate::operator != (Coordinate other) {
	return !(this->x == other.x && this->y == other.y);
}

void Coordinate::operator = (Coordinate other) {
	this->x = other.x;
	this->y = other.y;
}