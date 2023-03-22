#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    cout << "Ditme BHT\n";
    Board game(4, 4);
    game.fill('A');
    game.display(2, 2);

    return 0;
}