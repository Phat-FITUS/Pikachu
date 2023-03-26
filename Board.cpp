#include <iostream>
#include "Console.h"
#include "Board.h"

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
    this->deallocate();
}

void Board::allocate() {
    this->data = new char* [height];
    for (int i = 0; i < height; i++) {
        this->data[i] = new char[width];
    }
}

void Board::deallocate() {
    for (int i = 0; i < this->height; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;
}

bool Board::checkValidSize(int width, int height)
{
    return (width % 2 == 0
        || height % 2 == 0) 
        && (width <= Board().MAX_SIZE
        && 0 < width
        && 0 < height
        && height <= Board().MAX_SIZE);
}

void Board::display(int x_start, int y_start) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->draw.Cell(i * this->CELL_WIDTH + x_start, //Left top x of a Cell
                j * this->CELL_HEIGHT + y_start,            //Left top y of a Cell
                this->CELL_WIDTH,  //Width default of a Cell
                this->CELL_HEIGHT, //Height default of a Cell
                this->data[i][j], //Value text of a Cell
                this->selection
            );
        }
    }
}

void Board::fill(char initialization) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            this->data[i][j] = initialization;
        }
    }
}

bool Board::changeSize(int width, int height) {
    //Invalid size
    if (!Board().checkValidSize(width, height)) return false;

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