#include <iostream>
#include "Console.h"
#include "Colors.h"
#include "Keys.h"

using namespace std;

void drawCell(int width, int height, int x, int y) {

    Console screen;

    //Insert Character Into Cell.
    if (width % 2 == 0) {
        if (height % 2 == 0) {
            screen.GoTo(x - 1 + width / 2, y - 1 + height / 2);
            cout << "A";
        }
        else {
            screen.GoTo(x - 1 + width / 2, y + height / 2);
            cout << "A";
        }
    }
    else {
        if (height % 2 != 0) {
            screen.GoTo(x + width / 2, y + height / 2);
            cout << "A";
        }
        else {
            screen.GoTo(x + width / 2, y - 1 + height / 2);
            cout << "A";
        }
    }

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
    for (int i = 1; i < width; i++) {
        for (int j = 1; j < height; j++) {
            drawCell(10, 5, i * 10 + x_start, j * 5 + y_start);
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

int main()
{
    char** ptr;
    ptr = new char* [10];

    for (int i = 0; i < 5; i++) {
        ptr[i] = new char[6];
    }







    for (int i = 0; i < 5; i++)
    {
        delete[] ptr[i];
        ptr[i] = NULL;
    }
    return 0;
}


