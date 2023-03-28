#include <iostream>
#include "Game.h"
#include <time.h>

using namespace std;

int main()
{
    srand(time(NULL));
    Game pikachu;
    pikachu.start();

    return 0;
}