#pragma once

struct Coordinate {
	int x;
	int y;

	Coordinate(int x, int y);
	Coordinate();

	bool operator == (Coordinate other);
	bool operator != (Coordinate other);
	void operator = (Coordinate other);
};

struct CoupleCoordinate {
	Coordinate first_choice;
	Coordinate second_choice;

	void operator = (CoupleCoordinate other);
};

