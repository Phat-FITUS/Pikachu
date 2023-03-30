#include <iostream>
#include "Console.h"
#include "Board.h"
#include "Optimization.h"

using namespace std;

Board::Board() {
    this->height = 0;
    this->width = 0;
    this->data = NULL;
}

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
    this->allocate();
}

Board::~Board() {
    this->width = 0;
    this->height = 0;
    if (this->data) {
        this->deallocate();
    }
}

void Board::allocate() {
    this->data = new char* [width + 2];

    for (int i = 0; i < width + 2; i++) {
        this->data[i] = new char[height + 2];

        for (int j = 0; j < height + 2; j++) {
            this->data[i][j] = 0;
        }
    }
}

void Board::deallocate() {
    for (int i = 0; i < this->width + 2; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;
}

bool Board::checkValidSize(int width, int height)
{
    return (width % 2 == 0
        || height % 2 == 0) 
        && (width <= this->MAX_SIZE
        && 0 < width
        && 0 < height
        && height <= this->MAX_SIZE);
}

bool Board::canPlay(){
    bool canPlay = false;
    for (int x1 = 1; x1 <= this->width && !canPlay; x1++) {
        for (int y1 = 1; y1 <= this->height && !canPlay; y1++) {
            for (int x2 = 1; x2 <= this->width && !canPlay; x2++) {
                for (int y2 = 1; y2 <= this->height && !canPlay; y2++) {
                    if ((x1 != x2 || y1 != y2) && this->data[x1][y1] == this->data[x2][y2] && this->data[x1][y1] != 0) {
                        canPlay = Optimization().canConnect(this->data, this->width, this->height, Coordinate(x1, y1), Coordinate(x2, y2));
                    }
                }
            }
        }
    }
    return canPlay;
}

CoupleCoordinate Board::help() {
    for (int x1 = 1; x1 <= this->width; x1++) {
        for (int y1 = 1; y1 <= this->height; y1++) {
            for (int x2 = 1; x2 <= this->width; x2++) {
                for (int y2 = 1; y2 <= this->height; y2++) {
                    if ((x1 != x2 || y1 != y2) 
                        && this->data[x1][y1] == this->data[x2][y2] 
                        && this->data[x1][y1] != 0
                        && Optimization::canConnect(this->data, this->width, this->height, Coordinate(x1, y1), Coordinate(x2, y2))
                    ) {
                        CoupleCoordinate hint;

                        //Store suggested points
                        hint.first_choice = Coordinate(x1, y1);
                        hint.second_choice = Coordinate(x2, y2);

                        return hint;
                    }
                }
            }
        }
    }
}

void Board::display(int x_start, int y_start, Coordinate currentSelection, Coordinate active[2], CoupleCoordinate hint) {
    for (int i = 1; i <= this->width; i++) {
        for (int j = 1; j <= this->height; j++) {
            this->draw.Cell((i - 1) * this->CELL_WIDTH + x_start, //Left top x of a Cell
                (j - 1) * this->CELL_HEIGHT + y_start,            //Left top y of a Cell
                this->CELL_WIDTH,  //Width default of a Cell
                this->CELL_HEIGHT, //Height default of a Cell
                this->data[i][j], //Value text of a Cell
                currentSelection == Coordinate(i, j),
                active[0] == Coordinate(i, j) || active[1] == Coordinate(i, j),
                hint.first_choice == Coordinate(i, j) || hint.second_choice == Coordinate(i, j)
            );
        }
    }
}

void Board::fill(char initialization) {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->data[i][j] = initialization;
        }
    }
}

void Board::addPokemon(){
    shuffle:

    Optimization::initBoardGame(this->data, this->width, this->height);

    if (!canPlay()) goto shuffle;
}

bool Board::changeSize(int width, int height) {
    //Invalid size
    if (!this->checkValidSize(width, height)) return false;

    //In case of data is already allocated
    //We have to free the old allocated memory before allocating a new one
    if (this->data) this->deallocate();

    //Change old size to the new one
    this->width = width;
    this->height = height;
    this->allocate();

    //Change successfully
    return true;
}

int Board::getWidth() {
    return this->width;
}

int Board::getHeight() {
    return this->height;
}

char** Board::getData() {
    return this->data;
}
