#include "Object.h"
#include <iostream>


void Object::HorizontalLine(int x, int y, int width, char value) {
    for (int x0 = 0; x0 < width; x0++) {
        this->screen.GoTo(x + x0, y);
        cout << value;
    }
}

void Object::VerticalLine(int x, int y, int height, char value) {
    for (int y0 = 0; y0 < height; y0++) {
        this->screen.GoTo(x, y + y0);
        cout << value;
    }
}

void Object::Cell(int x, int y, int width, int height, char value, bool selected) {
    this->screen.GoTo(x, y);
    if (selected) {
        this->screen.SetColor(screen.color.Black, screen.color.LightBlue);
    }
    else {
        this->screen.SetColor(screen.color.Black, screen.color.White);
    }
    //Calculate the center position
    int x_center = width % 2 == 0 ? x - 1 + width / 2 : x + width / 2;
    int y_center = height % 2 == 0 ? y - 1 + height / 2 : y + height / 2;

    //Insert character into cell
    this->screen.GoTo(x_center, y_center);
    cout << value;

    //Object top horizontal line
    this->HorizontalLine(x + 1, y, width - 2, '-');

    //Object right vertical line
    this->VerticalLine(x + width - 1, y + 1, height - 2, '|');

    //Object bottom horizontal line
    this->HorizontalLine(x + 1, y + height - 1, width - 2, '-');

    //Object left vertical line
    this->VerticalLine(x, y + 1, height - 2, '|');

    //Set the console pointer to the right bottom of the object
    //Purpose: Avoid some cout which will lay over the object
    this->screen.GoTo(x + width, y + height);
}

void Object::Button(int x, int y, int width, int height, string text, bool selected) {
    this->screen.GoTo(x, y);
    if (selected) {
        this->screen.SetColor(screen.color.Black, screen.color.LightBlue);
    }
    else {
        this->screen.SetColor(screen.color.Black, screen.color.White);
    }
    //Calculate the center position
    int x_center = x + (width - text.length()) / 2;
    int y_center = y + height / 2;

    //Insert character into cell
    this->screen.GoTo(x_center, y_center);
    cout << text;

    //Object top horizontal line
    this->HorizontalLine(x, y, width, (char) 220);

    //Object right vertical line
    this->VerticalLine(x + width - 1, y + 1, height - 2, (char) 219);

    //Object bottom horizontal line
    this->HorizontalLine(x, y + height - 1, width, (char) 223);

    //Object left vertical line
    this->VerticalLine(x, y + 1, height - 2, (char) 219);

    //Set the console pointer to the right bottom of the object
    //Purpose: Avoid some cout which will lay over the object
    this->screen.GoTo(x + width, y + height);
}

void Object::TextEntry(int x, int y, int width, int height, string title, string value, string placeholder, bool selected) {
    this->screen.GoTo(x, y);

    if (selected) {
        this->screen.SetColor(screen.color.Black, screen.color.LightBlue);
    }
    else {
        this->screen.SetColor(screen.color.Black, screen.color.White);
    }

    //top of text entry
    cout << (char) 218;
    this->HorizontalLine(x + 1, y, width - 2, (char) 196);
    cout << (char) 191;

    //bottom of entry
    this->screen.GoTo(x, y + height);
    cout << char(192);
    this->HorizontalLine(x + 1, y + height, width - 2, (char) 196);
    cout << char(217);

    //left of entry
    this->VerticalLine(x, y + 1, height - 1, (char) 179);

    //right of entry
    this->VerticalLine(x + width - 1, y + 1, height - 1, (char) 179);

    //title of entry
    this->screen.GoTo(x + 3, y);
    for (char t : title) {
        if (t == char(32)) cout << char(196);
        else cout << t;
    }

    //value of form
    int x_text = x + 3;
    int y_text = y + height / 2;

    this->screen.GoTo(x_text, y_text);

    if (value.length()) {
        cout << value;
    }
    else {
        cout << placeholder;
    }
}