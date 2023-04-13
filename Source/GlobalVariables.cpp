#include "Asteroid.h"

GlobalVariables::GlobalVariables()
{
    GameOver = false;
    godmode = false;
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
