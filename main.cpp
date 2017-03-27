#include "Game.h"
#include "SDLFactory.h"

int main(int argc, char** argv)
{
    NSGame::AbstractFactory* F = new NSSDL::SDLFactory();
    NSGame::Game *game = new NSGame::Game(F);
    game->start();
    return 0;
}