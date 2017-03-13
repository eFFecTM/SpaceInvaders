#include "Game.h"

Game::Game(AbstractFactory* af)
{
    this->af = af;
}

void Game::start()
{
    af->init();
    playerShip = af->getPlayerShip();
    Event e;

    while(running)
    {
        e = af->getEvent();
        running = handleEvent(e);
        af->renderBackground();
        playerShip->render();
        af->renderPresent();
    }
}

bool Game::handleEvent(Event e)
{
    bool running = true;

    switch(e)
    {
        case Close:
            running = false;
            break;
        case Left:
            if (*playerShip->getX() > 0)
            {
                playerShip->setX(*playerShip->getX() - 10);
            }
            break;
        case Right:
            if (*playerShip->getX() < 725)
            {
                playerShip->setX(*playerShip->getX() + 10);
            }
            break;
        default:
            break;
    }

    return running;
}

