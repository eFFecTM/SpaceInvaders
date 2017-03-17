#include <iostream>
#include "Game.h"

Game::Game(AbstractFactory* af)
{
    this->af = af;
}

void Game::start()
{
    af->init();
    player = af->getPlayer();
    ls = 50; // left side border
    rs = 700; // right side border
    us = 25; // up side border
    bs = 600-*player->getHeight(); // bottom side border
    for(unsigned int i=0; i<8; i++)
    {
        enemies.push_back(af->getEnemy(ls+80*i,us,1));
        enemies.push_back(af->getEnemy(ls+80*i,us+60,2));
        enemies.push_back(af->getEnemy(ls+80*i,us+2*60,3));
        enemies.push_back(af->getEnemy(ls+80*i,us+3*60,4));
    }

    Event e;
    int i = 0;
    while(running)
    {
        e = af->getEvent();
        running = handleEvent(e);
        if(i == 125)
        {
            moveEnemies();
            shootEnemies();
            i = 0;
        }
        i++;
        moveRockets();
        collisionDetection();
        af->renderBackground();
        player->render();

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
            if (*player->getX() > 0)
            {
                player->setX(*player->getX() - 3);
            }
            break;
        case Right:
            if (*player->getX() < 720)
            {
                player->setX(*player->getX() + 3);
            }
            break;
        case Shoot:
            cout << rockets.size() << endl;
            if(rockets.size() < 5) // Max 5 rockets in existence
            {
                x = *player->getX()+ *player->getWidth()/2;
                y = *player->getY();
                rockets.push_back(af->getRocket(x,y));
            }
            break;
        default:
            break;
    }

    return running;
}

void Game::moveRockets()
{
    Entity* playerRocket;
    for(unsigned int i=0; i<rockets.size(); i++)
    {
        playerRocket = rockets.at(i);
        if(*playerRocket->getY() > -*playerRocket->getHeight())
            playerRocket->setY(*playerRocket->getY() - 1);
        else
        {
            delete playerRocket;
            rockets.erase(rockets.begin() + i);
        }
    }
}

void Game::moveEnemies()
{
    bool isMovingDown = false;

    for(Entity* enemy : enemies)
    {
        if(right && *enemy->getX() >= rs)
        {
            isMovingDown = true;
            right = false;
            break;
        }
        else if(!right && *enemy->getX() <= ls)
        {
            isMovingDown = true;
            right = true;
            break;
        }
    }

    if(isMovingDown)
    {
        for(Entity* enemy : enemies)
        {
            enemy->setY(*enemy->getY()+60);
        }
    }
    else
    {
        for(Entity* enemy : enemies)
        {
            if (right)
            {
                enemy->setX(*enemy->getX() + 20);
            }
            else // going left
            {
                enemy->setX(*enemy->getX() - 20);
            }
        }
    }
}

void Game::shootEnemies()
{


}

void Game::collisionDetection()
{
    for(unsigned int i=0;i<enemies.size();i++)
    {
        for(unsigned int j=0;j<rockets.size();j++)
        {
            Entity* enemy = enemies.at(i);
            Entity* rocket = rockets.at(j);
            if(hasIntersection(enemy,rocket))
            {
                delete enemy;
                enemies.erase(enemies.begin() + i);
                delete rocket;
                rockets.erase(rockets.begin() + j);
                break;
            }

        }
    }
}

// Algorithm from SDL library: SDL_rect.c (om gamecode in game te houden)
// Source code available on https://www.libsdl.org/
// A is enemy, B is rocket
bool Game::hasIntersection(Entity* A, Entity* B)
{
    int Amin, Amax, Bmin, Bmax;

    /* Horizontal intersection */
    Amin = *A->getX();
    Amax = Amin + *A->getWidth();
    Bmin = *B->getX();
    Bmax = Bmin + *B->getWidth();
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    /* Vertical intersection */
    Amin = *A->getY();
    Amax = Amin + *A->getHeight();
    Bmin = *B->getY();
    Bmax = Bmin + *B->getHeight();
    if (Bmin > Amin)
        Amin = Bmin;
    if (Bmax < Amax)
        Amax = Bmax;
    if (Amax <= Amin)
        return false;

    return true;
}

