#include "Asteroid.h"

GlobalVariables::GlobalVariables()
{
    GameOver = false;
    godmode = false;
    gameStarted = false;
    exitGame = false;

    srand(time(0));
}

void GlobalVariables::reset()
{
    gameStarted = false;
    GameOver = false;
}
