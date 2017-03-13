#include "Game.h"
#include "SDLFactory.h"

int main(int argc, char** argv)
{
    AbstractFactory* F = new SDLFactory();
    Game *game = new Game(F);
    game->start();

    return 0;
}