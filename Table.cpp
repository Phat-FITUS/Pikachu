#include <iostream>
#include "Console.h"
#include "Colors.h"
#include "Keys.h"

using namespace std;

void drawCell(int width, int height, int x, int y, char value) {

    Console screen;

    //Insert Character Into Cell.
    int x_center = width % 2 == 0 ? x - 1 + width / 2 : x + width / 2;
    int y_center = height % 2 != 0 ? y - 1 + height / 2 : y + height / 2;
   
    screen.GoTo(x_center , y_center);
    cout << value;

    screen.GoTo(x, y);

    //Draw Top Horizontal
    cout << "*";
    for (int i = 1; i < width - 1; i++) {
        cout << "-";
    }
    cout << "*";
    y++;
    screen.GoTo(x, y);


    //Draw Vertical
    for (int i = 1; i < height - 1; i++) {
        cout << "|";
        screen.GoTo(x + width - 1, y);
        cout << "|";
        y++;
        screen.GoTo(x, y);
    }
    cout << "*";


    //Draw Bot Horizontal
    for (int i = 1; i < width - 1; i++) {
        cout << "-";
    }
    cout << "*";
    y++;
    screen.GoTo(x, y);

}

void PrintBoard(int width, int height, int x_start, int y_start, char** ptr) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            drawCell(10, 5, i * 10 + x_start, j * 5 + y_start, ptr[i][j]);
        }
    }
}

void fill(char** ptr, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            ptr[i][j] = 'A';
        }
    }
}

void getBoardSize(int& width, int& height) {
    do {
        cin >> width;
    } while (width <= 0 || width > 8);

    do {
        cin >> height;
    } while (height <= 0 || height > 8);
}