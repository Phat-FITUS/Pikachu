#include "Draw.h"
#include <iostream>

using namespace std;

void Draw::HorizontalLine(int x, int y, int width, char value) {
    for (int x0 = 0; x0 < width; x0++) {
        this->screen.GoTo(x + x0, y);
        cout << value;
    }
}

void Draw::VerticalLine(int x, int y, int height, char value) {
    for (int y0 = 0; y0 < height; y0++) {
        this->screen.GoTo(x, y + y0);
        cout << value;
    }
}

void Draw::Cell(int x, int y, int width, int height, char value) {
    //Calculate the center position
    int x_center = width % 2 == 0 ? x - 1 + width / 2 : x + width / 2;
    int y_center = height % 2 == 0 ? y - 1 + height / 2 : y + height / 2;

    //Insert character into cell
    this->screen.GoTo(x_center, y_center);
    cout << value;

    //Draw top horizontal line
    this->HorizontalLine(x + 1, y, width - 2, '-');

    //Draw right vertical line
    this->VerticalLine(x + width - 1, y + 1, height - 2, '|');

    //Draw bottom horizontal line
    this->HorizontalLine(x + 1, y + height - 1, width - 2, '-');

    //Draw left vertical line
    this->VerticalLine(x, y + 1, height - 2, '|');

    //Set the console pointer to the right bottom of the object
    //Purpose: Avoid some cout which will lay over the object
    this->screen.GoTo(x + width, y + height);
}