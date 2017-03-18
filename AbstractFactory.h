#ifndef SPACEINVADERS_ABSTRACTFACTORY_H
#define SPACEINVADERS_ABSTRACTFACTORY_H

#include "Rocket.h"
#include "Player.h"
#include "Enemy.h"
#include "Event.h"

class AbstractFactory
{
public:
    AbstractFactory(){};
    virtual Player* getPlayer() = 0; // Maak abstract
    virtual Rocket* getRocket(int,int,int) = 0;
    virtual Enemy* getEnemy(int,int,int) = 0;
    virtual Event getEvent() = 0;
    virtual void renderBackground() = 0;
    virtual void renderScore(int) = 0;
    virtual void renderPresent() = 0;
    virtual void startTimer() = 0;
    virtual int getTickDifference() = 0;
    virtual void addDelay(int) = 0;
    virtual void playSoundEffect(int) = 0;
};

#endif //SPACEINVADERS_ABSTRACTFACTORY_H
