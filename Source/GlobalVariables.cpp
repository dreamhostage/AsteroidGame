#include "Asteroid.h"

GlobalVariables::GlobalVariables()
{
    GameOver = false;
    godmode = true;
    gameStarted = false;

    srand(time(0));
}

void GlobalVariables::reset()
{
    gameStarted = false;
    GameOver = false;
}
