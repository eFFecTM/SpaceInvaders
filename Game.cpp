#include "Game.h"

Game::Game(AbstractFactory* af)
{
    this->af = af;
}

void Game::start()
{
    player = af->getPlayer();
    ls = 32; // left side border
    rs = 748; // right side border
    us = 25; // up side border
    bs = 600-*player->getHeight(); // bottom side border
    for(unsigned int i=0; i<10; i++)
    {
        enemies.push_back(af->getEnemy(ls+60*i,us,1));
        enemies.push_back(af->getEnemy(ls+60*i,us+50,2));
        enemies.push_back(af->getEnemy(ls+60*i,us+2*50,3));
        enemies.push_back(af->getEnemy(ls+60*i,us+3*50,4));
    }

    Event e;
    int i = 0;
    while(running)
    {
        e = af->getEvent();
        running = handleEvent(e);
        if(i == 125)
        {
            shootEnemies();
            moveEnemies();
            i = 0;
        }
        i++;
        moveRockets();
        collisionDetection();
        af->renderBackground();
        player->render();

        for(Enemy* enemy : enemies)
            enemy->render();
        for(Rocket* rocket : playerRockets)
            rocket->render();
        for(Rocket* rocket : enemyRockets)
            rocket->render();
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
                player->setX(*player->getX() - 3);
            break;
        case Right:
            if (*player->getX() < 720)
                player->setX(*player->getX() + 3);
            break;
        case Shoot:
            cout << playerRockets.size() << endl;
            if(playerRockets.size() < 5) // Max 5 playerRockets in existence
            {
                x = *player->getX()+ *player->getWidth()/2;
                y = *player->getY();
                playerRockets.push_back(af->getRocket(x,y,1));
            }
            break;
        default:
            break;
    }
    return running;
}

void Game::moveRockets()
{
    Rocket* rocket;
    for(unsigned int i=0; i<playerRockets.size(); i++)
    {
        rocket = playerRockets.at(i);
        if (*rocket->getY() > -*rocket->getHeight())
            rocket->setY(*rocket->getY() - 1);
        else
        {
            delete rocket;
            playerRockets.erase(playerRockets.begin() + i);
        }
    }

    for(unsigned int i=0; i<enemyRockets.size(); i++)
    {
        rocket = enemyRockets.at(i);
        if(*rocket->getY() < 600)
            rocket->setY(*rocket->getY() + 1);
        else
        {
            delete rocket;
            enemyRockets.erase(enemyRockets.begin() + i);
        }
    }
}

void Game::moveEnemies()
{
    bool isMovingDown = false;

    for(Enemy* enemy : enemies)
    {
        if(right && *enemy->getX() > rs)
        {
            isMovingDown = true;
            right = false;
            break;
        }
        else if(!right && *enemy->getX() < ls)
        {
            isMovingDown = true;
            right = true;
            break;
        }
    }

    if(isMovingDown)
    {
        for(Enemy* enemy : enemies)
        {
            enemy->setY(*enemy->getY()+60);
        }
    }
    else
    {
        for(Enemy* enemy : enemies)
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
    int size = enemies.size();
    srand((unsigned int) time(0));
    int r = rand() % size; // 0 tot en met 31
    Enemy* enemy = enemies.at((unsigned int) r);
    int x = *enemy->getX();
    int y = *enemy->getY();
    enemyRockets.push_back(af->getRocket(x,y,2));
}

void Game::addScore(int)
{

}

void Game::collisionDetection()
{
    for(unsigned int i=0;i<enemies.size();i++)
    {
        for(unsigned int j=0;j<playerRockets.size();j++)
        {
            Enemy* enemy = enemies.at(i);
            Rocket* rocket = playerRockets.at(j);

            if(hasIntersection(enemy,rocket))
            {
                delete enemy;
                enemies.erase(enemies.begin() + i);
                delete rocket;
                playerRockets.erase(playerRockets.begin() + j);
                break;
            }
        }
    }

    for(unsigned int i=0;i<enemyRockets.size();i++)
    {
        Rocket* rocket = enemyRockets.at(i);

        if(hasIntersection(player,rocket))
        {
            delete rocket;
            enemyRockets.erase(enemyRockets.begin() + i);
            break;
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
