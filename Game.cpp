#include <iostream>
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
        movePlayerRockets();
        af->renderBackground();
        playerShip->render();
        for(Entity* enemy : enemies)
        {
            enemy->render();
        }
        for(Entity* rocket : rockets)
        {
            rocket->render();
        }
        af->renderPresent();
    }
}

bool Game::handleEvent(Event e)
{
    bool running = true;
    int x,y;

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
            if (*playerShip->getX() < 720)
            {
                playerShip->setX(*playerShip->getX() + 10);
            }
            break;
        case Shoot:
            x = *playerShip->getX()+ *playerShip->getWidth()/2;
            y = *playerShip->getY();
            rockets.push_back(af->getPlayerRocket(x,y));
            break;
        default:
            break;
    }

    return running;
}

void Game::movePlayerRockets()
{
    for(unsigned int i=0; i<rockets.size(); i++)
    {
        if(*rockets.at(i)->getY() > 0)
            rockets.at(i)->setY(*rockets.at(i)->getY() - 1);
        else
            rockets.erase(rockets.begin() + i);
    }
}
