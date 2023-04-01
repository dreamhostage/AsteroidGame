#include "Asteroid.h"

GlobalVariables::GlobalVariables()
{
    GameOver = false;
    godmode = true;
    gameStarted = false;
    exitGame = false;

    bIsGamePaused = true;

    srand(time(0));
}

void GlobalVariables::reset()
{
    gameStarted = false;
    GameOver = false;
}
