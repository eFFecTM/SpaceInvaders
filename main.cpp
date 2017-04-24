/**
 * Makes a factory and starts a game
 */

#include<windows.h>
#include "Game.h"
#include "SDLFactory.h"

int main(int argc, char** argv)
{
    ShowWindow(GetConsoleWindow(), 0);

    NSGame::AbstractFactory* F = new NSSDL::SDLFactory();
    NSGame::Game *game = new NSGame::Game(F);
    game->start();
    return 0;
}